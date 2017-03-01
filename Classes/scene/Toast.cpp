#include "../scene/Toast.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
bool Toast::init()
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
void Toast::showToast(Node* node,std::string tips,Point point)
{
	Toast* t=new Toast();

	if (t&&t->init())
	{
		auto m_labelTTF=LabelTTF::create(tips,"Arial",20);
		m_labelTTF->setPosition(point);
		t->addChild(m_labelTTF,5);

		auto m_bg=Scale9Sprite::create("robot_talk.png");
		m_bg->setContentSize(Size(150,40));
		m_bg->setPosition(point);
		t->addChild(m_bg);
		node->addChild(t,200);
		t->schedule(schedule_selector(Toast::delete_out),3.0);
	}
}
void Toast::delete_out(float dt)
{
	this->removeFromParentAndCleanup(true);
}