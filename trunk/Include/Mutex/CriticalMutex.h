#pragma once


#include <windows.h>

namespace nsIocpServerClientUtility
{
	class CCriticalMutex
	{
		private:
			CRITICAL_SECTION m_cSection;

		public:
			CCriticalMutex(){ InitializeCriticalSection(&m_cSection); }
			~CCriticalMutex(){ DeleteCriticalSection(&m_cSection); }
			
		public:
			bool Lock();
			bool Unlock();
			bool TryLock();
	};
	inline bool CCriticalMutex::Lock()
	{
		EnterCriticalSection(&m_cSection); return true;
	}
	inline bool CCriticalMutex::Unlock()
	{
		LeaveCriticalSection(&m_cSection); return true;
	}
	inline bool CCriticalMutex::TryLock()
	{
		return TryEnterCriticalSection(&m_cSection);
	}
}