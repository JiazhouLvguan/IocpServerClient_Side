#include "stdafx.h"
#include "Subject.h"
#include "ObserverBase.h"

namespace nsIocpServerClientNet
{

	void CSubject::AddObserver(IObserver* pObserver)
	{
		m_readWriteMutex.lock();
		m_setObserver.insert(pObserver);
		m_readWriteMutex.unlock();
	}

	void CSubject::RemoveObserver(IObserver* pObserver)
	{
		m_readWriteMutex.lock();
		auto iter_find = m_setObserver.find(pObserver);
		if (m_setObserver.end() != iter_find)
		{
			m_setObserver.erase(iter_find);
		}
		m_readWriteMutex.unlock();
	}

	bool CSubject::Broadcast(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2)
	{
		m_readWriteMutex.lock_read();
		auto iter_set_end = m_setObserver.cend();
		for (auto iter_set = m_setObserver.begin(); iter_set != iter_set_end; ++iter_set)
		{
			(*iter_set)->Notify(iMessage, pParam1, pParam2);
		}
		m_readWriteMutex.unlock();
		return true;
	}

	bool CSubject::Notisfy(IObserver*  pObserver, const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2)
	{
		m_readWriteMutex.lock_read();
		auto iter_find = m_setObserver.find(pObserver);
		if (m_setObserver.end() != iter_find)
		{
			pObserver->Notify(iMessage, pParam1, pParam2);
		}
		m_readWriteMutex.unlock();
		return true;
	}
	
}



