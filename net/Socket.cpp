#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#include "../include/Socket.h"
#include "../include/InetAddress.h"

Socket::~Socket()
{
	if (::close(mysockfd) < 0)
	{
		printf("close socket failed");
		// �׳��쳣���¼��־
	}
}

void Socket::bindAddress(const InetAddress& localaddr)
{
	if (0 != ::bind(mysockfd, (sockaddr*)localaddr.getSockAddr(), sizeof(sockaddr_in)))
	{
		printf("bind sockfd : %d fail\n", mysockfd);
		// �׳��쳣���¼��־
	}
}

void Socket::listen()
{
	if (0 != ::listen(mysockfd, 1024))
	{
		printf("listen sockfd : %d fail\n", mysockfd);
		// �׳��쳣���¼��־
	}
}

int Socket::accept(InetAddress* peeraddr)
{
	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	::memset(&addr, 0, sizeof(addr));

	int connfd = ::accept4(mysockfd, (sockaddr*)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
	if (connfd >= 0)
	{
		peeraddr->setSockAddr(addr);
	}
	else
	{
		printf("accept4() failed");
	}
	return connfd;
}

void Socket::shutdownWrite()
{
	if (::shutdown(mysockfd, SHUT_WR) < 0)
	{
		printf("shutdownWrite error");
	}
}

// ���ò�ʹ��Nagele�㷨
void Socket::setTcpNoDelay(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval)) < 0)
	{
		printf("setTcpNoDelay error");
		// �׳��쳣���¼��־
	}
}

// ���ÿ����õ�ַ
void Socket::setReuseAddr(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		printf("setReuseAddr error");
		// �׳��쳣���¼��־
	}
}

// ���ÿ����ö˿�
void Socket::setReusePort(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) < 0)
	{
		printf("setReusePort error");
		// �׳��쳣���¼��־
	}
}

// ���ñ�������
void Socket::setKeepAlive(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
	{
		printf("setKeepAlive error");
		// �׳��쳣���¼��־
	}
}
