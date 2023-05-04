#include "../include/CurrentThread.h"

namespace CurrentThread
{
	__thread int t_cachedTid = 0;

	void cacheTid()
	{
		if (t_cachedTid == 0)
		{
			// 间接系统调用
			t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
		}
	}
}