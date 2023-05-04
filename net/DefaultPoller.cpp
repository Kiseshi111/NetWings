#include <stdlib.h>

#include "../include/Poller.h"
#include "../include/EpollPoller.h"

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if (::getenv("MUDUO_USE_POLL"))
    {
        return nullptr; // 生成poll的实例
    }
    else
    {
        return new EpollPoller(loop); // 生成epoll的实例
    }
}