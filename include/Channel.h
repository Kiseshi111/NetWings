#pragma once

#include <functional>
#include <memory>

#include "Noncopyable.h"
#include "TimeStamp.h"

class EventLoop;

class Channel : Noncopyable
{
public:
	using EventCallback = std::function<void()>; // muduo仍使用typedef
	using ReadEventCallback = std::function<void(TimeStamp)>;

	Channel(EventLoop* loop, int fd);
	~Channel();

private:
	const int myfd;
	EventLoop* myloop;

	int flags;
	int events;
	int revents;

	static const int NoneEvent;
	static const int ReadEvent;
	static const int WriteEvent;

	ReadEventCallback readcallback;
	EventCallback writecallback;
	EventCallback closecallback;
	EventCallback errorcallback;

	std::weak_ptr<void> extend;
	bool extended;

	void update();
	void handleEventWithGuard(TimeStamp receiveTime);

public:
	void setReadCallback(ReadEventCallback cb) { readcallback = std::move(cb); }
	void setWriteCallback(EventCallback cb) { writecallback = std::move(cb); }
	void setCloseCallback(EventCallback cb) { closecallback = std::move(cb); }
	void setErrorCallback(EventCallback cb) { errorcallback = std::move(cb); }

	// events初始为0，|= 与 &=~ 互为逆运算，前者将events设置为ReadEvent的值
	void enableReading() { events |= ReadEvent; update(); }
	void disableReading() { events &= ~ReadEvent; update(); }
	void enableWriting() { events |= WriteEvent; update(); }
	void disableWriting() { events &= ~WriteEvent; update(); }
	void disabelAll() { events = NoneEvent; update(); }

	/*
		== 判断与 & 判断实际意义相同
		等于运算是比较十进制int值，按位与运算是二进制位都为1则为1，速度更快
		bool isNoneEvent() const { return events == NoneEvent; }
	*/
	bool isNoneEvent() const { return events == NoneEvent; }
	bool isWriting() const { return events & WriteEvent; }
	bool isReading() const { return events & ReadEvent; }

	void handleEvent(TimeStamp receiveTime);

	int fd() const { return myfd; }
	int event() const { return events; }

	int flag() { return flags; }
	void setFlags(int flag) { flags = flag; }

	EventLoop* ownerLoop() { return myloop; }
	void setRevent(int revent) { revents = revent; }

	void remove();
	void doExtend(const std::shared_ptr<void> &);

};