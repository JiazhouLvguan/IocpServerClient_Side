#pragma once

#include "SubjectBase.h"
#include "../MessageDefine/MessageDefine.h"


namespace nsIocpServerClientNet
{
	class CSubject :public ISubject
	{
		protected:
			_CReadWriteMutex		m_readWriteMutex;
			std::set<IObserver*>	m_setObserver;

		public:
			void AddObserver(IObserver*);

			void RemoveObserver(IObserver*);

			bool Broadcast(const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2);
			bool Notisfy(IObserver*  pObserver, const NOTISY_MSG_TYPE iMessage, void* pParam1, void* pParam2);
	};
}
