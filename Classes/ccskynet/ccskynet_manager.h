#ifndef _ccskynet_manager_
#define _ccskynet_manager_
#include "cocos2d.h"
#include "../ccskynet/ccskynet_socket.h"
#include "../ccskynet/ccskynet_message.h"
USING_NS_CC;


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

#define SOCKET_READ_BUFFER_SIZE 8192

class ccskynet_manager 
{
public:
	ccskynet_manager();
	~ccskynet_manager();
	static ccskynet_manager* getInstance();
	void start();
	static void* run(void* u);
	std::thread t;
	// check the net status
	bool isConnected();
	// close the socket
	void close();
	// connect to target address
	bool connect();
	// disconnect as close for now
	void disconnect();

	void onDisconnected(){}
	void onConnected(){}

public:
	bool canRead();
	bool canWrite();
	void send(ccskynet_message* mess);
	ccskynet_socket ccsSocket;
	ccsSocketStatus  m_eStatus;
	std::list<ccskynet_message*> m_PsendBufferQueue;
	char m_pReadBuffer[SOCKET_READ_BUFFER_SIZE];
};

#endif
