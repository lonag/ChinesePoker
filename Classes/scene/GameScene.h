#ifndef _game_scene_h_
#define _game_scene_h_
#include "../common/RootLayer.h"
#include "cocos2d.h"
USING_NS_CC;
class GameScene:public RootLayer
{
public:
	static Scene* scene();
	virtual bool init();
	virtual void initiation();
	void onClickFunc(Ref* ref);
	CREATE_FUNC(GameScene);
};
#endif