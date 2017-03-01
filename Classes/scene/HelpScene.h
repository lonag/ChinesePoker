#ifndef _help_scene_h_
#define _help_scene_h_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class HelpScene:public Layer
{
public:
	static Scene* scene();
	bool init();
	void createview();
	CREATE_FUNC(HelpScene);
public:
	Layout* main_ui;
	void onClick(Ref *sender, TouchEventType type);
};
#endif