#pragma once


#include "AsyOperateBase.h"


namespace nsIocpServerClientNet
{
	#define  MAX_BUF_LEN 1024

	typedef enum
	{
		ENUM_IO_ACCEPT = 0,
		ENUM_IO_CONNECT,
		ENUM_IO_READ,
		ENUM_IO_WRITE,
		ENUM_IO_ERROR,
	}ENUM_IO_OPER;

	typedef struct _OverLappedEx
	{
		OVERLAPPED			overLapped;
		ENUM_IO_OPER		enumoper;
		DWORD				flags;
		WSABUF				wbuf;
		CHAR				data[MAX_BUF_LEN];
		AsyOperateBase*		pAsyOperate;

		_OverLappedEx(){}      ///< 默认构造
		_OverLappedEx(AsyOperateBase* pAsyOperate, ENUM_IO_OPER enumoper)
			:pAsyOperate(pAsyOperate)
			, enumoper(enumoper)
			, flags(0)
		{
			pAsyOperate->AddRef();///< 注意每次复制对象，添加引用次数
			memset(&overLapped, 0, sizeof(overLapped));
			memset(data, 0, MAX_BUF_LEN);
			memset(&wbuf, 0, sizeof(wbuf));
			wbuf.buf = data;
			wbuf.len = MAX_BUF_LEN;
		}

		virtual ~_OverLappedEx()
		{
			pAsyOperate->ReleaseRef();
		}

		void ResetBuf()
		{
			memset(&overLapped, 0, sizeof(overLapped));
			memset(data, 0, MAX_BUF_LEN);
		}

	}PER_IO_CONTEXT, *LPPER_IO_CONTEXT;


	
	typedef struct _Accept_OverLappedEx : public _OverLappedEx
	{
		CSmartSocketHandle      sAcceptSocket;			///< Accepth或者AcceptEx使用的客户连接
		SOCKADDR_IN  RemoteSockAddr;		///< 远程连接的地址信息

		_Accept_OverLappedEx(AsyOperateBase* _pAsyncIO)
			:_OverLappedEx(_pAsyncIO, ENUM_IO_ACCEPT)
			, sAcceptSocket(INVALID_SOCKET)
		{
			memset(&RemoteSockAddr, 0, sizeof(SOCKADDR_IN));
		}
	}PER_ACCEPT_CONTEXT, *LPPER_ACCEPT_CONTEXT;

}
