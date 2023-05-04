#include <string.h>
#include <strings.h>

#include "../include/InetAddress.h"

InetAddress::InetAddress(uint16_t port, std::string ip)
{
	::memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = ::htons(port);
	myaddr.sin_addr.s_addr = ::inet_addr(ip.c_str());
}

std::string InetAddress::toIp() const
{
	char buf[64] = { 0 };
	::inet_ntop(AF_INET, &myaddr.sin_addr, buf, sizeof buf);
	return buf;
}

std::string InetAddress::toIpPort() const
{
	char buf[64] = { 0 };
	::inet_ntop(AF_INET, &myaddr.sin_addr, buf, sizeof buf);
	size_t end = ::strlen(buf);
	uint16_t port = ::ntohs(myaddr.sin_port);
	// 将port加在ip后
	sprintf(buf + end, ":%u", port);
	return buf;
}

uint16_t InetAddress::toPort() const
{
	return ::ntohs(myaddr.sin_port);
}

