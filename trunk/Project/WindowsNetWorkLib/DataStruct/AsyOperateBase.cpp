#include "stdafx.h"
#include "AsyOperateBase.h"


namespace nsIocpServerClientNet
{
	void AsyOperateBase::AddRef()
	{
		InterlockedIncrement(&m_lRefCount);
	}

	void AsyOperateBase::ReleaseRef()
	{
		InterlockedDecrement(&m_lRefCount);
		if (0 == m_lRefCount)
		{
			delete this;
			
			//һ��ʼ���ü��� ��ʼ��Ϊ1 ���� delete this ���ٴ�ִ������
			return;
		}
	}
}

