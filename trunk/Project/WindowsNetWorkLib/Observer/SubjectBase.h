#pragma once

#include "../MessageDefine/MessageDefine.h"

#include "ObserverBase.h"

//������ģ����� �Ż���ͷ�ļ�

namespace nsIocpServerClientNet
{
	class ISubject
	{
	public:

		virtual void AddObserver(IObserver*) = 0;
		virtual void RemoveObserver(IObserver*) = 0;

		virtual bool Broadcast(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2) = 0;
		virtual bool Notisfy(IObserver*  pObserver, const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2) = 0;
	};
}


