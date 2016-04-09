

namespace nsIocpServerClientNet
{
	class IThreadPool
	{
	public:
		virtual bool CreateThreadPool(int nThreadNumber) = 0;
		virtual void DestoryThreadPool() = 0;
		virtual	void DoTask() = 0;
	};
}
