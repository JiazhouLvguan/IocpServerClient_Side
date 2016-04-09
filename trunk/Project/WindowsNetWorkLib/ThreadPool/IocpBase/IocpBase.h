#pragma once

namespace nsIocpServerClientNet
{
	class CIocpBase
	{
	protected:
		CSmartIocpHandle	m_hIocp;
	public:
		CIocpBase();
		~CIocpBase();
		bool	CreateIocp(int nThreadCount);
		void	ReleaseIocp();

		//与设备绑定  套接字  文件等
		bool	AssociateWithIOCP(CSmartFileHandle* hEquipment, ULONG_PTR keyWord);
		bool	AssociateWithIOCP(CSmartSocketHandle* hEquipment, ULONG_PTR keyWord);
	};
}
