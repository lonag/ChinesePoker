#include "../scene/GameScene.h"
#include "../scene/LocalplayScene.h"
USING_NS_CC;
Scene* GameScene::scene()
{
	GameScene* layer=GameScene::create();
	auto m_scene=Scene::create();
	m_scene->addChild(layer,20);
	return m_scene;
}
bool GameScene::init()
{
	bool bRet=false;
	do 
	{
		if (!RootLayer::init())
		{
			return false;
		}
		bRet=true;
	} while (0);
	return bRet;
}
void GameScene::initiation()
{
	auto size=Director::getInstance()->getWinSize();
	Sprite* logo=Sprite::create("res/images/beijing@2x.jpg");
	logo->setPosition(size.width/2,size.height/2);
	this->addChild(logo);

	MenuItemFont* fontMenu=MenuItemFont::create("ENTER GAME",CC_CALLBACK_1(GameScene::onClickFunc,this));
	fontMenu->setPosition(size.width/2,size.height/2);
	//this->addChild(fontMenu,2);
	auto menu = Menu::create(fontMenu, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
void GameScene::onClickFunc(Ref* ref)
{
	Director::getInstance()->replaceScene(LocalplayScene::scene());
}