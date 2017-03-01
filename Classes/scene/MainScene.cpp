#include "../scene/MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "../scene/LocalPlayScene.h"
#include "../scene/HelpScene.h"

Scene* MainScene::scene()
{
	auto scene=Scene::create();
	MainScene* layer=MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init()
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
void MainScene::createview()
{
	Layer* _touchGroup=Layer::create();
	this->addChild(_touchGroup);
	main_ui=static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("mainui_1.json"));
	//main_ui->setTouchEnabled(false);
	Size screenSize = CCDirector::getInstance()->getWinSize();
	Size rootSize = main_ui->getSize();
	std::string helptxt=FileUtils::getInstance()->getStringFromFile("help.txt");
	_touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
		(screenSize.height - rootSize.height) / 2));
	_touchGroup->addChild(main_ui);
	Button *start_game=static_cast<Button*>(Helper::seekWidgetByName(main_ui, "start"));
	start_game->addTouchEventListener(this, toucheventselector(MainScene::onClick));

	Button *help_game=static_cast<Button*>(Helper::seekWidgetByName(main_ui, "help"));
	help_game->addTouchEventListener(this, toucheventselector(MainScene::onClick));

	Button *about_game=static_cast<Button*>(Helper::seekWidgetByName(main_ui, "about"));
	about_game->addTouchEventListener(this, toucheventselector(MainScene::onClick));
	
}
void MainScene::onClick(Ref *sender, TouchEventType type)
{
	Node *node=dynamic_cast<Node*>(sender);
	int tag=node->getTag();
	switch(tag)
	{
	case 14:
		{
			if (type==TOUCH_EVENT_ENDED)
			{
				Director::getInstance()->replaceScene(LocalplayScene::scene());
			}
		}
		break;
	case 15:
		{
			if (type==TOUCH_EVENT_ENDED)
			{
				Director::getInstance()->replaceScene(HelpScene::scene());
			}
		}
		break;
	case 16:
		{
			if (type==TOUCH_EVENT_ENDED)
			{
				//
			}
		}
		break;
	default:
		break;
	}
}
