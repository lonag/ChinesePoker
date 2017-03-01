#ifndef _ccskynet_dispatch_
#define _ccskynet_dispatch_
#include "cocos2d.h"
#include "../ccskynet/ccskynet_manager.h"
USING_NS_CC;
typedef void (Ref::*fnPacketfunc)(ccskynet_message* mess);
typedef void (*SMsgFun_Decleared) (void* target, ccskynet_message* msg);
typedef struct SMsgReceiver
{
	void* m_pObj;
	union
	{
		fnPacketfunc m_pRefFun;
		SMsgFun_Decleared m_pStaticFun;
	};
	bool m_bIsDecleared;
}TMsgReceiver;

class ccskynet_dispatch
{
public:
	ccskynet_dispatch();
	~ccskynet_dispatch();
    
public:
	static ccskynet_dispatch* getInstance();
	
public:
	bool dispatch_message(const char* msgType, ccskynet_message* msg);
	void register_message(const char* msgType,Ref* obj, ccskynet_message* mess, fnPacketfunc func);
	void register_message_cast(const char* msgType, void *obj, ccskynet_message*mess, fnPacketfunc func);
	void unregister_message(const char* msgType, void *obj);
protected:
	std::map<std::string, std::list<TMsgReceiver*>> m_aReceivers;
};
#endif
