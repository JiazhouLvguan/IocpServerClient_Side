#pragma once


namespace nsIocpServerClientNet
{
	struct IRef
	{
		virtual void AddRef() = 0;
		virtual void ReleaseRef() = 0;
	};


	struct AsyOperateBase : public IRef
	{
	
		long m_lRefCount = 1;

	
		void AddRef();
		void ReleaseRef();

		virtual bool Operate(bool bRet, DWORD dwBytesTransfered, void* pParam) = 0;
	};
}


