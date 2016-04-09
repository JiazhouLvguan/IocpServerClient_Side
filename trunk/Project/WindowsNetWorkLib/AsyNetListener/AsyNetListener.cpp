#include "stdafx.h"
#include "AsyNetListener.h"


namespace nsIocpServerClientNet
{
	
	CAsyNetListener::CAsyNetListener(std::shared_ptr<IThreadPool> pThreadPool)
		:m_pThreadPool(pThreadPool)
		, m_lpfnAcceptEx(NULL)
		, m_lpfnGetAcceptExSockAddrs(NULL)
		, m_lpfnDisconnectEx(NULL)
	{
		
	}
	CAsyNetListener::~CAsyNetListener()
	{
	
	}
	bool CAsyNetListener::Operate(bool bRet, DWORD dwBytesTransfered, void* pParam)
	{

		LPPER_IO_CONTEXT pIOCtx = (LPPER_IO_CONTEXT)pParam;
		assert(pIOCtx != NULL);

		if (bRet)
		{
			if (0 != dwBytesTransfered)
			{
				DoAcceptEx(pIOCtx);
				
				PER_IO_CONTEXT* pAcceptCtx = NULL;
				ReturnAccpetCtx(pAcceptCtx);
				PostAcceptEx(pAcceptCtx);
				
			}
			else
				PostAcceptEx(pIOCtx);
		}
		return true;
	}

