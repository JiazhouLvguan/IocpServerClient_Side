#pragma once


#include <windows.h>



namespace nsIocpServerClientUtility
{
	class CStaticMutex
	{
		private:
			HANDLE m_hMutex;

		public:
			CStaticMutex()
				:m_hMutex(::CreateMutex(NULL,FALSE,NULL)){}
			~CStaticMutex(){ ::CloseHandle(m_hMutex); }
			
			bool Lock();
			bool Unlock();
			bool TryLock();
	};
	inline bool CStaticMutex::Lock()
	{
		return ::WaitForSingleObject(m_hMutex,INFINITE) == WAIT_OBJECT_0 ;
	}
	inline bool CStaticMutex::Unlock()
	{
		return ::ReleaseMutex(m_hMutex) == TRUE;
	}
	inline bool CStaticMutex::TryLock()
	{
		return ::WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0;
	}
}
