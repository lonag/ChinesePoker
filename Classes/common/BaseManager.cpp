#include "../common/BaseManager.h"
#include "../common/RootTimer.h"
#include "../common/UserInfo.h"
#include "../common/GraySprite.h"
#include "../game/LocalGameServer.h"

static BaseManager* instance=NULL;
BaseManager::BaseManager()
{

}
BaseManager::~BaseManager()
{

}
BaseManager* BaseManager::getInstance()
{
	if (instance==NULL)
	{
		instance=new BaseManager();
		return instance;
	}
	return instance;
}

void BaseManager::showNode(Node* node,std::vector<int>type, const ccMenuCallback& callback, bool bAgain)
{
	auto size=Director::getInstance()->getWinSize();
	auto mainbg=Sprite::create("call_bg.png");
	mainbg->setPosition(Point(size.width/2,size.height/2-70));
	node->addChild(mainbg,10);
    mainbg->setVisible(false);
	//spade heart club diamond
	auto spade=Sprite::create("spade2.png");
	spade->setPosition(Point(mainbg->getContentSize().width/2-180,mainbg->getContentSize().height/2));
	mainbg->addChild(spade);

	auto heart=Sprite::create("heart2.png");
	heart->setPosition(Point(mainbg->getContentSize().width/2-90,mainbg->getContentSize().height/2));
	mainbg->addChild(heart);

	auto club=Sprite::create("club2.png");
	club->setPosition(Point(mainbg->getContentSize().width/2,mainbg->getContentSize().height/2));
	mainbg->addChild(club);


	auto diamond=Sprite::create("diamond2.png");
	diamond->setPosition(Point(mainbg->getContentSize().width/2+90,mainbg->getContentSize().height/2));
	mainbg->addChild(diamond);

	std::vector<Point> pointList;
	pointList.push_back(Point(mainbg->getContentSize().width/2-180,mainbg->getContentSize().height/2));
	pointList.push_back(Point(mainbg->getContentSize().width/2-90,mainbg->getContentSize().height/2));
	pointList.push_back(Point(mainbg->getContentSize().width/2,mainbg->getContentSize().height/2));
	pointList.push_back(Point(mainbg->getContentSize().width/2+90,mainbg->getContentSize().height/2));

	if (!type.empty())
	{
        int dataCnt[]={0,0,0,0};
        std::string dataStr[]={"diamond1.png","spade1.png","heart1.png","club1.png"};
        int dataCm[]={1,4,3,2};//黑 红 梅 方 大小 排序是 方 黑 红 梅 0123

		for (int i=0;i<type.size();i++)
		{

			std::string str;
			switch (type[i])
			{
			case 0:
			{
				str="diamond1.png";
				dataCnt[0]+=1;
			}
			
			break;
			case 1:
			{
				str="spade1.png";
				dataCnt[1]+=1;
			}
			break;
			case 2:
			{
				str="heart1.png";
				dataCnt[2]+=1;
			}
				
			break;
			case 3:
			{
				str="club1.png";
				dataCnt[3]+=1;
			}
				
			break;
			}
			if(!bAgain)
			{
				auto m_menuitem=MenuItemImage::create(str,str,callback);
				m_menuitem->setTag(1000+type[i]);
				m_menuitem->setPosition(pointList[type[i]]);
				// create menu, it's an autorelease Ref
				auto menu = Menu::create(m_menuitem, NULL);
				menu->setPosition(Point::ZERO);
				mainbg->addChild(menu, 5);
                mainbg->setVisible(true);
			}
			

		}
		if(bAgain)
		{
			for(int i=0;i<4;i++)
			{
                if(dataCnt[i]==2&&dataCm[i]>dataCm[UserInfo::getInstance()->getBanker()])
				{
					auto m_menuitem=MenuItemImage::create(dataStr[i].c_str(),dataStr[i].c_str(),callback);
					m_menuitem->setTag(1000+i);
					m_menuitem->setPosition(pointList[i]);
					// create menu, it's an autorelease Ref
					auto menu = Menu::create(m_menuitem, NULL);
					menu->setPosition(Point::ZERO);
					mainbg->addChild(menu, 5);
                    mainbg->setVisible(true);
				}
			}
		}
	}
}

long BaseManager::getCurrentTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    	
	
}

void BaseManager::showExternPoke(Node* node,std::vector<PokeData> data, int timeout)
{
	rootNode=Node::create();
	node->addChild(rootNode,15,48493);
	RootTimer* m_tTimer=new RootTimer();
	auto size=Director::getInstance()->getWinSize();
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
		auto card=Sprite::create(str);
		card->setPosition(Point(size.width/2-120+i*30,size.height/2));
		card->setAnchorPoint(Point::ZERO);
		rootNode->addChild(card,5);
	}

	m_tTimer->timeOut(timeout,this,time_func_selector(BaseManager::timeOut));
	rootNode->addChild(m_tTimer);
}

void BaseManager::showEightPoke(Node* node, std::vector<PokeData> data, int timeout)
{
	rootNode=Node::create();
	node->addChild(rootNode,15,48493);
	RootTimer* m_tTimer=new RootTimer();
	RootTimer* show_timer=new RootTimer();
	show_timer->timeOut(timeout,this,time_func_selector(BaseManager::showOut));
	m_tTimer->timeOut(timeout+1,this,time_func_selector(BaseManager::removeTimeOut));
	rootNode->addChild(m_tTimer);
	rootNode->addChild(show_timer);
	auto size=Director::getInstance()->getWinSize();
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
		auto card=Sprite::create(str);
		card->setPosition(Point(size.width/2-120+i*30,size.height/2));
		card->setAnchorPoint(Point::ZERO);
		rootNode->addChild(card,5);
	}
	rootNode->setVisible(false);
}

