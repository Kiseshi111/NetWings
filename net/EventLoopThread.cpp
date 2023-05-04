#include "../include/EventLoopThread.h"
#include "../include/EventLoop.h"

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
								 const std::string& name)
	:myloop(nullptr)
	,exiting(false)
	,mythread(std::bind(&EventLoopThread::threadFunc, this), name)
	,mutex()
	,cond()
	,callback(cb)
{
}

EventLoopThread::~EventLoopThread()
{
	exiting = true;
	if (myloop != nullptr)
	{
		myloop->quit();
		mythread.join();
	}
}

EventLoop* EventLoopThread::startLoop()
{
	// 开启底层线程
	mythread.start();

	EventLoop* loop = nullptr;
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (loop == nullptr)
		{
			cond.wait(lock);
		}
		loop = myloop;
	}
	return loop;
}

// thread对应唯一loop
void EventLoopThread::threadFunc()
{
	EventLoop loop;

	if (callback)
	{
		callback(&loop);
	}

	{
		std::unique_lock<std::mutex> lock(mutex);
		myloop = &loop;
		cond.notify_one();
	}
	// 开启底层poll() 开始事件监听
	loop.loop();
	std::unique_lock<std::mutex> lock(mutex);
	myloop = nullptr;
}