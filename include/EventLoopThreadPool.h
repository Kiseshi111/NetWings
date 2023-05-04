#pragma once

#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "Noncopyable.h"

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : Noncopyable
{
public:
	using ThreadInitCallback = std::function<void(EventLoop*)>;

	EventLoopThreadPool(EventLoop *baseloop, const std::string &nameArg);
	~EventLoopThreadPool();

private:
	EventLoop* baseloop;
	std::string myname;
	bool started;
	int threadNum;
	int next;
	std::vector<std::unique_ptr<EventLoopThread>> threads;
	std::vector<EventLoop*> loops;

public:
	EventLoop* getNextLoop();
	std::vector<EventLoop*> getAllLoops();
	void setThread(int numThread) { threadNum = numThread; }
	void start(const ThreadInitCallback &cb = ThreadInitCallback());
	bool isStarted() const { return started; }
	const std::string name() const { return myname; }
};