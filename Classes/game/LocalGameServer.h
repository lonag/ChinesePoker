#ifndef _LOCAL_GAME_SERVER_H_
#define _LOCAL_GAME_SERVER_H_
#include "cocos2d.h"
#include "../game/GameRule.h"

USING_NS_CC;
typedef void (Ref::*deal_done_func)(Ref*,int);
#define deal_done_selector(_selector) deal_done_func(&_selector)

#define safe_delete_list(_list) if (_list.size()>0)\
{\
	_list.clear();\
}
#define safe_delete_ptr(_list) if(_list.size()>0)\
{\
for(int i=1;i<_list.size();i++)\
{\
	delete _list[i];\
}\
}
/*
cmd 4 ti shi wan jia fan zhu
cmd 5 zhan shi di pai gei di zhu
cmd 6 
*/


struct PokeReceiver
{
	Ref* ob;
	deal_done_func func;
};


class LocalGameServer
{
public:

	LocalGameServer();
	~LocalGameServer();
	static LocalGameServer* getInstance();
	int getClientPokeData(int id,std::vector<PokeData> data);
	std::vector<PokeData> getClientBigData(int id);
	int getCurrentDealPokeDone();
	int getWhoBigId();
	int getCurrentPokeCount();
	int getClientDataSize();
	std::map<int,std::vector<PokeData>>clientPokeData;
	std::vector<int> idlist;
	std::vector<int> nobankeridlist;
	void restart();
	void Destory();
public:
	void register_services(int id,Ref* obj,deal_done_func func);
	void deal_done(int id);
	void deal_banker();
	//kou di
	void deal_pokerlist();
	void deal_banker_poke(int id);
	void deal_poke_end();
	void deal_poke_robot(int id);

	void deal_last_poke(int id=0);

	//show di poke
	int deal_poke_done(int id);
	std::vector<int>donelist;
	std::map<int,PokeReceiver>recvObjPokeList;
	int checkFour();
public:
	class AutoNode* node;
	/*class CountNode* c_node;*/
	void getCountList(int id,std::vector<PokeData>&data);
	int rightvalue;
	int leftvalue;
	int rightscore;
	int leftscore;
	int getScore();//1 right,2 left
	int calcLastScore();
};
#endif