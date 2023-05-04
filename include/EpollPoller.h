#pragma once

#include <vector>
#include <sys/epoll.h>

#include "TimeStamp.h"
#include "Poller.h"

class Channel;

class EpollPoller : public Poller
{
public:
	EpollPoller(EventLoop *loop);
	~EpollPoller() override;
	
private:
	using EventList = std::vector<epoll_event>;

	int epoll_fd;
	EventList events;
	static const int InitEventListSize = 16;

	void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
	void update(int operation, Channel* channel);

public:
	TimeStamp poll(int timeout, ChannelList* activeChannels) override;

	void updateChannel(Channel* channel) override;
	void removeChannel(Channel* channel) override;

};