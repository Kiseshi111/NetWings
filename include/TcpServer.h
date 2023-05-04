#pragma once

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>

#include "Buffer.h"
#include "Callbacks.h"
#include "Noncopyable.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "EventLoopThreadPool.h"
#include "TcpConnection.h"

class TcpServer
{
public:
	
	using ThreadInitCallback = std::function<void(EventLoop*)>;

	enum Option
	{
		NoReusePort,
		ReusePort
	};

	TcpServer(EventLoop* loop,
		const std::string& nameArg,
		const InetAddress& listenAddr,
		Option option = NoReusePort);
	~TcpServer();

private:
	using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

	EventLoop* loop;

	const std::string ipPort;
	const std::string name;
	
	std::unique_ptr<Acceptor> acceptor;
	std::shared_ptr<EventLoopThreadPool> threadPool;

	ThreadInitCallback threadInitCallback;
	ConnectionCallback connectionCallback;
	MessageCallback messageCallback;
	WriteCompleteCallback writeCompleteCallback;

	ConnectionMap connections;

	std::atomic_int started;
	int nextConnId;

    void newConnection(int sockfd, const InetAddress &peerAddr);
	void removeConnection(const TcpConnectionPtr &conn);
	void removeConnectionInLoop(const TcpConnectionPtr &conn);

public:
	void start();
	void setThreadNum(int threadNum);

	void setThreadInitCallback(const ThreadInitCallback& cb) { threadInitCallback = cb; }
	void setConnectionCallback(const ConnectionCallback& cb) { connectionCallback = cb; }
	void setMessageCallback(const MessageCallback& cb) { messageCallback = cb; }
	void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback = cb; }
};