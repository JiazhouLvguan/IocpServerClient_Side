#pragma once


#include "ThreadPoolBase.h"
#include "../IocpBase/IocpBase.h"
#include "../../NetDefine/NetDefine.h"
#include "../../DataStruct/IocpStruct.h"


namespace nsIocpServerClientNet
{
	class CAsyNetThreadPool :public CIocpBase, public IThreadPool
	{
	private:
		std::vector<std::thread*>			m_vecpthread;

	public:
		CAsyNetThreadPool();
		~CAsyNetThreadPool();
	public:
		bool CreateThreadPool(int nThreadNumber);
		void DestoryThreadPool();
		void DoTask();
	};
}

