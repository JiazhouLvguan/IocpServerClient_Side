#include "../IocpBase/IocpBase.h"
#include "ThreadPoolBase.h"





namespace nsIocpServerClientNet
{
	class CAsyNetThreadPool :public CIocpBase, public IThreadPool
	{
	private:
		std::vector<CSmartThreadHandle>		m_vecSmartThreadHandle;

	public:
		CAsyNetThreadPool();
		~CAsyNetThreadPool();
	public:
		bool CreateThreadPool(int nThreadNumber);
		void DestoryThreadPool();
		void DoTask();
	};
}

