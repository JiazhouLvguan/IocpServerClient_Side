#pragma once

namespace nsIocpServerClientNet
{

	//typedef std::function<void(std::wstring)>	fShowClientMessgae;

	class CIocpServer
	{
	//private:
		//fShowClientMessgae		m_fShowClientMessgae;
	public:
		CIocpServer(const char* pszAddress, int nPort);
		
		//void	AddShowClientMessageFunction(fShowClientMessgae&);
		//使用C++11 特性  将 RemoteClient 消息 显示在 客户端 
		/*
			考虑以下问题:
			1. 多线程 同时操作 control 写数据
			2. 程序耦合

			最终决定 通过向 客户端 投递消息 完成此功能
		*/


		~CIocpServer();
	
	};
}