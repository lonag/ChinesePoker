#ifndef _game_setting_h_
#define _game_setting_h_
#include "../common/RootLayer.h"
#include "cocos2d.h"
USING_NS_CC;
class GameSetting:public RootLayer
{
public:
	static Scene* scene();
	virtual bool init();
	virtual void initiation();
	void onClickFunc(Ref* ref);
	CREATE_FUNC(GameSetting);
public:
	virtual bool onTouchBegan(Touch* touch, Event* event){return false;}
};
#endif