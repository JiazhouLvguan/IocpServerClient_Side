#include "stdafx.h"
#include "IocpServer.h"

#include "AsyNetServer/AsyNetServer.h"

namespace nsIocpServerClientNet
{
	CAysNetServer* pAysNetServer = NULL;
	
	CIocpServer::CIocpServer(const char* pszAddress, int nPort)
	{
		if (pAysNetServer != NULL)
			return;

		WSAData wsadata;
		if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
			throw CExceptionInitNet("init net fail");

		pAysNetServer = new CAysNetServer;
		pAysNetServer->InitServer();

		pAysNetServer->StartListen(pszAddress, nPort);
	}

	CIocpServer::~CIocpServer()
	{
		if (pAysNetServer)
		{
			pAysNetServer->UninitServer();
			pAysNetServer = NULL;
			WSACleanup();
		}
	}
}

