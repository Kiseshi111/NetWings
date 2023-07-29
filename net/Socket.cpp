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
		// 抛出异常或记录日志
	}
}

void Socket::bindAddress(const InetAddress& localaddr)
{
	if (0 != ::bind(mysockfd, (sockaddr*)localaddr.getSockAddr(), sizeof(sockaddr_in)))
	{
		printf("bind sockfd : %d fail\n", mysockfd);
		// 抛出异常或记录日志
	}
}

void Socket::listen()
{
	if (0 != ::listen(mysockfd, 1024))
	{
		printf("listen sockfd : %d fail\n", mysockfd);
		// 抛出异常或记录日志
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

// 设置不使用Nagle算法
// 
// Nagle算法主要是避免发送小的数据包，要求TCP连接上最多只能有一个未被确认的小分组，在该分组的确认到达之前不能发送其他的小分组。
// 相反，TCP收集这些少量的小分组，并在确认到来时以一个分组的方式发出去。

void Socket::setTcpNoDelay(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval)) < 0)
	{
		printf("setTcpNoDelay error");
		// 抛出异常或记录日志
	}
}

// 设置可重用地址
//
// setsockopt函数将SO_REUSEADDR选项设置为1，即可以启用地址重用选项。
// 即使之前的套接字仍然处于TIME_WAIT状态，新的套接字也可以立即绑定到相同的本地地址和端口，从而实现地址的快速重用。

void Socket::setReuseAddr(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		printf("setReuseAddr error");
		// 抛出异常或记录日志
	}
}

// 设置可重用端口
// 当设置了SO_REUSEPORT选项后，多个套接字可以在同一个端口上进行监听，从而实现端口的可重用。
// 不同于SO_REUSEADDR选项，SO_REUSEPORT选项可以实现更好的负载均衡，即内核可以将来自客户端的连接请求平均地分配给多个监听套接字。

void Socket::setReusePort(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) < 0)
	{
		printf("setReusePort error");
		// 抛出异常或记录日志
	}
}

// 设置长连接
void Socket::setKeepAlive(bool oper)
{
	int optval = oper ? 1 : 0;
	if (::setsockopt(mysockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
	{
		printf("setKeepAlive error");
		// 抛出异常或记录日志
	}
}
