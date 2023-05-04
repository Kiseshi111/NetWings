#pragma once

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread
{
	// 保存tid缓存 为减少系统调用耗时
	// __thread保证每个线程有一份独立实体 即独立tid
	extern __thread int t_cachedTid;

	void cacheTid();

	// 内联函数只在当前文件中起作用
	inline int tid()
	{
		// 如果还未获取tid 则进入if 通过cacheTid()系统调用获取tid
		if (__builtin_expect(t_cachedTid == 0, 0))
		{
			cacheTid();
		}
		return t_cachedTid;
	}
};