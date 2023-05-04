#pragma once

#include <memory>
#include <string>
#include <atomic>

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Buffer.h"
#include "TimeStamp.h"
#include "Callbacks.h"

class Channel;
class Socket;
class EventLoop;

class TcpConnection : Noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(EventLoop* loop,
		const std::string &name,
		const InetAddress &localAddr,
		const InetAddress &peerAddr,
		int sockfd);
	~TcpConnection();

private:
	EventLoop* myloop;
	const std::string myname;
	const InetAddress myLocalAddr;
	const InetAddress myPeerAddr;

	std::unique_ptr<Socket> socket;
	std::unique_ptr<Channel> channel;

	// 接收缓冲区
	Buffer inputBuffer;
	// 发送缓冲区
	Buffer outputBuffer;

	ConnectionCallback connectionCallback;
	MessageCallback messageCallback;
	WriteCompleteCallback writeCompleteCallback;
	HighWaterMarkCallback highWaterMarkCallback;
	CloseCallback closeCallback;
	size_t highWaterMark;

	enum State
	{
		Connected,
		Connecting,
		Disconnected,
		Disconnecting
	};

    void setState(State state) { mystate = state; }
	
	void handleRead(TimeStamp receiveTime);
	void handleWrite();
	void handleClose();
	void handleError();

	void sendInLoop(const void *data, size_t len);
	void shutdownInLoop();
	
	std::atomic_int mystate;

public:
	EventLoop* getLoop() const { return myloop; };
	const std::string& name() const { return myname; }
	const InetAddress& localAddress() const { return myLocalAddr; }
	const InetAddress& peerAddress() const { return myPeerAddr; }

	bool connected() const { return mystate == Connected; }

	void connectEstablished();
	void connectDestroyed();
	
	void send(const std::string &buf);
	void shutdown();

	void setConnectionCallback(const ConnectionCallback& cb) { connectionCallback = cb; }
	void setMessageCallback(const MessageCallback& cb) { messageCallback = cb; }
	void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback = cb; }
	void setCloseCallback(const CloseCallback& cb) { closeCallback = cb; }
	void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t HighWaterMark) 
	{ highWaterMarkCallback = cb; highWaterMark = HighWaterMark; }
};