#include "../scene/HelpScene.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/MainScene.h"
Scene* HelpScene::scene()
{
	auto scene=Scene::create();
	HelpScene* layer=HelpScene::create();
	scene->addChild(layer);
	return scene;
}
bool HelpScene::init()
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
void HelpScene::createview()
{
	Layer* _touchGroup=Layer::create();
	this->addChild(_touchGroup);
	main_ui=static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("helpui_1.json"));
	//main_ui->setTouchEnabled(false);
	Size screenSize = CCDirector::getInstance()->getWinSize();
	Size rootSize = main_ui->getSize();
	std::string helptxt=FileUtils::getInstance()->getStringFromFile("help.txt");
	Text* help=static_cast<Text*>(Helper::seekWidgetByName(main_ui, "Label_16"));
	help->setText(helptxt);
	_touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
		(screenSize.height - rootSize.height) / 2));
	_touchGroup->addChild(main_ui);
	Button *back=static_cast<Button*>(Helper::seekWidgetByName(main_ui, "Button_9"));
	back->addTouchEventListener(this, toucheventselector(HelpScene::onClick));
}
void HelpScene::onClick(Ref *sender, TouchEventType type)
{
	//back to main scene
	if (type==TOUCH_EVENT_ENDED)
	{
		Director::getInstance()->replaceScene(MainScene::scene());
	}
	
}