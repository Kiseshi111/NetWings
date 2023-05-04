#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sys/types.h>
#include <stddef.h>

class Buffer
{
public:
	static const size_t CheapPrepend = 8;
	static const size_t InitialSize = 1024;

public:
	explicit Buffer(size_t initalSize = InitialSize)
		:buffer(CheapPrepend + initalSize)
		,readerIndex(CheapPrepend)
		,writerIndex(CheapPrepend)
	{
	}

private:
	std::vector<char> buffer;
	size_t readerIndex;
	size_t writerIndex;
	
	char* begin() { return &*buffer.begin(); }
	const char* begin() const { return &*buffer.begin(); }

	void makeSpace(size_t len)
	{
		if (writableBytes() + prependableBytes() < len + CheapPrepend)
		{
			buffer.resize(writerIndex + len);
		}
		// 数据移动
		else
		{
			size_t readable = readableBytes();
			std::copy(begin() + readerIndex,
					  begin() + writerIndex,
					  begin() + CheapPrepend);
			readerIndex = CheapPrepend;
			writerIndex = readerIndex + readable;
		}
	}

public:
	void append(const char* data, size_t len)
	{
		// 放入数据前先确保可写空间足够
		ensureWriteableBytes(len);
		std::copy(data, data + len, beginWrite());
		writerIndex += len;
	}

	char* beginWrite() { return begin() + writerIndex; }
	const char* beginWrite() const { return begin() + writerIndex; }

	// 检索数据长度 若不超过可读长度则可读索引增加
	void retrieve(size_t len)
	{
		if (len < readableBytes())
		{
			readerIndex += len;
		}
		else
		{
			retrieveAll();
		}
	}

	// 否则可读可写索引返回初始值
	void retrieveAll()
	{
		readerIndex = CheapPrepend;
		writerIndex = CheapPrepend;
	}

	std::string retrieveAsString(size_t len)
	{
		std::string result(peek(), len);
		retrieve(len);
		return result;
	}
	std::string retrieveAllString() { return retrieveAsString(readableBytes()); }
	void ensureWriteableBytes(size_t len)
	{
		// 不满足可写长度则扩容
		if (writableBytes() < len)
		{
			makeSpace(len);
		}
	}

	ssize_t readFd(int fd, int* saveErrno);
	ssize_t writeFd(int fd, int* saevErrno);

	size_t readableBytes() const { return writerIndex - readerIndex; }
	size_t writableBytes() const { return buffer.size() - writerIndex; }
	size_t prependableBytes() const { return readerIndex; }

	const char* peek() const { return begin() + readerIndex; }
};