#pragma once

#include <arpa/inet.h>

#include "../include/Noncopyable.h"

class InetAddress;

class Socket : Noncopyable
{
public:
	explicit Socket(int sockfd)
		:mysockfd(sockfd)
	{}

	~Socket();

private:
	const int mysockfd;

public:
	int fd() const { return mysockfd; }
	void bindAddress(const InetAddress& localaddr);

	// listen()函数中的参数1024是Linux内核中backlog队列的大小，表示允许的最大未完成连接数
	// 在高并发场景下，可能需要调整这个参数的大小以提高性能
	void listen();
	int accept(InetAddress* peerAddr);

	void setReuseAddr(bool oper);
	void setReusePort(bool oper);
	void setTcpNoDelay(bool oper);
	void setKeepAlive(bool oper);

	void shutdownWrite();
};