	void CAsyNetListener::OpenSocket(const char* pStrIP, const UINT nPort, const bool bTcp)
	{
		CloseSocket();
		m_listenerSocket = WSASocket(AF_INET, bTcp ? SOCK_STREAM : SOCK_DGRAM, bTcp ? IPPROTO_TCP : IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
		
		if (!m_listenerSocket.CheckIsValid())		
			throw CExceptionSocket("Listener Create inValid Socket");

		sockaddr_in server;
		memset(&server, 0, sizeof(sockaddr_in));
		server.sin_family = AF_INET;
		if (NULL != pStrIP)
			server.sin_addr.s_addr = inet_addr(pStrIP);
		else
			server.sin_addr.s_addr = htonl(INADDR_ANY);
		server.sin_port = htons(nPort);

		if (SOCKET_ERROR == bind(m_listenerSocket, (SOCKADDR*)&server, sizeof(server)))
			throw CExceptionSocket("listener Bind Error");
	}

	void CAsyNetListener::CloseSocket()
	{
		if (m_listenerSocket.CheckIsValid())
		{
			shutdown(m_listenerSocket, SD_BOTH);
			m_listenerSocket.FreeHandle();

			CCriticalMutexWapper criticalMutexWapper(m_criticalMutexLock);
			m_lstReuseAcceptCtx.clear();
			m_lstCurrentUseAcceptCtx.clear();
		}
	}

	void CAsyNetListener::Listen()
	{
		if (SOCKET_ERROR == listen(m_listenerSocket, SOMAXCONN))
			throw CExceptionSocket("listener listen error");

		
		std::shared_ptr<CAsyNetThreadPool> pAsyNetThreadPool = std::static_pointer_cast<CAsyNetThreadPool>(m_pThreadPool);
		
		// 将自己 放入完成端口
		if (!pAsyNetThreadPool->AssociateWithIOCP(&m_listenerSocket, (ULONG_PTR)0))
			throw CExceptionThreadPool("associate with iocp error");
		
		GUID GuidAcceptEx = WSAID_ACCEPTEX;
		GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
		GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
		
		LOAD_WINSOCK2_FUNC(m_listenerSocket, GuidAcceptEx, m_lpfnAcceptEx);
		DWORD dwError = WSAGetLastError();
		LOAD_WINSOCK2_FUNC(m_listenerSocket, GuidGetAcceptExSockAddrs, m_lpfnGetAcceptExSockAddrs);
		LOAD_WINSOCK2_FUNC(m_listenerSocket, GuidDisconnectEx, m_lpfnDisconnectEx);

		
		for (int i = 0; i < ACCEPT_NUM; ++i)
		{
			///< 新建一个PER_IO_CONTEXT
			PER_IO_CONTEXT* pAcceptCtx = NULL;

			ReturnAccpetCtx(pAcceptCtx);

			PostAcceptEx(pAcceptCtx);
		}
	}
	
	void CAsyNetListener::ReturnAccpetCtx(PER_IO_CONTEXT*	&pIOCtx)
	{
		CCriticalMutexWapper lock(m_criticalMutexLock);
		if (0 != m_lstReuseAcceptCtx.size())
		{
			auto pAcceptCtx = m_lstReuseAcceptCtx.begin();
			
			//m_lstCurrentUseAcceptCtx.push_back(std::move(std::unique_ptr<PER_IO_CONTEXT>(pAcceptCtx->get())));
			m_lstCurrentUseAcceptCtx.push_back(std::move(*pAcceptCtx));
			m_lstReuseAcceptCtx.pop_front();

			pIOCtx = (m_lstCurrentUseAcceptCtx.back()).get();
		}
		else
		{
			pIOCtx = new PER_ACCEPT_CONTEXT(this);

			m_lstCurrentUseAcceptCtx.push_back(std::unique_ptr<PER_IO_CONTEXT>(pIOCtx));
		}
	}

	void CAsyNetListener::PostAcceptEx(PER_IO_CONTEXT* &pIOCtx)
	{
		auto pAcceptCtx = dynamic_cast<PER_ACCEPT_CONTEXT*>(pIOCtx);
		assert(pAcceptCtx != NULL);

		if (INVALID_SOCKET == pAcceptCtx->sAcceptSocket)
		{
			pAcceptCtx->sAcceptSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
				NULL, 0, WSA_FLAG_OVERLAPPED);

			if (INVALID_SOCKET == pAcceptCtx->sAcceptSocket)
				throw CExceptionSocket("create invalid socket");
		}
		else
			//重新使用 socket
			this->m_lpfnDisconnectEx((pAcceptCtx->sAcceptSocket), NULL, TF_REUSE_SOCKET, 0);
		
		DWORD dwBytes = 0;
		
		auto nRet = m_lpfnAcceptEx(m_listenerSocket, pAcceptCtx->sAcceptSocket, pAcceptCtx->data,
			pAcceptCtx->wbuf.len - ((sizeof(SOCKADDR_IN) + 16) * 2), sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16, &dwBytes, &pAcceptCtx->overLapped);
		
		if (!nRet && WSA_IO_PENDING != WSAGetLastError())
			throw CExceptionSocket("create accept socket failed");
	}

