#include <stdlib.h>

#include "../include/Poller.h"
#include "../include/EpollPoller.h"

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if (::getenv("MUDUO_USE_POLL"))
    {
        return nullptr; // ����poll��ʵ��
    }
    else
    {
        return new EpollPoller(loop); // ����epoll��ʵ��
    }
}