#include "stdafx.h"
#include "AsyNetThreadPool.h"


namespace nsIocpServerClientNet
{
	CAsyNetThreadPool::CAsyNetThreadPool(){}
	CAsyNetThreadPool::~CAsyNetThreadPool()
	{
		//�����߳�
		int nSize = m_vecpthread.size();
		for (int n = 0; n < nSize; n++)
		{
			//ʵ���� �߳��Ѿ����н���  deatch ֻ�ǽ��߳� ���� ���п�ȥ����
			m_vecpthread[n]->detach();
			delete m_vecpthread[n];
		}
	}

	bool CAsyNetThreadPool::CreateThreadPool(int nThreadsNumber)
	{
		SYSTEM_INFO sysInfo = { 0 };
		GetSystemInfo(&sysInfo);

		if (!CreateIocp(nThreadsNumber))	throw CExceptionThreadPool("create Iocp Fail");
			
		
		int nThreads = sysInfo.dwNumberOfProcessors * 2;
		while (nThreadsNumber--)
		{
			std::thread* pthreadDotask = new std::thread(&CAsyNetThreadPool::DoTask,this);

			m_vecpthread.push_back(pthreadDotask);
			//m_vecHandle.push_back(pthreadDotask->native_handle());
		}

		return true;
	}

	void CAsyNetThreadPool::DoTask()
	{
		//�̳߳� ��   ��ɶ˿���ȡ������ Ȼ�� ִ�ж������
	
		while (true)
		{
			OVERLAPPED           *pOverlapped = NULL;
			LPPER_IO_CONTEXT     pSockCtx = NULL;
			DWORD                dwBytesTransfered = 0;
			LONG_PTR		     nCompleteKey = 0;

			BOOL bRet = GetQueuedCompletionStatus(m_hIocp,
				&dwBytesTransfered,
				(PULONG_PTR)&nCompleteKey,
				&pOverlapped,
				INFINITE);

			
			if (nCompleteKey != NULL && nCompleteKey == IOCP_EXIT_FLAG)
			{
				///< IOCP �˳���ʶ
				break;
			}

			if (pOverlapped == NULL && !bRet)
			{
				continue;
			}

			if (pOverlapped != NULL)
			{
				pSockCtx = CONTAINING_RECORD(pOverlapped, PER_IO_CONTEXT, overLapped);
				if (!pSockCtx->pAsyOperate->Operate(bRet, dwBytesTransfered, (void*)pSockCtx))
				{
					delete pSockCtx;
					pSockCtx = NULL;
				}
			}
		}
	}
	
	void CAsyNetThreadPool::DestoryThreadPool()
	{
		int nThreadNum = m_vecpthread.size();

		for (int n = 0; n < nThreadNum; n++)
			PostQueuedCompletionStatus(m_hIocp, 0, IOCP_EXIT_FLAG, NULL);
		
		for (int n = 0; n < nThreadNum; n++)
		{
			m_vecpthread[n]->join();
			delete m_vecpthread[n];
			m_vecpthread[n] = NULL;
		}
	}

}