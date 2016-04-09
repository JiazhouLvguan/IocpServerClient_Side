#pragma once
 
typedef enum
{
	NOTISFY_MSG_SERVER_NEWCLIENT = 0x01,				///< 服务端新增远程客户连接
	NOTISFY_MSG_SERVER_DISCONNECTCLIENT = 0x02,			///< 服务端主动断开远程客户连接
	NOTISFY_MSG_CLIENT_NEWCLIENT = 0x03,				///< 客户端新增远程客户连接
	NOTISFY_MSG_CLIENT_DISCONNECTCLIENT = 0x04,			///< 客户端主动断开连接
}NOTISY_MSG_TYPE;


#define  IOCP_EXIT_FLAG  0xFFFFFFFF
#define  THREADS_NUM     4
#define  ACCEPT_NUM      10



