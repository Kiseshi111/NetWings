#include <memory>

#include "../include/EventLoopThreadPool.h"
#include "../include/EventLoopThread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& nameArg)
	:baseloop(baseLoop)
	,myname(nameArg)
	,started(false)
	,threadNum(0)
	,next(0)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
	
}
 
void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
	started = true;

	for (int i = 0; i < threadNum; ++i)
	{
		char buf[myname.size() + 32];
		// 为线程设置带编号的名称
		snprintf(buf, sizeof(buf), "%s%d", myname.c_str(), i);
		EventLoopThread* t = new EventLoopThread(cb, buf);
		threads.push_back(std::unique_ptr<EventLoopThread>(t));
		loops.push_back(t->startLoop());
	}

	if (threadNum == 0 && cb)
	{
		cb(baseloop);
	}
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
	EventLoop* loop = baseloop;

	// 轮询分配subloop
	if (!loops.empty())
	{
		loop = loops[next];
		++next;
		if (next >= loops.size())
		{
			next = 0;
		}
	}

	return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
	if (loops.empty())
	{
		return std::vector<EventLoop*>(1, baseloop);
	}
	else
	{
		return loops;
	}
}