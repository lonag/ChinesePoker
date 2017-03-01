#ifndef _ccskynet_socket_h_
#define _ccskynet_socket_h_
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
typedef unsigned int          SOCKET;
#ifndef INVALID_SOCKET
#define INVALID_SOCKET  (SOCKET)(~0)
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR            (-1)
#endif
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#endif

enum ccsSocketStatus
{
	eSocketConnected			=  1,
	eSocketConnecting			=  2,
	eSocketDisconnected			=  3,
	eSocketConnectFailed		=  4,
	eSocketConnectTimeout		=  5,
	eSocketReceive				=  6,
	eSocketIoClosed				=  0,
	eSocketIoError				= -1,
	eSocketCreateFailed			= -2,
};
class ccskynet_socket
{
public:
	ccskynet_socket();
	~ccskynet_socket();
public:
	bool ccInit();
	int  ccRead(char* _buff, int _len);
	int  ccWrite(char* _buff, int _len);
	int  ccIsConnected();
	bool ccIsReadable();
	bool ccIsWritable();
	void ccClose();
	bool ccConnect();
	void ccDisconnect();
	void setInetAddress(std::string ip,unsigned short port);
protected:
	SOCKET m_uSocket;
	std::string ip;
	unsigned short port;
};
#endif