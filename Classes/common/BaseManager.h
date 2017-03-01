#ifndef _BASE_MANAGER_H_
#define _BASE_MANAGER_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
USING_NS_CC;
class BaseManager :public Ref
{
public:
	BaseManager();
	~BaseManager();
	static BaseManager* getInstance();
	void showNode(Node* node,std::vector<int>type,const ccMenuCallback& callback,bool bAgain=false);
	void showExternPoke(Node* node,std::vector<PokeData> data,int timeout);
	void showEightPoke(Node* node,std::vector<PokeData> data,int timeout);
	//
	void showRobotPoke(Node* node,std::vector<PokeListItem> data,int id);

	Node* rootNode;
	void timeOut(Ref* obj);
	void removeTimeOut(Ref* obj);
	void showOut(Ref* obj);
	long getCurrentTime();
public:
	MenuItemSprite* getMenu(std::string strName,const ccMenuCallback& callback);
	Sprite* graylightWithCCSprite(std::string str,bool isLight);
};
#endif