#include <sys/epoll.h>

#include "../include/Channel.h"
#include "../include/EventLoop.h"

/*
	EPOLLIN :��ʾ��Ӧ���ļ����������Զ�
	EPOLLOUT:��ʾ��Ӧ���ļ�����������д
	EPOLLPRI:��ʾ��Ӧ���ļ��������н��������ݿɶ�
	EPOLLERR:��ʾ��Ӧ���ļ���������������
	EPOLLHUP:��ʾ��Ӧ���ļ����������Ҷ�
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
	// ��
	if (revents & (EPOLLIN | EPOLLPRI))
	{
		if (readcallback)
		{
			readcallback(receiveTime);
		}
	}
	// д
	if (revents & EPOLLOUT)
	{
		if (writecallback)
		{
			writecallback();
		}
	}
	// ����
	if (revents & EPOLLERR)
	{
		if (errorcallback)
		{
			errorcallback();
		}
	}
	// �ر�
	if ((revents & EPOLLHUP) && !(revents & EPOLLIN))
	{
		if (closecallback)
		{
			closecallback();
		}
	}
}