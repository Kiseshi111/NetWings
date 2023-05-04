#include "../include/Thread.h"
#include "../include/CurrentThread.h"

#include <semaphore.h>

std::atomic_int Thread::createdNum(0);

Thread::Thread(ThreadFunc func, const std::string& name)
	:started(false)
	,joined(false)
	,tid(0)
	,myfunc(std::move(func))
	,myname(name)
{
	setDefaultName();
}

Thread::~Thread()
{
	if (started && !joined)
	{
		// 分离父子线程 子线程运行后自动销毁
		thread->detach();
	}
}

void Thread::start()
{
	started = true;
	sem_t sem;
	// false: 进程间不共享该变量
	sem_init(&sem, false, 0);
	thread = std::shared_ptr<std::thread>(new std::thread([&]() {
		tid = CurrentThread::tid();
		sem_post(&sem);
		myfunc();
		}));

	sem_wait(&sem);
}

void Thread::join()
{
	joined = true;
	thread->join();
}

void Thread::setDefaultName()
{
	int num = ++createdNum;
	if (myname.empty())
	{
		char buf[32] = { 0 };
		snprintf(buf, sizeof buf, "Thread%d", num);
		myname = buf;
	}
}