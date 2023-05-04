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
	// �����ײ��߳�
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

// thread��ӦΨһloop
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
	// �����ײ�poll() ��ʼ�¼�����
	loop.loop();
	std::unique_lock<std::mutex> lock(mutex);
	myloop = nullptr;
}