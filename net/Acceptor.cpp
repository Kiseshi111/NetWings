#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include "../include/Acceptor.h"
#include "../include/InetAddress.h"

static int createNonblockingSockfd()
{
	/*
		AF_INET : ʹ��IPV4Э��
		SOCK_STREAM : ʹ���ֽ���TCP����
		SOCK_NONBLOCK : ������
		SOCK_CLOEXEC : ���ӽ����йرո�socket
	*/
	int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
	if (sockfd < 0)
	{
		printf("listen socket create error");
	}
	return sockfd;
}

Acceptor::Acceptor(EventLoop* loop,
	const InetAddress& listenAddr,
	bool reuseport)
	: myloop(loop)
	, acceptSocket(createNonblockingSockfd())
	, acceptChannel(myloop, acceptSocket.fd())
	, listening(false)
{
	acceptSocket.setReuseAddr(true);
	acceptSocket.setReusePort(true);
	acceptSocket.bindAddress(listenAddr);

	acceptChannel.setReadCallback(
		std::bind(&Acceptor::handleRead, this)
	);
}

Acceptor::~Acceptor()
{
	acceptChannel.disabelAll();
	acceptChannel.remove();
}

void Acceptor::listen()
{
	listening = true;
	acceptSocket.listen();
	// channelע����Poller
	acceptChannel.enableReading();
}

void Acceptor::handleRead()
{
	InetAddress peerAddr;
	int connfd = acceptSocket.accept(&peerAddr);
	if (connfd >= 0)
	{
		if (newConnectionCallback)
		{
			newConnectionCallback(connfd, peerAddr);
		}
		else
		{
			::close(connfd);
		}
	}
	else
	{
		printf("accept error");
	}
}