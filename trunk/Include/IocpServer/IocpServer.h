#pragma once



namespace nsIocpServerClientNet
{
	class CIocpServer
	{
	public:
		CIocpServer(const char*	pszAddress, int nPort);
		~CIocpServer();
	};
	
}