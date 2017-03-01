#include "../scene/Logo.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/LocalPlayScene.h"
#include "../scene/HelpScene.h"
#include "../common/Clock.h"
#include "../scene/MainScene.h"
Scene* Logo::scene()
{
	auto scene=Scene::create();
	Logo* layer=Logo::create();
	scene->addChild(layer);
	return scene;
}
bool Logo::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		createview();
		bRet=true;
	} while (0);
	return bRet;
}
void Logo::createview()
{
	Color4B colr=Color4B(225,225,225,225);
	auto colorlayer=LayerColor::create(colr);
	this->addChild(colorlayer);
	auto sprite=Sprite::create("karjoy.png");
	auto winSize =Director::getInstance()->getWinSize();
	sprite->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(sprite,1);
	CallLater(this,1,time_func_selector(Logo::onClick));
	
}
void Logo::onClick(Ref* b)
{
	Director::getInstance()->replaceScene(MainScene::scene());
}
