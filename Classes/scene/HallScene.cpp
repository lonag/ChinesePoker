#include "../scene/HallScene.h"
#include "../pay/PayPool.h"
#include "../configs/Configs.h"
USING_NS_CC;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "protocols/PluginManager.h"
using namespace cocos2d::plugin;
#endif

enum {
	TAG_PAY_BY_ALIPAY = 100,
	TAG_PAY_BY_ND91,
};

typedef struct tagEventMenuItem {
	std::string id;
	int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
	{"BtnAlipay.png", TAG_PAY_BY_ALIPAY},
	{"BtnND91.png", TAG_PAY_BY_ND91},
};


Scene* HallScene::scene()
{
	auto scene= Scene::create();
	HallScene* layer=HallScene::create();
	scene->addChild(layer);
	return scene;
}
bool HallScene::init()
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
void HallScene::initiation()
{
// 	auto mainbg=Sprite::create("res/images/room/room_bg.png");
// 	mainbg->setPosition(Point(size.width/2,size.height/2));
// 	this->addChild(mainbg);

// 	auto size=Director::getInstance()->getWinSize();
// 	auto room_top=Sprite::create("res/images/hall/hall_top_bg.png");
// 	room_top->setPosition(Point(0,size.height));
// 	room_top->setAnchorPoint(Point(0,1));
// 	this->addChild(room_top,1);
// 
// 	auto room_bottom=Sprite::create("res/images/hall/hall_bottom_bg.png");
// 	room_bottom->setPosition(Point::ZERO);
// 	room_bottom->setAnchorPoint(Point(0,0));
// 	this->addChild(room_bottom,1);	
	//PayPool::pay();
	//PayPool::playCGVideo("demo.mp4");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	MyPurchase::getInstance()->loadIAPPlugin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	auto pEGLView = Director::getInstance()->getOpenGLView();
	Point posBR = Point(pEGLView->getVisibleOrigin().x + pEGLView->getVisibleSize().width, pEGLView->getVisibleOrigin().y);
	Point posTL = Point(pEGLView->getVisibleOrigin().x, pEGLView->getVisibleOrigin().y + pEGLView->getVisibleSize().height);

	// add a "close" icon to exit the progress. it's an autorelease object
	MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(HallScene::menuBackCallback, this));
	Size backSize = pBackItem->getContentSize();
	pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

	// create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pBackItem, NULL);
	pMenu->setPosition( Point::ZERO );
	this->addChild(pMenu, 1);

	Point posStep = Point(220, -150);
	Point beginPos = posTL + (posStep * 0.5f);
	int line = 0;
	int row = 0;
	for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
		MenuItemImage* pMenuItem = MenuItemImage::create(s_EventMenuItem[i].id.c_str(), s_EventMenuItem[i].id.c_str(),
			CC_CALLBACK_1(HallScene::eventMenuCallback, this));
		pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);

		Point pos = beginPos + Point(posStep.x * row, posStep.y * line);
		Size itemSize = pMenuItem->getContentSize();
		if ((pos.x + itemSize.width / 2) > posBR.x)
		{
			line += 1;
			row = 0;
			pos = beginPos + Point(posStep.x * row, posStep.y * line);
		}
		row += 1;
		pMenuItem->setPosition(pos);
	}
#endif

}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
void HallScene::eventMenuCallback(Ref* pSender)
{
	MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;
	TProductInfo pInfo;
	MyPurchase::MyPayMode mode = (MyPurchase::MyPayMode) (pMenuItem->getTag() - TAG_PAY_BY_ALIPAY + 1);
	pInfo["productName"] = "100金币";
	pInfo["productPrice"] = "0.01";
	pInfo["productDesc"] = "100个金灿灿的游戏币哦";
	pInfo["Nd91ProductId"] = "685994";
	log("pay callback");
	MyPurchase::getInstance()->payByMode(pInfo, mode);
}

void HallScene::menuBackCallback(Ref* pSender)
{
	MyPurchase::purgePurchase();

	//Scene* newScene = HelloWorld::scene();
	//Director::getInstance()->replaceScene(newScene);
}
#endif