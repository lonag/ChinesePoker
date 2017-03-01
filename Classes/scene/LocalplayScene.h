#ifndef _LOCAL_PLAY_SCENE_H_
#define _LOCAL_PLAY_SCENE_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
#include "../common/RootLayer.h"
#include "../robot/Robot.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
using namespace ui;
using namespace cocostudio;
USING_NS_CC;

class LocalplayScene : public RootLayer
{
public:
	LocalplayScene();
	~LocalplayScene();
	static Scene* scene();
	virtual bool init();
	virtual void initiation();
	void onClickFunc(Ref *b);
	GameRule* rule;
	void Timer(float dt);
	long startTime;
	int countTime;
	long currentTime;
	long getCurrentTime();
	CREATE_FUNC(LocalplayScene);
public:
	void playDealPokeAni(int key);
	void FreshCardNode();
	std::vector<Robot*> robotList;
	std::vector<PokePNG> roleCardPngList;
	std::vector<PokeData> playPokeList;
	std::vector<Sprite*> playPokeNodeList;
	std::vector<int>selectPokeIdList;
	std::vector<bool> isSelect;
	std::vector<Rect> playPokeRectList;
	void freshCardPngList(int size);
	int pokesize;
	void timeout(Ref* b);
	void endPokeDeal(Ref* b);
	void SelectBanker(Ref* obj);
	std::vector<int> typeidList;
	MenuItemImage* startPoke;
	MenuItemSprite* dealExternPoke;
	void showRobotPoke(std::vector<PokeData> data,int id);
public:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
public:
	void server_mess(Ref* obj,int key);
	class LocalSort:public sortObj<PokeData>
	{
	public:
		virtual unsigned int sequence(PokeData t);
	};
public:
	void showBackView();
	void backFunc(Ref* ref);
	void gameReset();
	void showBankPoke(int type);
	void ShowVS(int type);
	void ShowVsScore(int score);
	void showCallFunc(Ref* ref);
	void update(float dt);
public:
	Layout* room_ui;
};

#endif