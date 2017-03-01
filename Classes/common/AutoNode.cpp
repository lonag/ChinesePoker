#include "../common/AutoNode.h"
bool AutoNode::init()
{
	bool bRet=false;
	do 
	{
		if (!Node::init())
		{
			return false;
		}
		nodePoke=NULL;
		bRet=true;
	} while (0);
	return bRet;
}
AutoNode* AutoNode::create()
{
	AutoNode* node=new AutoNode();
	if (node&&node->init())
	{
		return node;
	}
	delete node;
	return NULL;
}
void AutoNode::ShowPoke(std::vector<PokeData>& data,int id,bool remove/*=false*/)
{
	if (nodePoke==NULL)
	{
		nodePoke=Node::create();
		this->addChild(nodePoke,20,32342);
	}
	auto winSize=Director::getInstance()->getWinSize();
	for (int i=0;i<data.size();i++)
	{
		PokeData m_data=data[i];
		char str[126]={0};
		if (m_data.data>=14)
		{
			int d=1061+13*4+m_data.data-14;
			sprintf(str,"card_%d@2x.png",d);

		}
		else
		{
			int d=1061+(m_data.data-1)*4+m_data.type;
			sprintf(str,"card_%d@2x.png",d);

		}

		Point p;
		switch (id)
		{
		case 0:
			{
				p.x=300;
				p.y=winSize.height/2+100;
			}
			break;
		case 1:
			{
				p.x=winSize.width/2;
				p.y=winSize.height-200;
			}
			break;
		case 2:
			{
				p.x=winSize.width-300;
				p.y=winSize.height/2+100;
			}
			break;
		case 3:
			{
				p.x=winSize.width/2;
				p.y=350;
			}
			break;
		case 4:
			{
				p.x=winSize.width/2;
				p.y=450;
			}
			break;
		}
		auto card=Sprite::create(str);
		log("image = %s",str);
		card->setPosition(Point(p.x+i*38,p.y));
		nodePoke->addChild(card,50);
	}
	data.clear();
	if (remove)
	{
		this->schedule(schedule_selector(AutoNode::timer),2.0f);
		
	}
}
void AutoNode::timer(float dt)
{
	this->unschedule(schedule_selector(AutoNode::timer));
	this->removeChildByTag(32342);
	nodePoke=NULL;
}