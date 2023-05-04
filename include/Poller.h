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
	
	// 防止内存泄露
	virtual ~Poller() = default;

	ChannelMap channels;

private:	
	EventLoop* ownerloop;

public:
	virtual TimeStamp poll(int timeout, ChannelList* activeChannels) = 0;
	virtual void updateChannel(Channel *channel) = 0;
	virtual void removeChannel(Channel *channel) = 0;

	/*
		类的成员有两种，静态成员和实例成员
		不同实例同名成员有不同的存储空间，静态成员存储空间固定
		若想通过类直接访问成员，而非通过对象访问的话
		则需要将成员声明为静态static，成员函数亦是如此
	*/ 
	static Poller* newDefaultPoller(EventLoop* loop);

	bool hasChannel(Channel* channel) const;
};