#pragma once


#include <Windows.h>
#include <Winsock2.h> 



/*
	句柄的封装 智能清理
*/

typedef VOID(WINAPI*FREEHANDLE)(UINT_PTR);


template<class HANDLETYPE, FREEHANDLE Function, UINT_PTR defaultValue = NULL>
class CSmartHandle
{
	private:
		UINT_PTR	m_handle;
		

	public:
		CSmartHandle()
			:m_handle(defaultValue) {}
		
		CSmartHandle(HANDLETYPE handleType) 
			:m_handle((UINT_PTR)handleType) {}
		
		operator HANDLETYPE()
		{
			return (HANDLETYPE)m_handle;
		}
		

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//private:
	//	HANDLETYPE	m_handleType;
	//public:
		/* 强制转换后   放在临时变量 中 无法对其取值  */
		/*
		operator HANDLETYPE*()	const
		{
			//return &((HANDLETYPE)m_handle);	
			m_handleType = (HANDLETYPE)m_handle;
			return &m_handleType;
		}
		*/
	////////////////////////////////////////////////////////////////////////////////////////////////////

		CSmartHandle& operator=(const CSmartHandle& smartHandle)
		{
			m_handle = smartHandle.m_handle;
			return *this;
		}

		HANDLETYPE operator=(HANDLETYPE handleType)
 		{
 			FreeHandle();
 			m_handle = (UINT_PTR)handleType;
			return *this;
 		}

		~CSmartHandle()
		{
			FreeHandle();
		}
		bool	CheckIsValid()
		{
			return m_handle != defaultValue;
		}
		void	FreeHandle()
		{
			if (CheckIsValid())
			{
				Function(m_handle);
				m_handle = defaultValue;
			}
		}

};

#define  MAKESMARTFREEHANDLE(ClassName,DefineType,Function)\
	typedef CSmartHandle<DefineType,(FREEHANDLE)Function>ClassName;


#define  MAKESMARTFREEHANDLEEX(ClassName,DefineType,Function,defaultValue)\
	typedef CSmartHandle<DefineType,(FREEHANDLE)Function,defaultValue>ClassName;

MAKESMARTFREEHANDLE(CSmartIocpHandle, HANDLE, CloseHandle);
MAKESMARTFREEHANDLE(CSmartThreadHandle, HANDLE, CloseHandle);
MAKESMARTFREEHANDLE(CSmartFileHandle, HANDLE, CloseHandle);
MAKESMARTFREEHANDLE(CSmartSocketHandle, SOCKET, closesocket);
