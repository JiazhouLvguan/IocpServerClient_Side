#pragma once

#include "ReadWriteMutex.h"
#include "StaticMutex.h"
#include "CriticalMutex.h"

namespace nsIocpServerClientUtility
{
	template<typename Mutex> class CMutexWapper
	{
		private:
			Mutex& m_mutex;
		public:
			CMutexWapper(Mutex& mutex) :m_mutex(mutex)
			{
				m_mutex.Lock();
			}
			~CMutexWapper()
			{
				m_mutex.Unlock();
			}
			bool TryLock()
			{
				return  m_mutex.TryLock();
			}
	};

	typedef CMutexWapper<CStaticMutex>		CStaticMutexWapper;
	typedef CMutexWapper<CCriticalMutex>	CCriticalMutexWapper;

}