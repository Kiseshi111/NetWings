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

//inet_ntop是一个网络编程函数，用于将IPv4和IPv6的二进制地址转换成可读性更好的字符串表示形式(192.168.1.1)
//
//const char* inet_ntop(int af, const void* src, char* dst, socklen_t size);	
//
//参数说明：
//
//af：表示地址族（address family），可以是AF_INET（IPv4）或AF_INET6（IPv6）。
//src：指向存储二进制地址的缓冲区的指针。
//dst：用于存储转换后的可读性更好的字符串地址的缓冲区指针。
//size：dst缓冲区的大小。
//函数返回值：
//
//如果转换成功，则返回指向转换后的字符串地址的指针（即dst指针）。
//如果转换失败，函数返回NULL，并设置errno为相应的错误码。

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

