#include <functional>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "../include/TcpServer.h"
#include "../include/TcpConnection.h"

static EventLoop* CheckLoopNotNull(EventLoop* loop)
{
	if (loop == nullptr)
	{
		printf("%s : %s : %d mainLoop is null!\n", __FILE__, __FUNCTION__, __LINE__);
	}
	return loop;
}

TcpServer::TcpServer(EventLoop* loop,
				const std::string& nameArg,
				const InetAddress& listenAddr,
				Option option)
	:loop(CheckLoopNotNull(loop))
	,name(nameArg)
	,ipPort(listenAddr.toIpPort())
	,acceptor(new Acceptor(loop, listenAddr, option == ReusePort))
	,threadPool(new EventLoopThreadPool(loop, name))
	,connectionCallback()
	,messageCallback()
	,nextConnId(1)
	,started(0)
{
	acceptor->setNewConnectionCallback(
		std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2)
	);
}

TcpServer::~TcpServer()
{
	for (auto& item : connections)
	{
		TcpConnectionPtr conn(item.second);
		// 原始智能指针复位 出作用域则TcpConnectionPtr释放
		item.second.reset();

		conn->getLoop()->runInLoop(
			std::bind(&TcpConnection::connectDestroyed, conn));
	}
}

void TcpServer::start()
{
	// 防止一个TcpServer对象被start多次
	if (started++ == 0)
	{
		threadPool->start(threadInitCallback);
		loop->runInLoop(std::bind(&Acceptor::listen, acceptor.get()));
	}
}

void TcpServer::setThreadNum(int threadNum)
{
	threadPool->setThread(threadNum);
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
	// 获取一个subLoop
	EventLoop* ioLoop = threadPool->getNextLoop();

	char buf[64] = { 0 };

	// 将格式化的数据写入字符串 为每条连接设置不同的name
	snprintf(buf, sizeof buf, "%s%d", ipPort.c_str(), nextConnId);
	++nextConnId;
	std::string connName = name + buf;

	// 通过sockfd获取sockfd绑定的本机的ip和port
	sockaddr_in local;
	::memset(&local, 0, sizeof(local));
	socklen_t addrlen = sizeof(local);
	
	InetAddress localAddr(local);

	TcpConnectionPtr conn(new TcpConnection(
		ioLoop,
		connName,
		localAddr,
		peerAddr,
		sockfd
	));

	// 为当前连接设置回调
	connections[connName] = conn;
	conn->setConnectionCallback(connectionCallback);
	conn->setMessageCallback(messageCallback);
	conn->setWriteCompleteCallback(writeCompleteCallback);
	conn->setCloseCallback(
		std::bind(&TcpServer::removeConnection, this, std::placeholders::_1)
	);

	ioLoop->runInLoop(
		std::bind(&TcpConnection::connectEstablished, conn)
	);
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
	loop->runInLoop(
		std::bind(&TcpServer::removeConnectionInLoop, this, conn)
	);
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
	connections.erase(conn->name());
	EventLoop* ioLoop = conn->getLoop();

	ioLoop->queueInLoop(
		std::bind(
			&TcpConnection::connectDestroyed, conn));
}