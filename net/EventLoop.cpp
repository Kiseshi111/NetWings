#include <sys/eventfd.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>

#include "../include/EventLoop.h"
#include "../include/Channel.h"
#include "../include/Poller.h"

__thread EventLoop* loopInThisThread = nullptr;

// io复用接口超时时间
const int pollTimeMs = 10000;

int createEventfd()
{
	int event_fd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if (event_fd < 0)
	{
		printf("event_fd error : %d", errno);
	}
	return event_fd;
}

EventLoop::EventLoop()
	:looping(false)
	,quitted(false)
	,callingPendingFunctors(false)
	,threadId(CurrentThread::tid()) 
	,wakeupFd(createEventfd())
	,wakeupChannel(new Channel(this, wakeupFd))
	,poller(Poller::newDefaultPoller(this))
{
	printf("EventLoop created %p in thread %d\n", this, threadId);
	if (loopInThisThread)
	{
		// 不做处理
		printf("Another EventLoop %p exists in this thread %d\n", loopInThisThread, threadId);
	}
	else
	{
		loopInThisThread = this;
	}

	wakeupChannel->setReadCallback(
		std::bind(&EventLoop::handleRead, this));

	wakeupChannel->enableReading();
}

EventLoop::~EventLoop()
{
	wakeupChannel->disabelAll();
	wakeupChannel->remove();
	::close(wakeupFd);
	loopInThisThread = nullptr;
}

void EventLoop::loop()
{
	looping = true;
	quitted = false;

	printf("EventLoop %p start looping\n", this);

	while (!quitted)
	{
		// 清空活跃channel
		activeChannels.clear();
		pollreturetime = poller->poll(pollTimeMs, &activeChannels);

		// 通知每个发生事件的channel处理相应事件
		for (Channel* channel : activeChannels)
		{
			channel->handleEvent(pollreturetime);
		}
		doPendingFunctors();
	}
	printf("EventLoop %p stop looping.\n", this);
	looping = false;
}

void EventLoop::quit()
{
	quitted = true;

	// 若不在当前线程，则唤醒EventLoop所属线程epoll_wait
	if (!isInLoopThread())
	{
		wakeup();
	}
}

void EventLoop::runInLoop(Functor cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInLoop(cb);
	}
}

void EventLoop::queueInLoop(Functor cb)
{
	// unique_lock类模板，在构造时获取锁，析构时释放锁
	// 所以lock对象在作用域外自动析构释放锁
	{
		std::unique_lock<std::mutex> lock(mutex);
		pendingFunctors.emplace_back(cb);
	}

	if (!isInLoopThread() || callingPendingFunctors)
	{
		wakeup();
	}
}

// 写入一个数据wakeupChannel就会发生读事件，当前EventLoop线程就会被唤醒
void EventLoop::wakeup()
{
	uint64_t one = 1;
	ssize_t n = write(wakeupFd, &one, sizeof(one));
	if (n != sizeof(one))
	{
		printf("EventLoop::wakeup() writes %lu bytes instead of 8\n", n);
	}
}


void EventLoop::updateChannel(Channel* channel)
{
	poller->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
	poller->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel)
{
	return poller->hasChannel(channel);
}

void EventLoop::handleRead()
{
	uint64_t one = 1;
	ssize_t n = read(wakeupFd, &one, sizeof(one));
	if (n != sizeof(one))
	{
		printf("EventLoop::handleRead() reads %lu bytes instead of 8\n", n);
	}
}

void EventLoop::doPendingFunctors()
{
	std::vector<Functor> functors;
	callingPendingFunctors = true;

	{
		std::unique_lock<std::mutex> lock(mutex);
		functors.swap(pendingFunctors);
	}

	for(const Functor &functor : functors)
	{
		functor();
	}
	callingPendingFunctors = false;
}