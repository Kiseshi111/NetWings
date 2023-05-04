#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <mutex>
#include <memory>

#include "Noncopyable.h"
#include "CurrentThread.h"
#include "TimeStamp.h"

class Poller;
class Channel;

class EventLoop : Noncopyable
{
public:
	using Functor = std::function<void()>;

	EventLoop();
	~EventLoop();

private:
	using ChannelList = std::vector<Channel*>;

	std::atomic_bool looping;
	std::atomic_bool quitted;
	std::atomic_bool callingPendingFunctors;
	std::vector<Functor> pendingFunctors;

	std::unique_ptr<Poller> poller;
	TimeStamp pollreturetime;

	const pid_t threadId;
	int wakeupFd;
	std::unique_ptr<Channel> wakeupChannel;

	std::mutex mutex;

	ChannelList activeChannels;
	
	void handleRead();
	void doPendingFunctors();

public:
	void loop();
	void quit();

	TimeStamp pollRetureTime() const { pollreturetime; }

	void runInLoop(Functor cb);
	void queueInLoop(Functor cb);

	void wakeup();

	void updateChannel(Channel*channel);
	void removeChannel(Channel*channel);
	bool hasChannel(Channel* channel);

	
	// 为什么CurrentThread要用命名空间
	bool isInLoopThread() const { return threadId == CurrentThread::tid(); }
};