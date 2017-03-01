#ifndef _logo_h
#define _logo_h
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class Logo:public Layer
{
public:
	static Scene* scene();
	bool init();
	void createview();
	CREATE_FUNC(Logo);
public:
	Layout* main_ui;
	void onClick(Ref* b);
};
#endif