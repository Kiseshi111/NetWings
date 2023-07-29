#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

#include "../include/Buffer.h"

ssize_t Buffer::readFd(int fd, int* saveErrno)
{
	char extraBuf[65536] = { 0 };

	//在函数readv和writev的使用中，iov_base是struct iovec结构体的一个成员。
	//struct iovec是用于传递多个连续内存块的结构体，它定义如下
	//
	//struct iovec {
	//	void* iov_base; // 内存块的起始地址
	//	size_t iov_len; // 内存块的大小
	//};

	//在这里，iov_base是指向内存块的起始地址，它是一个指针类型（void* ），指向要读取或写入的数据所在的内存地址。

	//iov_len是内存块的大小，表示要读取或写入的数据的字节数。
	//通过iov_base和iov_len组合，可以描述一个内存块的位置和大小，从而实现读取或写入连续多个内存块的操作。

	//在函数readv和writev中，iov_base和iov_len一般通过一个数组struct iovec* 来传递，数组中的每个元素描述一个要读取或写入的内存块。
	//函数会按照数组中的顺序依次读取或写入这些内存块的数据。
	//这样的设计使得在进行大量数据的读取或写入时，可以通过一次调用函数实现，避免了多次系统调用带来的性能开销。

	struct iovec vec[2];

	const size_t writable = writableBytes();

	vec[0].iov_base = begin() + writerIndex;
	vec[0].iov_len = writable;

	vec[1].iov_base = extraBuf;
	vec[1].iov_len = sizeof(extraBuf);

	const int  iovcnt = (writable < sizeof(extraBuf)) ? 2 : 1;
	const ssize_t n = ::readv(fd, vec, iovcnt);

	if (n < 0)
	{
		*saveErrno = errno;
	}
	else if (n <= writable)
	{
		writerIndex += n;
	}
	else
	{
		writerIndex = buffer.size();
		append(extraBuf, n - writable);
	}
	return n;

}

ssize_t Buffer::writeFd(int fd, int* saveErrno)
{
	ssize_t n = ::write(fd, peek(), readableBytes());
	if (n < 0)
	{
		*saveErrno = errno;
	}
	return n;
}
