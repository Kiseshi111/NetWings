#include <stdlib.h>

#include "../include/Channel.h"
#include "../include/Poller.h"


Poller::Poller(EventLoop* loop)
	:ownerloop(loop)
{

}

bool Poller::hasChannel(Channel* channel) const
{
	auto it = channels.find(channel->fd());
	return it != channels.end() && it->second == channel;
}