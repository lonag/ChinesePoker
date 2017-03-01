#include "../scene/GameSetting.h"
#include "../scene/LocalplayScene.h"
#include "../common/UserInfo.h"
#include "../extensions/cocos-ext.h"
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC_EXT;
USING_NS_CC;
Scene* GameSetting::scene()
{
	GameSetting* layer=GameSetting::create();
	auto m_scene=Scene::create();
	m_scene->addChild(layer,20);
	return m_scene;
}
bool GameSetting::init()
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
void GameSetting::initiation()
{
	auto size=Director::getInstance()->getWinSize();
	

	auto block_scaled = Scale9Sprite::create("res/images/shop/dialog_shop_bg.png");
    block_scaled->setPosition(size.width/2,size.height/2);
	block_scaled->setContentSize(Size(128*2, 64*3 ));
	this->addChild(block_scaled);

	auto msprite=Sprite::create("res/images/setting/setting_close.png");
	msprite->setPosition(size.width/2-50,size.height/2);
	msprite->setVisible(!UserInfo::getInstance()->getIsMusic());
	
	this->addChild(msprite,6,100);

	auto ssprite=Sprite::create("res/images/setting/setting_close.png");
	ssprite->setPosition(size.width/2+50,size.height/2);
	this->addChild(ssprite,6,101);
	ssprite->setVisible(!UserInfo::getInstance()->getIsSound());


	MenuItemImage* musicMenu=MenuItemImage::create("res/images/setting/setting_music.png","res/images/setting/setting_music.png",CC_CALLBACK_1(GameSetting::onClickFunc,this));
	musicMenu->setPosition(size.width/2-50,size.height/2);
	musicMenu->setTag(1);

	MenuItemImage* soundMenu=MenuItemImage::create("res/images/setting/setting_sound.png","res/images/setting/setting_sound.png",CC_CALLBACK_1(GameSetting::onClickFunc,this));
	soundMenu->setPosition(size.width/2+50,size.height/2);
	soundMenu->setTag(2);

	//this->addChild(fontMenu,2);


	auto menu = Menu::create(musicMenu,soundMenu, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5);
	
}
void GameSetting::onClickFunc(Ref* ref)
{
	//Director::getInstance()->replaceScene(LocalplayScene::scene());
	auto node=dynamic_cast<Node*>(ref);
	switch (node->getTag())
	{
	case 1:
		{
			if(UserInfo::getInstance()->getIsMusic())
			{
				UserInfo::getInstance()->setIsMusic(false);
				this->getChildByTag(100)->setVisible(true);
				SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			}
			else
			{
				UserInfo::getInstance()->setIsMusic(true);
				this->getChildByTag(100)->setVisible(false);
				SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/lobyy_bgMusic.mp3",true);
				
			}
		}
		break;
	case 2:
		{
			if(UserInfo::getInstance()->getIsSound())
			{
				UserInfo::getInstance()->setIsSound(false);
				this->getChildByTag(101)->setVisible(true);
				SimpleAudioEngine::getInstance()->stopAllEffects();
				
			}
			else
			{
				UserInfo::getInstance()->setIsSound(true);
				this->getChildByTag(101)->setVisible(false);
				SimpleAudioEngine::getInstance()->resumeAllEffects();
			}
		}
		break;
	default:
		break;
	}
}
