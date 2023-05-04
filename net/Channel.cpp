#include <sys/epoll.h>

#include "../include/Channel.h"
#include "../include/EventLoop.h"

/*
	EPOLLIN :表示对应的文件描述符可以读
	EPOLLOUT:表示对应的文件描述符可以写
	EPOLLPRI:表示对应的文件描述符有紧急的数据可读
	EPOLLERR:表示对应的文件描述符发生错误
	EPOLLHUP:表示对应的文件描述符被挂断
*/
const int Channel::ReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::WriteEvent = EPOLLOUT;
const int Channel::NoneEvent = 0;

Channel::Channel(EventLoop* loop, int fd)
	:myloop(loop)
	,myfd(fd)
	,events(0)
	,revents(0)
	,extended(false)
	,flags(-1)
{

}

Channel::~Channel()
{

}

void Channel::update()
{
	myloop->updateChannel(this);
}

void Channel::remove()
{
	myloop->removeChannel(this);
}

void Channel::doExtend(const std::shared_ptr<void>& obj)
{
	extend = obj;
	extended = true;
}

void Channel::handleEvent(TimeStamp receiveTime)
{
	if (extended)
	{
		std::shared_ptr<void> guard = extend.lock();
		if (guard)
		{
			handleEventWithGuard(receiveTime);
		}
	}
	else
	{
		handleEventWithGuard(receiveTime);
	}
}

void Channel::handleEventWithGuard(TimeStamp receiveTime)
{
	// 读
	if (revents & (EPOLLIN | EPOLLPRI))
	{
		if (readcallback)
		{
			readcallback(receiveTime);
		}
	}
	// 写
	if (revents & EPOLLOUT)
	{
		if (writecallback)
		{
			writecallback();
		}
	}
	// 错误
	if (revents & EPOLLERR)
	{
		if (errorcallback)
		{
			errorcallback();
		}
	}
	// 关闭
	if ((revents & EPOLLHUP) && !(revents & EPOLLIN))
	{
		if (closecallback)
		{
			closecallback();
		}
	}
}