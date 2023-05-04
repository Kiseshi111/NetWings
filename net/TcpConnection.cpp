#include <functional>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/tcp.h>

#include "../include/TcpConnection.h"
#include "../include/Socket.h"
#include "../include/Channel.h"
#include "../include/EventLoop.h"

static EventLoop* checkLoopNotNull(EventLoop* loop)
{
	if (loop == nullptr)
	{
		printf("%s:%s:%d mainLoop is null!\n", __FILE__, __FUNCTION__, __LINE__);
	}
	return loop;
}

TcpConnection::TcpConnection(EventLoop* loop,
			const std::string &nameArg,
			const InetAddress &localAddr,
			const InetAddress &peerAddr,
			int sockfd)
	:myloop(checkLoopNotNull(loop))
	,myname(nameArg)
	,myLocalAddr(localAddr)
	,myPeerAddr(peerAddr)
	,socket(new Socket(sockfd))
	,channel(new Channel(loop, sockfd))
	,mystate(Connecting)
	,highWaterMark(64 * 1024 * 1024)
{
	channel->setReadCallback(
		std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
	channel->setWriteCallback(
		std::bind(&TcpConnection::handleWrite, this));
	channel->setCloseCallback(
		std::bind(&TcpConnection::handleClose, this));
	channel->setErrorCallback(
		std::bind(&TcpConnection::handleError, this));

	printf("TcpConnection::construction[%s] at fd = %d\n", myname.c_str(), sockfd);

	socket->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
	printf("TcpConnection::destruction[%s] at fd = %d state = %d\n", myname.c_str(), channel->fd(), (int)mystate);
}

void TcpConnection::connectEstablished()
{
	setState(Connected);

	channel->doExtend(shared_from_this());

	channel->enableReading();

	// 防止TcpConnection意外析构
	connectionCallback(shared_from_this());
}

void TcpConnection::connectDestroyed()
{
	if (mystate == Connected)
	{
		setState(Disconnected);

		channel->disabelAll();
		connectionCallback(shared_from_this());
	}
	channel->remove();
}

void TcpConnection::send(const std::string& buf)
{
	if (mystate == Connected)
	{
		if (myloop->isInLoopThread())
		{
			sendInLoop(buf.c_str(), buf.size());
		}
		else
		{
			myloop->runInLoop(
				std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
		}
	}
}

void TcpConnection::shutdown()
{
	if (mystate == Connected)
	{
		setState(Disconnecting);
		myloop->runInLoop(
			std::bind(&TcpConnection::shutdownInLoop, this));
	}
}

void TcpConnection::sendInLoop(const void* data, size_t len)
{
	ssize_t nwrote = 0;
	size_t remaining = len;
	bool Error = false;

	if (mystate == Disconnected)
	{
		printf("disconnected, give up writing");
	}

	// 不在写状态且 内核缓冲区不满
	// outputBuffer == 0 表示outputBuffer没有可读字节 即内核缓冲区未满 不需要使用到outputBuffer
	if (!channel->isWriting() && outputBuffer.readableBytes() == 0)
	{
		nwrote = ::write(channel->fd(), data, len);
		if (nwrote >= 0)
		{
			remaining = len - nwrote;
			// 若数据一次性发送完
			if (remaining == 0 && writeCompleteCallback)
			{
				myloop->queueInLoop(
				std::bind(writeCompleteCallback, shared_from_this()));
			}
		}
		else
		{
			nwrote = 0;
			// EWOULDBLOCK : 非阻塞下 表示没有数据可读
			if (errno != EWOULDBLOCK)
			{
				printf("TcpConnection::sendInLoop error");
				if (errno == EPIPE || errno == ECONNRESET)
				{
					Error = true;
				}
			}
		}
	}

	// 数据未发送完
	if (!Error && remaining > 0)
	{
		size_t oldLen = outputBuffer.readableBytes();
		
		// 获取当前发送缓冲区的数据长度 和 上次剩余的数据长度的总和 需大于水位线 才会触发回调
		if (oldLen + remaining >= highWaterMark && oldLen < highWaterMark && highWaterMarkCallback)
		{
			myloop->queueInLoop(
				std::bind(highWaterMarkCallback, shared_from_this(), oldLen + remaining));
		}

		// 将剩余未写入数据写入发送缓冲区
		outputBuffer.append((char*)data + nwrote, remaining);

		// 若不在写状态 则需要设置写事件
		if (!channel->isWriting())
		{
			channel->enableWriting();
		}
	}
}

void TcpConnection::shutdownInLoop()
{
	if (!channel->isWriting())
	{
		socket->shutdownWrite();
	}
}

void TcpConnection::handleRead(TimeStamp receiveTime)
{
	int saveErrno = 0;
	ssize_t n = inputBuffer.readFd(channel->fd(), &saveErrno);

	if (n > 0)
	{
		messageCallback(shared_from_this(), &inputBuffer, receiveTime);
	}
	else if (n == 0)
	{
		handleClose();
	}
	else
	{
		errno = saveErrno;
		printf("TcpConnection::handleRead error");
		handleError();
	}
}

void TcpConnection::handleWrite()
{
	if (channel->isWriting())
	{
		int saveErrno = 0;
		ssize_t n = outputBuffer.writeFd(channel->fd(), &saveErrno);
		if (n > 0)
		{
			outputBuffer.retrieve(n);
			if (outputBuffer.readableBytes() == 0)
			{
				channel->disableWriting();
				if (writeCompleteCallback)
				{
					myloop->queueInLoop(
						std::bind(writeCompleteCallback, shared_from_this()));
				}
				if (mystate == Disconnecting)
				{
					shutdownInLoop();
				}
			}
		}
		else
		{
			printf("TcpConnection::handleWrite error");
		}
	}
	else
	{
		printf("TcpConnection fd=%d is down, no more writing", channel->fd());
	}
}

void TcpConnection::handleClose()
{
	printf("TcpConnection::handleClose fd = %d state = %d\n", channel->fd(), (int)mystate);
	setState(Disconnected);

	channel->disabelAll();

	TcpConnectionPtr connPtr(shared_from_this());
	connectionCallback(connPtr);

	closeCallback(connPtr);
}

void TcpConnection::handleError()
{
	int optval;
	socklen_t optlen = sizeof optval;
	int err = 0;

	/*
	    读取socket文件描述符属性 检验
		sockfd : 要进行选项检验的套接字
		level : 选项检验所在的协议层
		optname : 要检验的选项
		optval : 指向接收选项值的缓冲区的指针
		optlen : 指针optlen同时指向输入缓冲区的长度和返回的选项长度值
	*/
	if (::getsockopt(channel->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
	{
		err = errno;
	}
	else
	{
		err = optval;
	}
	printf("TcpConnection::handleError name : %s - SO_ERROR : %d\n", myname.c_str(), err);

}