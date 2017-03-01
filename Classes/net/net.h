#ifndef _NET_H
#define _NET_H
#include "cocos2d.h"
#include "Socket.h"
#include "Reactor.h"
#include "RPacket.h"
#include "WPacket.h"
#include <signal.h>
namespace net{
static inline bool init(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
   WSADATA wsaData;
   if(WSAStartup(0x0202,&wsaData) != 0)
   {
      WSACleanup();
      return false;
   }
#else
	signal(SIGPIPE,SIG_IGN);
#endif   
   return true;
}

static inline void clean(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)   
   WSACleanup();
#endif   
}

}

#endif
