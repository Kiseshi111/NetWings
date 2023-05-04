#pragma once

#include <vector>
#include <unordered_map>

#include "Noncopyable.h"
#include "TimeStamp.h"

class Channel;
class EventLoop;

class Poller
{
public:
	using ChannelList = std::vector<Channel*>;
	using ChannelMap = std::unordered_map<int, Channel*>;

	Poller(EventLoop* loop);
	
	// ��ֹ�ڴ�й¶
	virtual ~Poller() = default;

	ChannelMap channels;

private:	
	EventLoop* ownerloop;

public:
	virtual TimeStamp poll(int timeout, ChannelList* activeChannels) = 0;
	virtual void updateChannel(Channel *channel) = 0;
	virtual void removeChannel(Channel *channel) = 0;

	/*
		��ĳ�Ա�����֣���̬��Ա��ʵ����Ա
		��ͬʵ��ͬ����Ա�в�ͬ�Ĵ洢�ռ䣬��̬��Ա�洢�ռ�̶�
		����ͨ����ֱ�ӷ��ʳ�Ա������ͨ��������ʵĻ�
		����Ҫ����Ա����Ϊ��̬static����Ա�����������
	*/ 
	static Poller* newDefaultPoller(EventLoop* loop);

	bool hasChannel(Channel* channel) const;
};