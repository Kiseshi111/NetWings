#pragma once

#include <functional>
#include <thread>
#include <string>
#include <memory>
#include <atomic>
#include <unistd.h>

#include "Noncopyable.h"

class Thread : Noncopyable
{
public:
	using ThreadFunc = std::function<void()>;

	explicit Thread(ThreadFunc, const std::string& name = std::string());
	~Thread();

private:
	bool started;
	bool joined;
	std::shared_ptr<std::thread> thread;
	pid_t tid;
	ThreadFunc myfunc;
	std::string myname;
	static std::atomic_int createdNum;
	
	void setDefaultName();

public:
	void start();
	void join();

	bool isStarted() { return started; }
	pid_t getTid() const { return tid; }
	const std::string& getName() const { return myname; }
	static int numCreated() { return createdNum; }
};
