#include "../common/CommonUtils.h"
void CommonUtils::deleteDataByKey(std::vector<PokeData>&data ,int key,int type)
{
	log("data size = %d",(int)data.size());
	int count=1;
	int deletec=0;
	for (std::vector<PokeData>::iterator it=data.begin();it!=data.end(); )
	{
		if (count==0)
		{
			return;
		}
		if (key==(*it).data&&type==(*it).type)
		{
			it=data.erase(it);
			count--;
			deletec++;
		}
		else
		{
			++it;
		}
	}
	if(deletec!=1)
	{
		log("not erase!");
	}
	log("delete size = %d",(int)data.size());
}
PokeData& CommonUtils::findKey(std::vector<PokeData>&data ,int key)
{
	//PokeData p;
	if (key<data.size())
	{
		//p=data[key];
		return data[key];
	}
    return data[0];
}
bool CommonUtils::CheckKey(std::vector<int>&data,int key)
{
	bool isExist=false;
	for (int i=0;i<data.size();i++)
	{
		if (data[i]==key)
		{
			isExist=true;
		}
	}
	return isExist;
}
void CommonUtils::GetMenu(Node* node,std::string str,std::string pngName,const ccMenuCallback& callback,int tag,int order,Point& p)
{
	auto pngSprite=Sprite::create(pngName);
	auto labelSprite=LabelTTF::create(str,"Arial",20);
	labelSprite->setPosition(Point(pngSprite->getContentSize().width/2,pngSprite->getContentSize().height/2));
	pngSprite->addChild(labelSprite,5);
	auto menuNode=MenuItemSprite::create(pngSprite,pngSprite,callback);
	menuNode->setTag(tag);
	menuNode->setPosition(p);
	auto menuLayer=Menu::create(menuNode,NULL);
	menuLayer->setPosition(Point::ZERO);
	node->addChild(menuLayer,order);
}
void CommonUtils::ShowPoke(std::vector<PokeData>& data,int id)
{
	auto winSize=Director::getInstance()->getWinSize();
	auto scene=Director::getInstance()->getRunningScene();
	for (int i=0;i<data.size();i++)
	{
		PokeData m_data=data[i];
		char str[126]={0};
		if (m_data.data>=14)
		{
			int d=1061+13*4+m_data.data-14;
			sprintf(str,"ddz/card/card_%d@2x.png",d);
			
		}
		else
		{
			int d=1061+(m_data.data-1)*4+m_data.type;
			sprintf(str,"ddz/card/card_%d@2x.png",d);
			
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
				p.y=winSize.height-100;
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
		}
		auto card=Sprite::create(str);
		card->setPosition(Point(p.x+i*38,p.y));
		scene->addChild(card,50);
	}
	data.clear();
}
Point CommonUtils::ShowTipsPoint(int id)
{
    Point p=Point(0,0);
    auto winSize=Director::getInstance()->getWinSize();

	switch (id)
	{
	case 0:
		{
			p.x=150;
			p.y=winSize.height/2+100;
		}
		break;
	case 1:
		{
			p.x=300;
			p.y=winSize.height-50;
		}
		break;
	case 2:
		{
			p.x=winSize.width-50-100;
			p.y=winSize.height/2+100;
			
		}
		break;
	case 3:
		{
			p.x=winSize.width/2;
			p.y=350;
		}
		break;
	}
	return p;
}

Point CommonUtils::ShowClockPoint(int id)
{
	Point p;
	auto winSize=Director::getInstance()->getWinSize();

	switch (id)
	{
	case 0:
		{
			p.x=183;
			p.y=354;//winSize.height/2+200;
		}
		break;
	case 1:
		{
			p.x=461;//winSize.width/2;
			p.y=619;//winSize.height-100;
		}
		break;
	case 2:
		{
			p.x=1103;//winSize.width-200;
			p.y=354;//winSize.height/2+200;
		}
		break;
	case 3:
		{
			p.x=winSize.width/2;
			p.y=350;
		}
		break;
	}
	return p;
}

void CommonUtils::ShowUserInfo(Node* node)
{

	auto size=Director::getInstance()->getWinSize();

	auto userleft=Sprite::create("res/images/userinfo/sex_man.png");
	userleft->setPosition(Point(50,size.height/2+100));
	node->addChild(userleft,15);

	auto userright=Sprite::create("res/images/userinfo/sex_man.png");
	userright->setPosition(Point(size.width-50,size.height/2+100));
	node->addChild(userright,15);


// 	auto userbottom=Sprite::create("res/images/sex_man.png");
// 	userbottom->setPosition(Point(100,450));
// 	node->addChild(userbottom,15);


	auto usertop=Sprite::create("res/images/userinfo/sex_man.png");
	usertop->setPosition(Point(200,size.height-50));
	node->addChild(usertop,15);

}
PokeData CommonUtils::checkA(std::vector<PokeData>&data,int type)
{
	PokeData m_data;
	for(std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
	{
		if(it->data==13)
		{
			if (it->type!=type)
			{
				m_data=(*it);
				return m_data;
			}
			
		}
	}
	//error not exist a;
	m_data.data=-1;
	return m_data;
}
PokeData CommonUtils::checkAAK(std::vector<PokeData>&data,int type)
{
	PokeData m_data;
	int key=-1;
	bool isExistAA=false;
	for(std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
	{
		if(it->data==13)
		{
			if (it->type!=type)
			{
				key=it->type;
			}
			
		}
	}
	if(key!=-1)
	{
		for(std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
		{
			if(it->type==key)
			{
				if(it->data==13)
				{
					isExistAA=true;
				}
			}
		
		}
	}
	if(isExistAA)
	{
		for(std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
		{
			if(it->type==key)
			{
				if(it->data==12)
				{
					m_data=(*it);
				
				}
			}
		
		}
	}
	//error not exist aak;
	m_data.data=-1;
	return m_data;
}
PokeData CommonUtils::checkX(std::vector<PokeData>&data,int id,int type)
{
	for (int i=0;i<data.size();i++)
	{
		if (id==data[i].data&&type==data[i].type)
		{
			return data[i];
		}
	}
    PokeData d;
    return d;
}
bool CommonUtils::checkMain(PokeData& data,int type)
{
	if(data.data==1)   {return true;}
	if(data.data==9)   {return true;}
	if(data.data==14)  {return true;}
	if(data.data==15)  {return true;}
	if(data.type==type){return true;}
	return false;
}
bool CommonUtils::checkExistNotMainPoke(std::vector<PokeData>& data,int type)
{
	int count=0;
	for (int i=0;i<data.size();i++)
	{
		if (!checkMain(data[i],type))
		{
			count++;
		}
	}
	if (count==0)
	{
		return true;
	}
	return false;
}