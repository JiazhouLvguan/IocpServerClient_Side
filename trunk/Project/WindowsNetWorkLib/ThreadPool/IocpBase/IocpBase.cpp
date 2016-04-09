#include "stdafx.h"
#include "IocpBase.h"


namespace nsIocpServerClientNet
{

	CIocpBase::CIocpBase()
	{
	
	}

	CIocpBase::~CIocpBase()
	{
		ReleaseIocp();
	}

	bool	CIocpBase::CreateIocp(int nThreadCount)
	{
		m_hIocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, nThreadCount);
		return m_hIocp.CheckIsValid();
	}

	void	CIocpBase::ReleaseIocp()
	{
		m_hIocp.FreeHandle();
	}
	
	bool	CIocpBase::AssociateWithIOCP(CSmartFileHandle* hEquipment, ULONG_PTR keyWord)
	{
		assert(hEquipment != INVALID_HANDLE_VALUE);
		assert(m_hIocp.CheckIsValid());
		return ::CreateIoCompletionPort(hEquipment, m_hIocp, keyWord, NULL) == m_hIocp;
	}

	bool	CIocpBase::AssociateWithIOCP(CSmartSocketHandle* hEquipment, ULONG_PTR keyWord)
	{
		assert(m_hIocp.CheckIsValid());
		SOCKET s = *hEquipment;
		return ::CreateIoCompletionPort((HANDLE)s, m_hIocp, keyWord, NULL) == m_hIocp;
	}

}

