#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>

class InetAddress
{
public:
	explicit InetAddress(uint16_t port = 0, std::string ip = "127.0.0.1");
	explicit InetAddress(const sockaddr_in& addr)
		:myaddr(addr)
	{
	}

private:
	sockaddr_in myaddr;

public:
	std::string toIpPort() const;
	std::string toIp() const;
	uint16_t toPort() const;

	const sockaddr_in* getSockAddr() const { return &myaddr; }
	void setSockAddr(const sockaddr_in& addr) { myaddr = addr; }
};