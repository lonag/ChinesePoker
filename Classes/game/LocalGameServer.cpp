#include "../game/LocalGameServer.h"
#include "../common/UserInfo.h"
#include "../game/GamePokeManager.h"
#include "../Common/CommonUtils.h"
#include "../common/AutoNode.h"
#include "../common/UserInfo.h"
#include "../common/CountNode.h"
#include "../log/logger.h"


#define SHOW_OUT_ID 10045//出牌对象的scene id

static LocalGameServer* instance=NULL;
LocalGameServer::LocalGameServer()
{
	
	node=AutoNode::create();
	leftvalue=0;
	rightvalue=0;
	rightscore=0;
	leftscore=0;
}
void LocalGameServer::restart()
{
	leftvalue=0;
	rightvalue=0;
	rightscore=0;
	leftscore=0;
	UserInfo::getInstance()->setIsExistCount(false);
	UserInfo::getInstance()->setType(-1);
	UserInfo::getInstance()->setBanker(3);
	std::vector<PokeData>T_data;
	UserInfo::getInstance()->setFirstPoke(T_data);
	UserInfo::getInstance()->setFirstType(-1);
	safe_delete_list(nobankeridlist);
	safe_delete_list(idlist);
	safe_delete_list(clientPokeData);
	safe_delete_list(recvObjPokeList);
	safe_delete_list(donelist);
}
void LocalGameServer::Destory()
{
	leftvalue=0;
	rightvalue=0;
	rightscore=0;
	leftscore=0;
	UserInfo::getInstance()->setIsExistCount(false);
	UserInfo::getInstance()->setType(-1);
	//UserInfo::getInstance()->setBanker(-1);
	std::vector<PokeData>T_data;
	UserInfo::getInstance()->setFirstPoke(T_data);
	UserInfo::getInstance()->setFirstType(-1);
	safe_delete_list(nobankeridlist);
	safe_delete_list(idlist);
	safe_delete_list(clientPokeData);
	safe_delete_list(recvObjPokeList);
	safe_delete_list(donelist);//清空完成列表
	delete instance;
}
LocalGameServer::~LocalGameServer()
{

}
LocalGameServer* LocalGameServer::getInstance()
{
	if (instance==NULL)
	{
		instance=new LocalGameServer();
		return instance;
	}
	return instance;
}
int LocalGameServer::getWhoBigId()
{
	int winId=-1;
	if (!clientPokeData.empty())
	{
		if (clientPokeData.size()==4)
		{
			//clientPokeData.clear();
		}
		winId=GamePokeManager::getInstance()->compareWhoBig(clientPokeData,idlist,UserInfo::getInstance()->getType());
	}
	return winId;
}
int LocalGameServer::getClientDataSize()
{
	return (int)clientPokeData.size();
}
int LocalGameServer::getClientPokeData(int id,std::vector<PokeData> data)
{
	for(int i=1;i<data.size();i++)
	{
		//("robot id = %d poke = %d type = %d",id,data[i].data,data[i].type);
	}
	if (UserInfo::getInstance()->getFirstType()==-1)
	{
		if (data.size()>0)
			UserInfo::getInstance()->setFirstType(data[0].type);
		UserInfo::getInstance()->setFirstPoke(data);
	}
	clientPokeData[id]=data;
	idlist.push_back(id);
	int winId=GamePokeManager::getInstance()->compareWhoBig(clientPokeData,idlist,UserInfo::getInstance()->getType());
	
	auto scene=Director::getInstance()->getRunningScene();
	if(!scene->getChildByTag(SHOW_OUT_ID))
	{
		scene->addChild(node,1000,SHOW_OUT_ID);
	}
	//
	getCountList(id,data);
	node->ShowPoke(data,id);
	//CommonUtils::ShowPoke(data,id);
	if (clientPokeData.size()==4)
	{
		//clientPokeData.clear();
		node->ShowPoke(data,id,true);
		std::vector<PokeData>T_data;
		UserInfo::getInstance()->setFirstPoke(T_data);
		UserInfo::getInstance()->setFirstType(-1);
		//si ren chu pai hou huo qu who big;
		//si zi ji de hua chu wan xia shou pai zai tong zhi xia jia chu pai.
		EndPokeData _lastdata;
		_lastdata.big=winId;
		for(int i=0;i<clientPokeData[winId].size();i++)
			_lastdata.lastdata.push_back(clientPokeData[winId][i]);
		
		UserInfo::getInstance()->setIEndData(_lastdata);


		return winId;
	}
	return 5;//biao shi si ren you ren hai mei chu wan pai ,tong zhi xia shou jiu shi le.
}
int LocalGameServer::getScore()
{
	//一句算一次分才行
	int key=getWhoBigId();
	int banker=UserInfo::getInstance()->getBanker();


	if (key==1||key==3)
	{
		if (banker==0||banker==2)
		{
			rightscore+=rightvalue;
		}
	}
	if (key==2||key==0)
	{
		if (banker==1||banker==3)
		{
			leftscore+=rightvalue;
		}
	}
	
	//log(">>>>>>>>>>>>socre = %d",score);
	//idlist.clear();
	//clientPokeData.clear();
	if (banker==0||banker==2)
		return rightscore;
	if (banker==1||banker==3)
		return leftscore;
	return 0;
}
void LocalGameServer::getCountList(int id,std::vector<PokeData>&data)
{
	for (int i=0;i<data.size();i++)
	{
		if (data[i].data==4)
		{
			rightvalue+=5;
			log("score");
			UserInfo::getInstance()->setIsExistCount(true);
		}
		if (data[i].data==12)
		{
			rightvalue+=10;
			log("score");
			UserInfo::getInstance()->setIsExistCount(true);
		}
		if (data[i].data==9)
		{
			UserInfo::getInstance()->setIsExistCount(true);
			rightvalue+=10;
			log("score");
		}
	}
}
int LocalGameServer::calcLastScore()
{

	return 0;
}
std::vector<PokeData> LocalGameServer::getClientBigData(int id)
{
	
	if (!clientPokeData.empty())
	{
		if (clientPokeData.find(id)!=clientPokeData.end())
		{
			return clientPokeData.find(id)->second;
		}
	}
	std::vector<PokeData> data;
	return data;
}
int LocalGameServer::getCurrentDealPokeDone()
{
	std::map<int,std::vector<PokeData>>::iterator it=clientPokeData.end();
	return it->first;
}
int LocalGameServer::getCurrentPokeCount()
{
	if (clientPokeData.empty())
	{
		return 0;
	}
	std::map<int,std::vector<PokeData>>::iterator it=clientPokeData.begin();
	std::vector<PokeData> data=it->second;
	return (int)data.size();
}
void LocalGameServer::register_services(int id,Ref* obj,deal_done_func func)
{
	PokeReceiver recv;
	recv.ob=obj;
	recv.func=func;
	recvObjPokeList.insert(std::pair<int,PokeReceiver>(id,recv));
}
void LocalGameServer::deal_done(int id)
{
	UserInfo::getInstance()->setCount((int)clientPokeData.size());
	int key=0;
	
	switch (id)
	{
	case 0:
		key=3;
		break;
	case 1:
		key=0;
		break;
	case 2:
		key=1;
		break;
	case 3:
		key=2;
		break;
	}
	int big=checkFour();
	if (big!=-1)
	{
		key=big;
	}
	
	if (recvObjPokeList.find(key)!=recvObjPokeList.end())
	{
		//log("out id = %d",key);
		PokeReceiver recv=recvObjPokeList.find(key)->second;
		(recv.ob->*recv.func)(recv.ob,key);
	}
}
void LocalGameServer::deal_banker()
{
	int key=0;
	key=UserInfo::getInstance()->getBanker();
	int cmd=5;
	for (std::map<int,PokeReceiver>::iterator it=recvObjPokeList.begin();it!=recvObjPokeList.end();++it)
	{
		if (it->first!=key)
		{
			PokeReceiver recv=it->second;
			(recv.ob->*recv.func)(recv.ob,cmd);
		}
	}
}
//处理扣底牌流程
void LocalGameServer::deal_banker_poke(int id)
{
	nobankeridlist.push_back(id);
	if (nobankeridlist.size()==3)
	{
		int key=0;
		key=UserInfo::getInstance()->getBanker();
		int cmd=6;
		if (recvObjPokeList.find(key)!=recvObjPokeList.end())
		{
			PokeReceiver recv=recvObjPokeList.find(key)->second;
			(recv.ob->*recv.func)(recv.ob,cmd);
		}
		nobankeridlist.clear();
	}
	
}
void LocalGameServer::deal_pokerlist()
{
	int key=0;
	key=UserInfo::getInstance()->getBanker();//发主牌
	int cmd=7;
	if (recvObjPokeList.find(key)!=recvObjPokeList.end())
	{
		PokeReceiver recv=recvObjPokeList.find(key)->second;
		(recv.ob->*recv.func)(recv.ob,cmd);
	}
}
void LocalGameServer::deal_poke_end()
{
	int key=0;
	key=UserInfo::getInstance()->getBanker();
	int cmd=9;
	for (std::map<int,PokeReceiver>::iterator it=recvObjPokeList.begin();it!=recvObjPokeList.end();++it)
	{
		/*if(it->first!=key)
		{
			PokeReceiver recv=it->second;
			(recv.ob->*recv.func)(recv.ob,cmd);	
		}*/
		PokeReceiver recv=it->second;
		(recv.ob->*recv.func)(recv.ob,cmd);	
	}
	/*if (recvObjPokeList.find(key)!=recvObjPokeList.end())
	{
		PokeReceiver recv=recvObjPokeList.find(key)->second;
		(recv.ob->*recv.func)(recv.ob,cmd);
	}*/
}
void LocalGameServer::deal_last_poke(int id)
{
	int cmd=12;
	for (std::map<int,PokeReceiver>::iterator it=recvObjPokeList.begin();it!=recvObjPokeList.end();++it)
	{
		if(id != it->first&&id==3)
		{
			PokeReceiver recv=it->second;
			(recv.ob->*recv.func)(recv.ob,cmd);	
		}
		
	}
}
void LocalGameServer::deal_poke_robot(int id)
{
	int key=0;
	key=UserInfo::getInstance()->getBanker();
	if(id!=key)
		return;
	int cmd=10;
	if (recvObjPokeList.find(key)!=recvObjPokeList.end())
	{
		PokeReceiver recv=recvObjPokeList.find(key)->second;
		(recv.ob->*recv.func)(recv.ob,cmd);
	}
}
int LocalGameServer::deal_poke_done(int id)
{
	donelist.push_back(id);
	if (donelist.size()==4)
	{
		int cmd=8;
		//tell local scene deal
		for (std::map<int,PokeReceiver>::iterator it=recvObjPokeList.begin();it!=recvObjPokeList.end();++it)
		{
			PokeReceiver recv=it->second;
			(recv.ob->*recv.func)(recv.ob,cmd);
		}
		
	}
	return (int)donelist.size();
}
int LocalGameServer::checkFour()
{

	if (!clientPokeData.empty())
	{
		if (clientPokeData.size()==4)
		{
			int key=getWhoBigId();
			
			UserInfo::getInstance()->setIsExistCount(false);
			int banker=UserInfo::getInstance()->getBanker();
		
			if (key==1||key==3)
			{
				if (banker==0||banker==2)
				{
					//代表我，网络层的话要通知每一个玩家
					int cmd=11;
					if (recvObjPokeList.find(3)!=recvObjPokeList.end())
					{
						PokeReceiver recv=recvObjPokeList.find(3)->second;
						(recv.ob->*recv.func)(recv.ob,cmd);
					}
				}
			}
			if (key==2||key==0)
			{
				if (banker==1||banker==3)
				{
					int cmd=11;
					if (recvObjPokeList.find(3)!=recvObjPokeList.end())
					{
						PokeReceiver recv=recvObjPokeList.find(3)->second;
						(recv.ob->*recv.func)(recv.ob,cmd);
					}
				}
			}
			
			idlist.clear();
			clientPokeData.clear();//清空数据推迟

			//刷新一回合的积分榜
			leftvalue=0;
			rightvalue=0;
			return key;
		}
	}
	return -1;
}