#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include "../include/Channel.h"
#include "../include/EpollPoller.h"

/*
	New：channel未添加到Poller
	Added：channel已添加到Poller
	Deleted：channel已从Poller删除
*/ 
const int New = -1;
const int Added = 1;
const int Deleted = 2;

// ?
EpollPoller::EpollPoller(EventLoop* loop)
	:Poller(loop)
	,epoll_fd(::epoll_create1(EPOLL_CLOEXEC))
	,events(InitEventListSize)
{
	if (epoll_fd < 0)
	{
		printf("epoll_create error : %d \n", errno);
	}
	else
	{
		printf("epoll_fd %d create succeed\n", epoll_fd);
	}
}

EpollPoller::~EpollPoller()
{
	::close(epoll_fd);
}

TimeStamp EpollPoller::poll(int timeout, ChannelList* activeChannels)
{
	printf("func is %s => fd total count : %lu\n", __FUNCTION__, channels.size());

	int eventNum = ::epoll_wait(epoll_fd, &*events.begin(), static_cast<int>(events.size()), timeout);
	int saveErrno = errno;

	TimeStamp now(TimeStamp::now());

	if (eventNum > 0)
	{
		printf("%d events happend\n", eventNum); 
		fillActiveChannels(eventNum, activeChannels);

		if (eventNum == events.size())
		{
			events.resize(events.size() * 2);
		}
	}
	else if (eventNum == 0)
	{
		printf("%s timeout!\n", __FUNCTION__);
	}
	else 
	{
		if (saveErrno != EINTR)
		{
			errno = saveErrno;
			printf("EPollPoller::poll() error: %d\n", saveErrno);
		}
	}
	return now;
}

void EpollPoller::updateChannel(Channel* channel)
{
	const int flags = channel->flag();
	printf("func is %s => fd = %d event = %d flag = %d\n", __FUNCTION__, channel->fd(), channel->event(), flags);

	if (flags == New || flags == Deleted)
	{
		if (flags == New)
		{
			int fd = channel->fd();
			channels[fd] = channel;
		}
		else
		{
		}
		channel->setFlags(Added);
		update(EPOLL_CTL_ADD, channel);
	}
	else
	{
		int fd = channel->fd();
		if (channel->isNoneEvent())
		{
			update(EPOLL_CTL_DEL, channel);
			channel->setFlags(Deleted);
		}
		else
		{
			update(EPOLL_CTL_MOD, channel);
		}
	}
}

void EpollPoller::removeChannel(Channel* channel)
{
	int fd = channel->fd();
	channels.erase(fd);

	printf("func is %s => fd = %d\n", __FUNCTION__, fd);

	int flags = channel->flag();
	if (flags == Added)
	{
		update(EPOLL_CTL_DEL, channel);
	}
	channel->setFlags(New);
}

void EpollPoller::fillActiveChannels(int eventNum, ChannelList* activeChannels) const
{
	for (int i = 0; i < eventNum; ++i)
	{
		Channel* channel = static_cast<Channel*>(events[i].data.ptr);
		channel->setRevent(events[i].events);
		activeChannels->push_back(channel);
	}
}

void EpollPoller::update(int operation, Channel* channel)
{
	epoll_event event;
	::memset(&event, 0, sizeof(event));

	int fd = channel->fd();

	if (fd < 0) {
		printf("invalid file descriptor\n");
		return;
	}

	// 使用EPOLLONESHOT标志确保每个channel只被唤醒一次，从而避免竞争条件
	// event.events = channel->event() | EPOLLONESHOT;
	event.events = channel->event();
	event.data.fd = fd;
	event.data.ptr = channel;

	if (::epoll_ctl(epoll_fd, operation, fd, &event) < 0)
	{
		if (operation == EPOLL_CTL_DEL)
		{
			printf("epoll_ctl del error : %d\n", errno);
		}
		else if(operation == EPOLL_CTL_ADD)
		{
			printf("epoll_ctl add error : %d\n", errno);
		}
		else if(operation == EPOLL_CTL_MOD)
		{
			printf("epoll_ctl mod error : %d\n", errno);
		}
	}
}