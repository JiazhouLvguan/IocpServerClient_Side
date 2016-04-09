#pragma once

#include "../DataStruct/IocpStruct.h"
#include "../Observer/ObserverBase.h"
#include "../DataStruct/AsyOperateBase.h"
#include "../AsyNetListener/AsyNetListener.h"
#include "../AsyNetRemoteClient/AsyNetRemoteClient.h"


namespace nsIocpServerClientNet
{
	class CAysNetServer : public IObserver
	{
	public:
		typedef std::map<int, std::vector<std::string>>		mapClientsMessage;
		typedef	std::pair<int, std::vector<std::string>>		pairClientMessage;
	private:
		static	CCriticalMutex		m_criticalMutex;
		static	mapClientsMessage	m_mapClientsMessage;
		
	public:
		static	void	AddMessageToServer(pairClientMessage&);

	public:

		CAysNetServer();
		virtual ~CAysNetServer();

		void InitServer();

		void UninitServer();

		void StartListen(const char *pListenIP, const UINT32 port);
		
		void AddRemoteClient(AsyOperateBase* pRemoteClient, LPPER_IO_CONTEXT pIOCtx);

		void DeleteRemoteClient(AsyOperateBase* pRemoteClient, SOCKET* pRemoteSockKey);

		virtual void Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2);

	private:
		AsyOperateBase*		m_pListener;
		
		_CReadWriteMutex	m_rwlockRemoteClientSet;

		std::map<AsyOperateBase*, std::set<LPPER_IO_CONTEXT>> m_mapRemoteClient2IOSet;

		std::shared_ptr<IThreadPool> m_pThPool;
	};
}


