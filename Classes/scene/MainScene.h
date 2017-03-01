#ifndef _main_scene_h_
#define _main_scene_h_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class MainScene:public Layer
{
public:
	static Scene* scene();
	bool init();
	void createview();
	CREATE_FUNC(MainScene);
public:
	Layout* main_ui;
	void onClick(Ref *sender, TouchEventType type);
};
#endif