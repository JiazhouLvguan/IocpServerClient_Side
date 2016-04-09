#include "stdafx.h"
#include "AsyNetServer.h"

namespace nsIocpServerClientNet
{
	CAysNetServer::CAysNetServer()
		:IObserver()
	{

	}

	CAysNetServer::~CAysNetServer()
	{

	}
	
	CAysNetServer::mapClientsMessage	CAysNetServer::m_mapClientsMessage;
	CCriticalMutex						CAysNetServer::m_criticalMutex;

	void CAysNetServer::AddMessageToServer(pairClientMessage& _pairClientMessage)
	{
		CCriticalMutexWapper criticalMutexWapper(m_criticalMutex);
		m_mapClientsMessage.insert(_pairClientMessage);
	}

	void CAysNetServer::InitServer()
	{
		///< 初始化线程池 IOCP
		m_pThPool = std::shared_ptr<IThreadPool>(new CAsyNetThreadPool);
		std::shared_ptr<CAsyNetThreadPool> pAsyNetThreadPool = std::static_pointer_cast<CAsyNetThreadPool>(m_pThPool);

		if (!pAsyNetThreadPool->CreateThreadPool(THREADS_NUM))
			throw CExceptionThreadPool("create threadpool fail");
	}

	void CAysNetServer::UninitServer()
	{
		
		assert(m_pThPool != NULL);
		m_pThPool->DestoryThreadPool();
		
		m_rwlockRemoteClientSet.lock();
			
		std::for_each(m_mapRemoteClient2IOSet.begin(), m_mapRemoteClient2IOSet.end(),
			[](std::pair<AsyOperateBase*, std::set<LPPER_IO_CONTEXT>> MapItem)
		{

			auto pRemoteClient = dynamic_cast<CAsyNetRemoteClient*>(MapItem.first);
			if (pRemoteClient != NULL)
			{
				std::for_each(MapItem.second.begin(), MapItem.second.end(),
					[](LPPER_IO_CONTEXT pIOCtx){
					delete pIOCtx;
					pIOCtx = NULL;
				});
				MapItem.second.clear();

				pRemoteClient->CloseSocket();
				pRemoteClient->ReleaseRef();
			}
		});

		m_mapRemoteClient2IOSet.clear();
		m_rwlockRemoteClientSet.unlock();
		
		auto pListener = dynamic_cast<CAsyNetListener*>(m_pListener);
		
		if (pListener != NULL)
		{
			pListener->CloseSocket();
			pListener->ReleaseRef();
		}	
	}

	void CAysNetServer::StartListen(const char *pListenIP, const UINT32 port)
	{
		//CIOCPBase IOCPObject;
		m_pListener = new CAsyNetListener(m_pThPool);
		CAsyNetListener*	pAsyNetListener = dynamic_cast<CAsyNetListener*>(m_pListener);

		try
		{
			pAsyNetListener->OpenSocket(pListenIP, port, true);

			pAsyNetListener->Listen();
		}
		catch (CExceptionSocket& ex)
		{
			pAsyNetListener->ReleaseRef();
			pAsyNetListener = NULL;
			throw ex;
			return;
		}
	
		

		IObserver* pObserver = (IObserver*)this;
		pAsyNetListener->AddObserver(pObserver);
	}

	

	void CAysNetServer::AddRemoteClient(AsyOperateBase* pRemoteClient, LPPER_IO_CONTEXT pIOCtx)
	{
		m_rwlockRemoteClientSet.lock();

		pRemoteClient->AddRef();

		
		auto iter_find = m_mapRemoteClient2IOSet.find(pRemoteClient);
		if (m_mapRemoteClient2IOSet.end() == iter_find)
		{
			std::set<LPPER_IO_CONTEXT> IOCtxSet;
			IOCtxSet.insert(pIOCtx);
			m_mapRemoteClient2IOSet.insert(std::make_pair(pRemoteClient, IOCtxSet));
		}
		else
		{
			iter_find->second.insert(pIOCtx);
		}
		m_rwlockRemoteClientSet.unlock();
		
	}

	void CAysNetServer::DeleteRemoteClient(AsyOperateBase* pRemoteClient, SOCKET* pRemoteSockKey)
	{
		m_rwlockRemoteClientSet.lock();

		///< 先通过指针对象查找
		if (pRemoteClient != NULL)
		{
			auto iter_find = m_mapRemoteClient2IOSet.find(pRemoteClient);
			if (m_mapRemoteClient2IOSet.end() != iter_find)
			{
				pRemoteClient->ReleaseRef();

				///< 当前情况是客户端主动断开连接的正常处理，I/O操作在线程池中释放
				m_mapRemoteClient2IOSet.erase(iter_find);
			}
		}

		///< 再根据socket查找对象
		if (pRemoteSockKey != NULL)
		{
			auto iter_MapEnd = m_mapRemoteClient2IOSet.end();
			for (auto iter_map = m_mapRemoteClient2IOSet.begin(); iter_map != iter_MapEnd;)
			{
				auto pTmp = dynamic_cast<CAsyNetRemoteClient*>(iter_map->first);
				if (pTmp != NULL)
				{
					if (pTmp->m_RemoteSocket == (*pRemoteSockKey))
					{
						pTmp->ReleaseRef();
						iter_map = m_mapRemoteClient2IOSet.erase(iter_map);
						break;
					}
					else
					{
						++iter_map;
					}
				}
			}
		}
		m_rwlockRemoteClientSet.unlock();
	}

	void CAysNetServer::Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2)
	{
		switch (iMessage)
		{
			case NOTISFY_MSG_SERVER_NEWCLIENT:         ///< 新增客户端连接
			{
				AddRemoteClient((AsyOperateBase*)pParam1, (LPPER_IO_CONTEXT)pParam2);
				break;
			}
			
			case NOTISFY_MSG_SERVER_DISCONNECTCLIENT:  ///< 服务端主动断开客户端连接
			{
				break;
			}
			
			case NOTISFY_MSG_CLIENT_DISCONNECTCLIENT:   ///< 删除客户端连接
			{
				DeleteRemoteClient((AsyOperateBase*)pParam1, (SOCKET*)pParam2);
				break;
			}
			
			default:
				break;
		}
	}



}