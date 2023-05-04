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

	// listen()�����еĲ���1024��Linux�ں���backlog���еĴ�С����ʾ��������δ���������
	// �ڸ߲��������£�������Ҫ������������Ĵ�С���������
	void listen();
	int accept(InetAddress* peerAddr);

	void setReuseAddr(bool oper);
	void setReusePort(bool oper);
	void setTcpNoDelay(bool oper);
	void setKeepAlive(bool oper);

	void shutdownWrite();
};