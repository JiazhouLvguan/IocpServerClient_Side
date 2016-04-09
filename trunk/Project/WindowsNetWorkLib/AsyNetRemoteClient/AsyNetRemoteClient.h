#pragma once

#include "../Observer/Subject.h"
#include "../DataStruct/IocpStruct.h"

namespace nsIocpServerClientNet
{
	class CAsyNetRemoteClient : public AsyOperateBase,public CSubject /*�����������۲죬����Ͽ�����*/
	{
		friend class CAysNetServer;

	public:

		CAsyNetRemoteClient(CSmartSocketHandle* pRemoteSock, SOCKADDR_IN remoteSockAddr);
		virtual ~CAsyNetRemoteClient(void);
					
		virtual bool Operate(bool bRet, DWORD dwBytesTransfered, void* pParam);

		void PostRecv(LPPER_IO_CONTEXT pIOCtx = NULL);

		void DoRecv(LPPER_IO_CONTEXT pIOCtx);

		void CloseSocket();

		void DoIOError(LPPER_IO_CONTEXT &pIOCtx);

		//�������
		void PostClientMessgaeToServerWindow(char*	pszMessage);

	private:
		std::vector<std::string>			m_vecString;

		CSmartSocketHandle					m_RemoteSocket;

		const SOCKADDR_IN					m_RemoteSockaddr;

		std::shared_ptr<PER_IO_CONTEXT>		m_pIOCtx;
	};
}

