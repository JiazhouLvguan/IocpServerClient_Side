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
		//ʹ��C++11 ����  �� RemoteClient ��Ϣ ��ʾ�� �ͻ��� 
		/*
			������������:
			1. ���߳� ͬʱ���� control д����
			2. �������

			���վ��� ͨ���� �ͻ��� Ͷ����Ϣ ��ɴ˹���
		*/


		~CIocpServer();
	
	};
}