#pragma once

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread
{
	// ����tid���� Ϊ����ϵͳ���ú�ʱ
	// __thread��֤ÿ���߳���һ�ݶ���ʵ�� ������tid
	extern __thread int t_cachedTid;

	void cacheTid();

	// ��������ֻ�ڵ�ǰ�ļ���������
	inline int tid()
	{
		// �����δ��ȡtid �����if ͨ��cacheTid()ϵͳ���û�ȡtid
		if (__builtin_expect(t_cachedTid == 0, 0))
		{
			cacheTid();
		}
		return t_cachedTid;
	}
};