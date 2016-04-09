#pragma once

#include "../Observer/Subject.h"
#include "../DataStruct/Primitives.h"
#include "../DataStruct/IocpStruct.h"
#include "../AsyNetRemoteClient/AsyNetRemoteClient.h"


#include <mswsock.h>
#include <winsock2.h>


namespace nsIocpServerClientNet
{
	class CAsyNetListener :public AsyOperateBase, /* ����ɶ˿���ȡ�����ݽ��в��� */ public CSubject, /*�������û���Ϊ�Լ��Ĺ۲���*/ public IObserver /*��Ϊ�����û��Ĺ۲���*/
	{
	private:	
		CSmartSocketHandle				m_listenerSocket;
		
		std::shared_ptr<IThreadPool>	m_pThreadPool;

		CCriticalMutex  m_criticalMutexLock;

		LPFN_ACCEPTEX                        m_lpfnAcceptEx;;

		LPFN_GETACCEPTEXSOCKADDRS            m_lpfnGetAcceptExSockAddrs;

		LPFN_DISCONNECTEX					 m_lpfnDisconnectEx;

		std::list<std::unique_ptr<PER_IO_CONTEXT>>  m_lstReuseAcceptCtx;

		std::list<std::unique_ptr<PER_IO_CONTEXT>>  m_lstCurrentUseAcceptCtx;

	public:
		CAsyNetListener(std::shared_ptr<IThreadPool> pThreadPool);				//�ⲿ�������̳߳� ������� �׽����豸
		~CAsyNetListener();

	public:
		bool Operate(bool bRet, DWORD dwBytesTransfered, void* pParam);

		void OpenSocket(const char* pStrIP, const UINT nPort, const bool bTcp = true);
		void CloseSocket();
		void Listen();

		//���쳣 ���淵��ֵ
		void ReturnAccpetCtx(LPPER_IO_CONTEXT &pIOCtx);
		void PostAcceptEx(LPPER_IO_CONTEXT &pIOCtx);
		void DoAcceptEx(LPPER_IO_CONTEXT &pIOCtx);
		
		void UpdateAcceptCtxList(CSmartSocketHandle* pRemoteSock);
		void Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2);
		void DoIOError(LPPER_IO_CONTEXT &pIOCtx);

	};
}

