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

	// ��ֹTcpConnection��������
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

	// ����д״̬�� �ں˻���������
	// outputBuffer == 0 ��ʾoutputBufferû�пɶ��ֽ� ���ں˻�����δ�� ����Ҫʹ�õ�outputBuffer
	if (!channel->isWriting() && outputBuffer.readableBytes() == 0)
	{
		nwrote = ::write(channel->fd(), data, len);
		if (nwrote >= 0)
		{
			remaining = len - nwrote;
			// ������һ���Է�����
			if (remaining == 0 && writeCompleteCallback)
			{
				myloop->queueInLoop(
				std::bind(writeCompleteCallback, shared_from_this()));
			}
		}
		else
		{
			nwrote = 0;
			// EWOULDBLOCK : �������� ��ʾû�����ݿɶ�
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

	// ����δ������
	if (!Error && remaining > 0)
	{
		size_t oldLen = outputBuffer.readableBytes();
		
		// ��ȡ��ǰ���ͻ����������ݳ��� �� �ϴ�ʣ������ݳ��ȵ��ܺ� �����ˮλ�� �Żᴥ���ص�
		if (oldLen + remaining >= highWaterMark && oldLen < highWaterMark && highWaterMarkCallback)
		{
			myloop->queueInLoop(
				std::bind(highWaterMarkCallback, shared_from_this(), oldLen + remaining));
		}

		// ��ʣ��δд������д�뷢�ͻ�����
		outputBuffer.append((char*)data + nwrote, remaining);

		// ������д״̬ ����Ҫ����д�¼�
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
	    ��ȡsocket�ļ����������� ����
		sockfd : Ҫ����ѡ�������׽���
		level : ѡ��������ڵ�Э���
		optname : Ҫ�����ѡ��
		optval : ָ�����ѡ��ֵ�Ļ�������ָ��
		optlen : ָ��optlenͬʱָ�����뻺�����ĳ��Ⱥͷ��ص�ѡ���ֵ
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