	void CAsyNetListener::DoAcceptEx(LPPER_IO_CONTEXT &pIOCtx)
	{
		LPPER_ACCEPT_CONTEXT pAcceptCtx = dynamic_cast<LPPER_ACCEPT_CONTEXT>(pIOCtx);
		assert(pAcceptCtx != NULL);

		SOCKADDR_IN* pLocalSockaddr = NULL;
		SOCKADDR_IN* pRemoteSockaddr = NULL;
		int nLocalSockaddrLength = 0;
		int nRemoteSockaddrLength = 0;

		///< step 1
		this->m_lpfnGetAcceptExSockAddrs(pAcceptCtx->wbuf.buf, pAcceptCtx->wbuf.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
			sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16,
			(LPSOCKADDR*)&pLocalSockaddr, &nLocalSockaddrLength,
			(LPSOCKADDR*)&pRemoteSockaddr, &nRemoteSockaddrLength);

		///<  设置套接字
		setsockopt(pAcceptCtx->sAcceptSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
			(char*)&(m_listenerSocket), sizeof(m_listenerSocket));

		std::shared_ptr<CAsyNetThreadPool> pAsyNetThreadPool = std::static_pointer_cast<CAsyNetThreadPool>(m_pThreadPool);
		pAsyNetThreadPool->AssociateWithIOCP(&(pAcceptCtx->sAcceptSocket), (ULONG_PTR)0);
		
		//	存储 远程客户端 地址
		memcpy(&pAcceptCtx->RemoteSockAddr, pRemoteSockaddr, sizeof(SOCKADDR_IN));


		//	创建 远程客户

		CAsyNetRemoteClient* pNewRemoteClient = new CAsyNetRemoteClient(&(pAcceptCtx->sAcceptSocket), pAcceptCtx->RemoteSockAddr);
		pNewRemoteClient->AddObserver(this);
		LPPER_IO_CONTEXT pIORecv = new PER_IO_CONTEXT(pNewRemoteClient, ENUM_IO_READ);
		
		//投递  recv请求  从客户端获取数据
		pNewRemoteClient->PostRecv(pIORecv);

		//发送信息 给所有的客户端
		Broadcast(NOTISFY_MSG_SERVER_NEWCLIENT, (void*)pNewRemoteClient, (void*)pIORecv);

		pNewRemoteClient->ReleaseRef();   ///< 注意这里要释放一次，后续都交给NetServer I/O Ctx释放
	}	

	void CAsyNetListener::UpdateAcceptCtxList(CSmartSocketHandle* pRemoteSock)
	{
		CCriticalMutexWapper lock(m_criticalMutexLock);
		m_lpfnDisconnectEx(*pRemoteSock, NULL, TF_REUSE_SOCKET, 0);

		auto iter_find = std::find_if(m_lstCurrentUseAcceptCtx.begin(), m_lstCurrentUseAcceptCtx.end(),
			[&](const std::unique_ptr<PER_IO_CONTEXT>& pItem)->bool{
			auto pItemTmp = dynamic_cast<PER_ACCEPT_CONTEXT*>(pItem.get());
			if (pItemTmp != NULL)
			{
				return (*pRemoteSock == pItemTmp->sAcceptSocket);
			}
			return false;
		});

		if (m_lstCurrentUseAcceptCtx.end() != iter_find)
		{
			
			m_lstReuseAcceptCtx.push_back(std::move(*iter_find));
			
			m_lstCurrentUseAcceptCtx.erase(iter_find);
		}
		
		Broadcast(NOTISFY_MSG_CLIENT_DISCONNECTCLIENT, NULL, (void*)pRemoteSock);
	}
	void CAsyNetListener::Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2)
	{
		switch (iMessage)
		{
		case NOTISFY_MSG_CLIENT_DISCONNECTCLIENT:  ///< 客户端断开
		{

			if (pParam2 != NULL)
			{
				UpdateAcceptCtxList((CSmartSocketHandle*)pParam2);
			}

		}
		break;
		case NOTISFY_MSG_SERVER_DISCONNECTCLIENT:  ///< 服务端主动断开连接
		{
			//作为 服务器的 观察者
			SOCKET* pRemoteSock = (SOCKET*)pParam2;
			Broadcast(NOTISFY_MSG_SERVER_DISCONNECTCLIENT, NULL, (void*)pRemoteSock);
		}
		break;
		default:
			break;
		}
	}
	void CAsyNetListener::DoIOError(LPPER_IO_CONTEXT &pIOCtx)
	{
		DWORD dwError = GetLastError();

		
		CCriticalMutexWapper lock(m_criticalMutexLock);

		auto iter_lstEnd = m_lstCurrentUseAcceptCtx.end();
		for (auto iter_lst = m_lstCurrentUseAcceptCtx.begin(); iter_lst != iter_lstEnd;)
		{
			if (pIOCtx == iter_lst->get())
			{
				iter_lst->reset();
				m_lstCurrentUseAcceptCtx.erase(iter_lst);
				break;
			}
			else
			{
				iter_lst++;
			}
		}
	}
}





