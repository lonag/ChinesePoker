#include "../ccskynet/ccskynet_dispatch.h"

static ccskynet_dispatch* instance = NULL;

ccskynet_dispatch::ccskynet_dispatch()
{
	m_aReceivers.clear();
}

ccskynet_dispatch::~ccskynet_dispatch()
{
	for (std::map<std::string, std::list<TMsgReceiver*> >::iterator it = m_aReceivers.begin();
		it != m_aReceivers.end();
		++it)
	{
		//delete it->second;
		std::list<TMsgReceiver*>& recv = it->second;
		for (std::list<TMsgReceiver*>::iterator lit = recv.begin();
			lit != recv.end(); 
			++lit)
		{
			delete *lit;
		}
	}
	m_aReceivers.clear();
}
ccskynet_dispatch* ccskynet_dispatch::getInstance()
{
	if (instance!=NULL)
	{
		instance=new ccskynet_dispatch();
	}
	return instance;
}

bool ccskynet_dispatch::dispatch_message(const char* msgType, ccskynet_message* msg)
{
	std::map<std::string, std::list<TMsgReceiver*> >::iterator it = m_aReceivers.find(msgType);

	if (it != m_aReceivers.end())
	{
		std::list<TMsgReceiver*> recvs = it->second;

		for (std::list<TMsgReceiver*>::iterator lit = recvs.begin();
			lit != recvs.end(); 
			++lit)
		{
			TMsgReceiver* recv = *lit;
			if (recv->m_bIsDecleared)
			{
				(*recv->m_pStaticFun)(recv->m_pObj, msg);
			}
			else
			{
				(((cocos2d::Ref*)(recv->m_pObj))->*(recv->m_pRefFun))(msg);
			}		
		}
		return true;
	}
	return false;
}

void ccskynet_dispatch::register_message(const char* msgType, Ref* obj, ccskynet_message* mess, fnPacketfunc func)
{
	log ("registeMsg:%s\n", msgType);
	if (msgType)
	{
		this->unregister_message(msgType, obj);

		TMsgReceiver* it = new TMsgReceiver;

		it->m_pObj = (void*)obj;
		it->m_pRefFun = func;
		it->m_bIsDecleared = false;
		//m_aReceivers[msgType] = it;
		m_aReceivers[msgType].push_back(it);
	}
}

void ccskynet_dispatch::unregister_message(const char* msgType, void *obj)
{
	std::map<std::string, std::list<TMsgReceiver*> >::iterator it = m_aReceivers.find(msgType);

	if (it != m_aReceivers.end())
	{
		std::list<TMsgReceiver*>& recv = it->second;
		for (std::list<TMsgReceiver*>::iterator lit = recv.begin();
			lit != recv.end(); 
			++lit)
		{
			if ((*lit)->m_pObj == obj)
			{
				//printf ("un registeMsg:%s\n", msgType);
				delete *lit;
				recv.erase(lit);
				if (recv.size() == 0)
				{
					m_aReceivers.erase(it);
				}
				break;
			}
		}
	}
}
