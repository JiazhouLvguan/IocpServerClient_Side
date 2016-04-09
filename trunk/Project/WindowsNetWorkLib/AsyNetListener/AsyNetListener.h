#pragma once

#include "../Observer/Subject.h"
#include "../DataStruct/Primitives.h"
#include "../DataStruct/IocpStruct.h"
#include "../AsyNetRemoteClient/AsyNetRemoteClient.h"


#include <mswsock.h>
#include <winsock2.h>


namespace nsIocpServerClientNet
{
	class CAsyNetListener :public AsyOperateBase, /* 从完成端口中取出数据进行操作 */ public CSubject, /*将连接用户作为自己的观察者*/ public IObserver /*作为连接用户的观察者*/
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
		CAsyNetListener(std::shared_ptr<IThreadPool> pThreadPool);				//外部创建的线程池 用于添加 套接字设备
		~CAsyNetListener();

	public:
		bool Operate(bool bRet, DWORD dwBytesTransfered, void* pParam);

		void OpenSocket(const char* pStrIP, const UINT nPort, const bool bTcp = true);
		void CloseSocket();
		void Listen();

		//用异常 代替返回值
		void ReturnAccpetCtx(LPPER_IO_CONTEXT &pIOCtx);
		void PostAcceptEx(LPPER_IO_CONTEXT &pIOCtx);
		void DoAcceptEx(LPPER_IO_CONTEXT &pIOCtx);
		
		void UpdateAcceptCtxList(CSmartSocketHandle* pRemoteSock);
		void Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2);
		void DoIOError(LPPER_IO_CONTEXT &pIOCtx);

	};
}

