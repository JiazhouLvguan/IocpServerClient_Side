#pragma once
#include "../MessageDefine/MessageDefine.h"



namespace nsIocpServerClientNet
{
	class IObserver
	{
	public:
		virtual void Notify(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2) = 0;
	};
}

