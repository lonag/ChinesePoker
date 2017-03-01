#include "../scene/Tablescene.h"
#include "../ccskynet/ccskynet_dispatch.h"
#include "../ccskynet/ccskynet_manager.h"
#include "Netcode.h"
TableScene::TableScene()
{
}
TableScene::~TableScene()
{

}
Scene* TableScene::scene()
{
	auto scene=Scene::create();
	TableScene* layer=TableScene::create();
	scene->addChild(layer);
	return scene;
}
bool TableScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		initialition();
		bRet=true;
	} while (0);
	return bRet;
}

	


void TableScene::initialition()
{
	auto startItem = MenuItemImage::create(
		"ddz/button/button_1020@2x.png",
		"ddz/button/button_1019@2x.png",
		CC_CALLBACK_1(TableScene::onClickFunc,this));
	startItem->setTag(2);
	startItem->setPosition(Point(200,100));

	// create menu, it's an autorelease Ref
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
void TableScene::onClickFunc(Ref* b)
{
	auto node=dynamic_cast<Node*>(b);
	int tag=node->getTag();
	switch (tag)
	{
	case 1:
		break;
	case 2:
		{
			ccskynet_message* mess=new ccskynet_message(64);
			ccskynet_manager::getInstance()->send(mess);
			ccskynet_dispatch::getInstance()->register_message("",this,mess,fnPacketfunc(&TableScene::onMessageRecived));
			mess->setCode(START_GAME);
			log("start game");
		}
		break;
	}
}
void TableScene::onMessageRecived(ccskynet_message* mess)
{

}