void BaseManager::showOut(Ref* obj)
{
	rootNode->setVisible(true);
}

void BaseManager::showRobotPoke(Node* node, std::vector<PokeListItem> data, int id)
{
	auto m_node=Node::create();
	node->addChild(m_node,15-id);
	auto size=Director::getInstance()->getWinSize();
	int count=0;
	for (int i=0;i<data.size();i++)
	{
		
		for(int j=0;j<data[i]._list.size();j++)
		{
			
			//log("i== %d  j==%d",i,j);
			PokeData m_data=data[i]._list[j];
			char str[126]={0};
			if (m_data.data>=14)
			{
				int d=1061+13*4+m_data.data-14;
				sprintf(str,"card_%d@2x.png",d);
				//log("str %s data = %d type = %d",str,m_data.data,4);
			}
			else
			{
				int d=1061+(m_data.data-1)*4+m_data.type;
				sprintf(str,"card_%d@2x.png",d);
				//log("str %s data = %d type = %d",str,m_data.data,m_data.type);
			}
			auto k_card=Sprite::create(str);
			k_card->setScale(0.5);
			k_card->setPosition(Point(size.width/2-500+count*30,size.height/2+id*50));// 0 1 2
			k_card->setAnchorPoint(Point::ZERO);
			m_node->addChild(k_card);
			count++;
		}
		
	}
	log(">>>>>>>>>>>>>>>>>>>>>>>>>count = %d",count);
}

void BaseManager::timeOut(Ref* obj)
{
	LocalGameServer::getInstance()->deal_pokerlist();
	rootNode->removeFromParentAndCleanup(true);
}

void BaseManager::removeTimeOut(Ref* obj)
{
	rootNode->removeFromParentAndCleanup(true);
	
}

MenuItemSprite* BaseManager::getMenu(std::string strName,const ccMenuCallback& callback)
{
	auto m_sprite=Sprite::create(strName);
	//auto m_graysprite=GraySprite::create(strName.c_str());
	auto m_item=MenuItemSprite::create(m_sprite,m_sprite,m_sprite,callback);
	return m_item;
}

CCSprite* BaseManager::graylightWithCCSprite(std::string str,bool isLight)
{
	auto oldSprite=Sprite::create(str);
	CCPoint p = oldSprite->getAnchorPoint();
	oldSprite->setAnchorPoint(ccp(0,0));
	CCRenderTexture *outTexture = CCRenderTexture::create((int)oldSprite->getContentSize().width,(int)oldSprite->getContentSize().height);
	outTexture->begin();
	oldSprite->visit();
	outTexture->end();
	oldSprite->setAnchorPoint(p);

	CCImage* finalImage = outTexture->newCCImage();
	unsigned char *pData = finalImage->getData();
	int iIndex = 0;

	if(isLight)
	{
		for (int i = 0; i < finalImage->getHeight(); i ++)
		{
			for (int j = 0; j < finalImage->getWidth(); j ++)
			{
				// highlight
				int iHightlightPlus = 50;
				int iBPos = iIndex;
				unsigned int iB = pData[iIndex];
				iIndex ++;
				unsigned int iG = pData[iIndex];
				iIndex ++;
				unsigned int iR = pData[iIndex];
				iIndex ++;
				//unsigned int o = pData[iIndex];
				iIndex ++;  //‘≠¿¥µƒ æ¿˝»±…Ÿ
				iB = (iB + iHightlightPlus > 255 ? 255 : iB + iHightlightPlus);
				iG = (iG + iHightlightPlus > 255 ? 255 : iG + iHightlightPlus);
				iR = (iR + iHightlightPlus > 255 ? 255 : iR + iHightlightPlus);
				//            iR = (iR < 0 ? 0 : iR);
				//            iG = (iG < 0 ? 0 : iG);
				//            iB = (iB < 0 ? 0 : iB);
				pData[iBPos] = (unsigned char)iB;
				pData[iBPos + 1] = (unsigned char)iG;
				pData[iBPos + 2] = (unsigned char)iR;
			}
		}
	}else{
		for (int i = 0; i < finalImage->getHeight(); i ++)
		{
			for (int j = 0; j < finalImage->getWidth(); j ++)
			{
				// gray
				int iBPos = iIndex;
				unsigned int iB = pData[iIndex];
				iIndex ++;
				unsigned int iG = pData[iIndex];
				iIndex ++;
				unsigned int iR = pData[iIndex];
				iIndex ++;
				//unsigned int o = pData[iIndex];
				iIndex ++; //‘≠¿¥µƒ æ¿˝»±…Ÿ
				unsigned int iGray = 0.3 * iR + 0.4 * iG + 0.2 * iB;
				pData[iBPos] = pData[iBPos + 1] = pData[iBPos + 2] = (unsigned char)iGray;
			}
		}
	}

	CCTexture2D *texture = new CCTexture2D;
	texture->initWithImage(finalImage);
	CCSprite* newSprite = CCSprite::createWithTexture(texture);
	delete finalImage;
	texture->release();
	return newSprite;
}
