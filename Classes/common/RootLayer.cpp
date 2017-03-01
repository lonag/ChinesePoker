#include "../common/RootLayer.h"
#include "AppMacros.h"
bool RootLayer::init()
{
	bool bRet=false;
	do 
	{
		if (!Layer::init())
		{
			return false;
		}
		bRet=true;
	} while (0);
	return bRet;
}
void RootLayer::exitGame(Ref* obj)
{

}
void RootLayer::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(RootLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(RootLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(RootLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	initiation();
}
void RootLayer::onExit()
{
	Layer::onExit();

}
bool RootLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void RootLayer::onTouchMoved(Touch* touch, Event* event)
{

}
void RootLayer::onTouchEnded(Touch* touch, Event* event)
{

}
void RootLayer::showTips(std::string str,TipsStyle style,Ref* obj/* =NULL */,const ccMenuCallback& callbackoK/* =NULL */,const ccMenuCallback& callbackCancell/* =NULL */)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto label=LabelTTF::create(str,"Arial", 20);
	label->setDimensions(Size(300,0));
	label->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(label,100);
	if (style==kTipsSure)
	{

	}
	else if (style==kTipsBad)
	{

	}
	else if (style==kTipsNone)
	{

	}
}