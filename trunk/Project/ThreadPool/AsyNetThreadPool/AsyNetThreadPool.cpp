#include "stdafx.h"
#include "AsyNetThreadPool.h"


namespace nsIocpServerClientNet
{
	CAsyNetThreadPool::CAsyNetThreadPool(){}
	CAsyNetThreadPool::~CAsyNetThreadPool(){}

	bool CAsyNetThreadPool::CreateThreadPool(int nThreadsNumber)
	{
		SYSTEM_INFO sysInfo = { 0 };
		GetSystemInfo(&sysInfo);

		if (!CreateIocp(nThreadsNumber))	throw CExceptionThreadPool("create Iocp Fail");
			
		
		int nThreads = sysInfo.dwNumberOfProcessors * 2;
		while (nThreadsNumber)
		{
			std::thread threadDotask(&CAsyNetThreadPool::DoTask,this);
			m_vecSmartThreadHandle.push_back(threadDotask.native_handle());
			threadDotask.detach();
		}

		return true;
	}

	void CAsyNetThreadPool::DoTask()
	{

	}
	
	void CAsyNetThreadPool::DestoryThreadPool()
	{
		for (int n = 0; n < m_vecSmartThreadHandle.size(); n++)
			PostQueuedCompletionStatus(m_hIocp, 0, IOCP_EXIT_FLAG, NULL);

		WaitForMultipleObjects(m_vecSmartThreadHandle.size(), m_vecSmartThreadHandle[0], TRUE, INFINITE);

	}

}