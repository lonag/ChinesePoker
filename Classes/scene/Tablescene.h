#ifndef _TABLE_SCENE_H_
#define _TABLE_SCENE_H_
#include "../ccskynet/ccskynet_message.h"
#include "cocos2d.h"
USING_NS_CC;
class TableScene : Layer
{
public:
	TableScene();
	~TableScene();
	CREATE_FUNC(TableScene);
	static Scene* scene();
	virtual bool init();
protected:
	void initialition();
	void onClickFunc(Ref* b);
	void onMessageRecived(ccskynet_message* mess);
};
#endif