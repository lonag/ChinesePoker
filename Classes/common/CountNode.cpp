#include "../common/CountNode.h"
bool CountNode::init()
{
	bool bRet=false;
	do 
	{
		if (!Node::init())
		{
			return false;
		}
		__String* str=__String::createWithFormat("%d",0);
		//str->autorelease();
		auto size=Director::getInstance()->getWinSize();
		m_count=LabelTTF::create(str->getCString(),"Arial",30);
		m_count->setPosition(Point(size.width/2+380,size.height/2+215));
		this->addChild(m_count,100);
		bRet=true;
	} while (0);
	return bRet;

}

CountNode* CountNode::create()
{
	CountNode* b=new CountNode();
	if (b&&b->init())
	{
		//b->autorelease();
		return b;
	}
	delete b;
	return nullptr;
}

void CountNode::setString(int count)
{
	__String* str=__String::createWithFormat("%d",count);
	m_count->setString(str->getCString());
}
