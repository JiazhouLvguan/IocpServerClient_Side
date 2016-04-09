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
			
			//一开始引用计数 初始化为1 避免 delete this 后再次执行析构
			return;
		}
	}
}

