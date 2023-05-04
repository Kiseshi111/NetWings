#pragma once

#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>

#include "Noncopyable.h"
#include "Thread.h"

class EventLoop;

class EventLoopThread : Noncopyable
{
public:
	using ThreadInitCallback = std::function<void(EventLoop*)>;

	EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(),
		const std::string &name = std::string());
	~EventLoopThread();

private:
	EventLoop* myloop;
	Thread mythread;
	bool exiting;
	std::mutex mutex;
	std::condition_variable cond;
	ThreadInitCallback callback;
	
	void threadFunc();

public:
	EventLoop* startLoop();
};