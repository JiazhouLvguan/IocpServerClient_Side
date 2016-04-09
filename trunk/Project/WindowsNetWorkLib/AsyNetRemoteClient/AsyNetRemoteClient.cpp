#include "stdafx.h"
#include "AsyNetRemoteClient.h"


namespace nsIocpServerClientNet
{
	CAsyNetRemoteClient::CAsyNetRemoteClient(CSmartSocketHandle* pRemoteSock,SOCKADDR_IN remoteSockAddr)
		:m_RemoteSocket(*pRemoteSock)
		, m_RemoteSockaddr(remoteSockAddr)
	{

	}


	CAsyNetRemoteClient::~CAsyNetRemoteClient(void)
	{
	}

	bool CAsyNetRemoteClient::Operate(bool bRet, DWORD dwBytesTransfered, void* pParam)
	{
		LPPER_IO_CONTEXT pIOCtx = (LPPER_IO_CONTEXT)pParam;
		assert(pIOCtx != NULL);

		if (bRet)
		{
			if (0 != dwBytesTransfered)
			{
				switch (pIOCtx->enumoper)
				{
					case ENUM_IO_READ:
					{
						DoRecv(pIOCtx);

						//此处添加回调	 
						PostClientMessgaeToServerWindow(pIOCtx->data);

						break;
					}
				
					case ENUM_IO_WRITE:
						break;
					default:
						break;
				}
			}
			else
			{
				DoIOError(pIOCtx);
				return false;
			}
				
		}
		else
		{
			DoIOError(pIOCtx);
			return false;
		}

		return true;
	}

	void CAsyNetRemoteClient::PostRecv(LPPER_IO_CONTEXT pIOCtx /*= NULL*/)
	{
		bool bNew = false;
		if (pIOCtx == NULL)
		{
			pIOCtx = new PER_IO_CONTEXT(this, ENUM_IO_READ);
			bNew = true;
		}
		else
		{
			pIOCtx->ResetBuf();
		}

		int nRet = WSARecv(m_RemoteSocket,
			&pIOCtx->wbuf,
			1,
			&pIOCtx->wbuf.len,
			&pIOCtx->flags,
			&pIOCtx->overLapped,
			NULL);

		if (SOCKET_ERROR == nRet && WSA_IO_PENDING != WSAGetLastError())
		{
			if (bNew)
			{
				delete pIOCtx;
				pIOCtx = NULL;
			}
			throw CExceptionSocket("wsarecv error");
		}
	}

	void CAsyNetRemoteClient::DoRecv(LPPER_IO_CONTEXT pIOCtx)
	{
		return PostRecv(pIOCtx);
	}

	void CAsyNetRemoteClient::CloseSocket()
	{
		shutdown(m_RemoteSocket, SD_BOTH);
		m_RemoteSocket.FreeHandle();
	}

	void CAsyNetRemoteClient::DoIOError(LPPER_IO_CONTEXT &pIOCtx)
	{
		DWORD dwError = GetLastError();
		
		if (ERROR_OPERATION_ABORTED == dwError)
		{
			Broadcast(NOTISFY_MSG_SERVER_NEWCLIENT, (void*)this, (void*)&m_RemoteSocket);
		}

		Broadcast(NOTISFY_MSG_CLIENT_DISCONNECTCLIENT, (void*)this, (void*)&m_RemoteSocket);
	}

	void CAsyNetRemoteClient::PostClientMessgaeToServerWindow(char*	pszMessage)
	{
		HWND hOldWnd = ::FindWindow(TO_FIND_MAINWINDOW_DEFINED_CLASSNAME, TO_FIND_MAINWINDOW_DEFINED_NAME);
		//取出数据 插入 到vector中
		::PostMessage(hOldWnd, WM_REMOTECLIENT_MESSAGE, (WPARAM)pszMessage,NULL);
	}

}

