#pragma once

#include <functional>

#include "Noncopyable.h"
#include "Channel.h"
#include "Socket.h"

class EventLoop;
class InetAddress;

class Acceptor : Noncopyable
{
public:
	using NewConnectionCallback = std::function<void(int sockfd, const InetAddress&)>;

	Acceptor(EventLoop* loop, const InetAddress& listenAddr, bool reuseport);
	~Acceptor();

private:
	EventLoop* myloop;
	Socket acceptSocket;
	Channel acceptChannel;
	NewConnectionCallback newConnectionCallback;

	bool listening;

public:
	void listen();
	bool isListening() const { return listening; }

	void handleRead();
	void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback = cb; }
};