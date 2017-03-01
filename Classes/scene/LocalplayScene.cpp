#include "../scene/LocalplayScene.h"
#include "../common/BaseManager.h"
#include "../common/Clock.h"
#include "../scene/GameScore.h"
#include "../game/GameRule.h"
#include "../scene/Admob.h"
#include "../scene/GameSetting.h"
#include "../game/GamePokeManager.h"
#include "../game/LocalGameServer.h"
#include "../common/GraySprite.h"
#include "../scene/HallScene.h"
#include "../common/UserInfo.h"
#include "../robot/Robot.h"
#include "../scene/Toast.h"
#include "../common/AutoNode.h"
#include "../pay/PayPool.h"
#include "../common/Crypt.h"
#include "cocostudio/CocoStudio.h"
#include "../log/logger.h"
#include "audio/include/SimpleAudioEngine.h"
#include "../package/package.h"
#include "../common/xTextParse.h"
#include <time.h>
using namespace CocosDenshion;

//result bg tag 2001
LocalplayScene::LocalplayScene()
{

}
LocalplayScene::~LocalplayScene()
{
	safe_delete_list(roleCardPngList);
	safe_delete_list(playPokeList);
	safe_delete_list(isSelect);
	safe_delete_list(roleCardPngList);
	safe_delete_list(playPokeRectList);
	safe_delete_list(playPokeNodeList);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
}
Scene* LocalplayScene::scene()
{
	auto scene=Scene::create();
	LocalplayScene* layer=LocalplayScene::create();
	scene->addChild(layer);
	return scene;
}
bool LocalplayScene::init()
{
	bool bRet=false;
	do 
	{
		if (!RootLayer::init())
		{
			return false;
		}
		//initiation();
		rule= new GameRule();
		startTime=0;
		countTime=0;
		pokesize=0;
		startPoke=nullptr;
		dealExternPoke=nullptr;
		bRet=true;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		//Admob::getInstance()->initAd();
#endif
	} while (0);
	

	return bRet;
}
void LocalplayScene::initiation()
{
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/lobyy_bgMusic.mp3",true);
	auto size=Director::getInstance()->getWinSize();
	auto startItem = MenuItemImage::create(
		"start_game.png",
		"start_game.png",
		CC_CALLBACK_1(LocalplayScene::onClickFunc,this));
	startItem->setTag(2);
	startItem->setScale(0.5);
	startItem->setPosition(Point(size.width/2,300));


	// create menu, it's an autorelease Ref
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	
// 	Clock* clock=Clock::create(30,Point(size.width/2,300),this,time_func_selector(LocalplayScene::timeout));
// 	this->addChild(clock,10);


	

	//CommonUtils::ShowUserInfo(this);
	//Toast::showToast(this,"不叫主",Point(600,400));
	Layer* _touchGroup=Layer::create();
	this->addChild(_touchGroup);
	room_ui=static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("game_1.json"));
	room_ui->setTouchEnabled(false);
	Size screenSize = CCDirector::getInstance()->getWinSize();
	Size rootSize = room_ui->getSize();

	_touchGroup->setPosition(Point((screenSize.width - rootSize.width) / 2,
		(screenSize.height - rootSize.height) / 2));
	_touchGroup->addChild(room_ui);
	std::string help=FileUtils::getInstance()->getStringFromFile("help.txt");
	Text *alert = Text::create();
	alert->setText(help.c_str());
    alert->setFontName("Marker Felt");
    alert->setFontSize(30);
	//alert->setTextAreaSize(Size(100,500));
    alert->setColor(Color3B(159, 168, 176));
	alert->setAnchorPoint(Point::ZERO);
    alert->setPosition(Point(0, screenSize.height - alert->getSize().height * 3.125));
	room_ui->addChild(alert,10);
	


	Text* _tc = static_cast<Text*>(Helper::seekWidgetByName(room_ui, "total_goad"));
	//
	_tc->setText(__String::createWithFormat("%d",0)->getCString());
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	//Admob::getInstance()->show();
#endif
	showBackView();
	//ShowVS(2);
	//ShowVsScore(5);


	//xTextParse::getParse()->load("res.txt");
	
	this->scheduleUpdate();
}
void LocalplayScene::update(float dt)
{
	//算系统时间
	struct tm *tm; 
	time_t timep; 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	time(&timep); 
#else  
	struct timeval now;
	gettimeofday(&now, NULL); 
	timep = now.tv_sec; 
#endif  
	tm = localtime(&timep); 
	//int year = tm->tm_year + 1900;
	//int month = tm->tm_mon + 1;
	//int day = tm->tm_mday;
	int hour=tm->tm_hour; 
	int min=tm->tm_min; 
	//int second=tm->tm_sec;
	//log("%d:%d",hour,min);
	__String* _str;
	if (min<10)
		if (hour<10)
			_str=__String::createWithFormat("0%d:0%d",hour,min);
		else
			_str=__String::createWithFormat("%d:0%d",hour,min);
	else 
		if (hour<10)
			_str=__String::createWithFormat("0%d:%d",hour,min);
		else
			_str=__String::createWithFormat("%d:%d",hour,min);
	Text* timer = static_cast<Text*>(Helper::seekWidgetByName(room_ui, "Label_18"));
	timer->setText(_str->getCString());


	
}
void LocalplayScene::ShowVsScore(int score)
{
	auto size = Director::getInstance()->getWinSize();
	auto m_label=LabelTTF::create("4","Arial",30);
	m_label->setPosition(size.width-120,size.height-145);
	m_label->setAnchorPoint(Point(0,0));
	this->addChild(m_label,15);
}
void LocalplayScene::ShowVS(int type)
{
	auto size = Director::getInstance()->getWinSize();

	auto vsbg=Sprite::create("jifenban.png");//vs_bg
	vsbg->setPosition(size.width-80,size.height-30);
	vsbg->setAnchorPoint(Point(1,1));
	this->addChild(vsbg,10);


	char str[156]="/0";
	sprintf(str,"score_flag%d.png",type);
	auto pSprite=Sprite::create(str);
	pSprite->setPosition(size.width-50-93-41,size.height-105-20+40);
	this->addChild(pSprite,15);
}
void LocalplayScene::showBankPoke(int type)
{
	auto size = Director::getInstance()->getWinSize();
	char str[156]="/0";
	sprintf(str,"s_%d.png",type);
	auto pSprite=Sprite::create(str);
	pSprite->setPosition(size.width-50,size.height-50);
	this->addChild(pSprite,15);

}
void LocalplayScene::showBackView()
{
	auto size=Director::getInstance()->getWinSize();

	MenuItemImage* backBtn=MenuItemImage::create("leave_btn.png","leave_btn.png",CC_CALLBACK_1(LocalplayScene::backFunc,this));
	backBtn->setPosition(585,666);
	backBtn->setTag(1);


	MenuItemImage* backBtnReset=MenuItemImage::create("console_reset_btn.png","console_reset_btn.png",CC_CALLBACK_1(LocalplayScene::backFunc,this));
	backBtnReset->setPosition(654,666);
	backBtnReset->setTag(2);

	MenuItemImage* backBtnSet=MenuItemImage::create("hall_setting_btn.png","hall_setting_btn.png",CC_CALLBACK_1(LocalplayScene::backFunc,this));
	backBtnSet->setPosition(722,666);
	backBtnSet->setTag(3);

	auto menu = Menu::create(backBtn,backBtnReset,backBtnSet, NULL);
	menu->setPosition(Point::ZERO);
	//menu->setVisible(false);
	this->addChild(menu, 10);

}
void LocalplayScene::backFunc(Ref* ref)
{
	SimpleAudioEngine::getInstance()->playEffect("btn.mp3");
	auto node=dynamic_cast<Node*>(ref);
	switch (node->getTag())
	{
	case 1:
		{
			safe_delete_list(roleCardPngList);
			safe_delete_list(playPokeList);
			safe_delete_list(isSelect);
			safe_delete_list(roleCardPngList);
			safe_delete_list(playPokeRectList);
			safe_delete_list(playPokeNodeList);
			for(int i=0;i<robotList.size();i++)
			{
				//delete robotList[i];
			}
			safe_delete_list(robotList);
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
			Director::getInstance()->end();
		}
		break;
	case 2:
		{
			gameReset();
		}
		break;
	case 3:
		{
			this->addChild(GameSetting::scene(),20,100);
		}
		break;
	default:
		break;
	}
}
void LocalplayScene::gameReset()
{
	//release
	safe_delete_list(roleCardPngList);
	safe_delete_list(playPokeList);
	safe_delete_list(isSelect);
	safe_delete_list(roleCardPngList);
	safe_delete_list(playPokeRectList);
	safe_delete_list(playPokeNodeList);

	//reset
	rule->restart();
	LocalGameServer::getInstance()->restart();
	playPokeList.clear();
	auto scene=Director::getInstance()->getRunningScene();
	for(int id=0;id<3;id++)
	{
		if (scene->getChildByTag(23457+id))
		{
			scene->removeChildByTag(23457+id);
		}
	}
	
	rule->dealPoleAnimation();
	startTime=getCurrentTime();
	this->schedule(schedule_selector(LocalplayScene::Timer));
	

	playPokeList = rule->getRolePokeList(3);
	std::map<int,int> worldID;
	worldID.insert(std::pair<int,int>(0,0));//xi
	worldID.insert(std::pair<int,int>(1,1));//bei
	worldID.insert(std::pair<int,int>(2,2));//dong
	worldID.insert(std::pair<int,int>(3,3));//nan and local role
	UserInfo::getInstance()->setRoleWorldId(worldID);
	pokesize=(int)playPokeList.size()-1;
	
	for(int i=0;i<robotList.size();i++)
	{
		//delete robotList[i];
	}
	robotList.clear();
	Robot* bot=new Robot(rule->getRolePokeList(0),0);
	Robot* bot1=new Robot(rule->getRolePokeList(1),1);
	Robot* bot2=new Robot(rule->getRolePokeList(2),2);
	robotList.push_back(bot);
	robotList.push_back(bot1);
	robotList.push_back(bot2);
	LocalGameServer::getInstance()->register_services(3,this,deal_done_selector( LocalplayScene::server_mess));
}

static int pokeType(PokeData& _data)
{
	if(_data.data==1) {return 4;}
	else if(_data.data==9) {return 4;}
	else if(_data.data>=14) {return 4;}

	//
	return _data.type;
}


//观察者模式
void LocalplayScene::server_mess(Ref* obj,int key)
{
	log("server mess key = %d",key);
	if (key>3)
	{
		switch (key)
		{
		case 4:
			break;
		case 5:
			{
				LocalGameServer::getInstance()->deal_banker_poke(3);//不反主
				UserInfo::getInstance()->setEightPoke(rule->getExternPoke());//底牌数据初始化
			}
			break;
		case 6://显示底牌
			{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
				//Admob::getInstance()->hide();
#endif
				//bottom poke
				BaseManager::getInstance()->showExternPoke(this,rule->getExternPoke(),1);
			}
			break;
		case 7:// kou di show
			{

				playPokeList.clear();
				playPokeList=rule->getExternPoke(3);
				isSelect.clear();
				for (int i=0;i<playPokeList.size();i++)
				{
					isSelect.push_back(false);
				}

				std::sort(playPokeList.begin(),playPokeList.end(),LocalSort());
				playPokeRectList.clear();
				playPokeNodeList.clear();
				freshCardPngList(-1);
				FreshCardNode();

				
				auto size=Director::getInstance()->getWinSize();

				dealExternPoke = BaseManager::getInstance()->getMenu(
					"dialog_btn.png",
					CC_CALLBACK_1(LocalplayScene::onClickFunc,this));
				dealExternPoke->setTag(4);
				dealExternPoke->setPosition(Point(size.width/2,350));
				dealExternPoke->setEnabled(false);


				auto m_label=LabelTTF::create(LoadString(str_koudi),"Arial",30);
				m_label->setPosition(Point(dealExternPoke->getContentSize().width/2,dealExternPoke->getContentSize().height/2));
				dealExternPoke->addChild(m_label);
				// create menu, it's an autorelease Ref
				auto menu = Menu::create(dealExternPoke, NULL);
				menu->setPosition(Point::ZERO);
				this->addChild(menu, 10);
			}
			break;
		case 8:   //结算积分已经重新开始
			{
				CallLater(this,4,time_func_selector(LocalplayScene::endPokeDeal));

				//展示最后的底牌出来
				BaseManager::getInstance()->showEightPoke(this,UserInfo::getInstance()->getEightPoke(),2);//唉，方法不可以乱用，自找麻烦啊
				EndPokeData _last=UserInfo::getInstance()->getIEndData();
				int _type=pokeType(_last.lastdata[0]);
				//int _size=_last.lastdata.size();
				std::vector<PokeData> eightdata=UserInfo::getInstance()->getEightPoke();
				int _bank=UserInfo::getInstance()->getBanker();
				int scorecnt=0;
				if(_type==_bank||_type==4)//最后是主牌才算分的哦
				{
					for(int i=0;i<eightdata.size();i++)
					{
						if(eightdata[i].data==9||eightdata[i].data==12)
							scorecnt+=10;
						if(eightdata[i].data==4)
							scorecnt+=5;
					}
				
					if(_bank==1||_bank==3)
					{
						if(_last.big==2||_last.big==0)
							scorecnt+=LocalGameServer::getInstance()->getScore();
					}
					else
					{
						if(_last.big==1||_last.big==3)
							scorecnt+=LocalGameServer::getInstance()->getScore();
					}
					Text* _tc = static_cast<Text*>(Helper::seekWidgetByName(this->room_ui, "total_goad"));
					//log("score = %d",LocalGameServer::getInstance()->getScore());
					_tc->setText(__String::createWithFormat("%d",scorecnt)->getCString());
				}
				else
				{
					Text* _tc = static_cast<Text*>(Helper::seekWidgetByName(this->room_ui, "total_goad"));
					//log("score = %d",LocalGameServer::getInstance()->getScore());
					_tc->setText(__String::createWithFormat("%d",LocalGameServer::getInstance()->getScore())->getCString());
				}

			}
			break;
		case 9:
			{
				std::sort(playPokeList.begin(),playPokeList.end(),LocalSort());
				playPokeRectList.clear();
				playPokeNodeList.clear();
				freshCardPngList(-1);
				FreshCardNode();

				//LocalGameServer::getInstance()->getClientPokeData(3,m_data);
				//LocalGameServer::getInstance()->deal_done(3);

				auto size=Director::getInstance()->getWinSize();


				startPoke = MenuItemImage::create(
					"dialog_btn.png",
					"dialog_btn.png",
					CC_CALLBACK_1(LocalplayScene::onClickFunc,this));
				startPoke->setTag(3);
				startPoke->setPosition(Point(size.width/2,350));
				startPoke->setVisible(true);

				auto m_poke_label=LabelTTF::create(LoadString(str_chupai),"Arial",30);
				m_poke_label->setPosition(Point(startPoke->getContentSize().width/2,startPoke->getContentSize().height/2));
				startPoke->addChild(m_poke_label);

				auto menu = Menu::create(startPoke, NULL);
				menu->setPosition(Point::ZERO);
				this->addChild(menu, 10);
				//node->getParent()->removeFromParentAndCleanup(true);
			}
			break;
		case 11://刷新对家的得分
			{
				Text* _tc = static_cast<Text*>(Helper::seekWidgetByName(this->room_ui, "total_goad"));
				//log("score = %d",LocalGameServer::getInstance()->getScore());
				_tc->setText(__String::createWithFormat("%d",LocalGameServer::getInstance()->getScore())->getCString());
			}
			break;
		case 12://直接出最后一手牌
			{
				//报错
				if(playPokeList.size()==0)
					log("playPokeList size == 0 ");
				LocalGameServer::getInstance()->getClientPokeData(3,playPokeList);
				playPokeList.clear();
				roleCardPngList.clear();
				FreshCardNode();
				LocalGameServer::getInstance()->deal_poke_done(3);
			}
			break;
		}
		return;
	}
	else
	{
		int count=UserInfo::getInstance()->getCount();
		if(count==4)
		{
			if (startPoke!=nullptr)
			{
				startPoke->runAction(Sequence::create(DelayTime::create(2.0),CallFuncN::create(CC_CALLBACK_1(LocalplayScene::showCallFunc,this)),NULL));
				log("true");
				//startPoke->setVisible(true);
			}
		}
		else
		{
			if (startPoke!=nullptr)
			{
				//startPoke->runAction(Sequence::create(DelayTime::create(2.0),CallFuncN::create(CC_CALLBACK_1(LocalplayScene::showCallFunc,this)),NULL));
				log("true");
				startPoke->setVisible(true);
			}
		}
		
	}
	//CommonUtils::GetMenu(this,"game","res/images/dialog/dialog_btn.png",CC_CALLBACK_1(LocalplayScene::onClickFunc,this),3,5,Point(200,450));
}
void LocalplayScene::endPokeDeal(Ref* b)
{
	auto node =dynamic_cast<Node*>(b);
	node->removeFromParent();

	this->addChild(GameScore::scene(),40);//game score

	//show game over node;
	auto size=Director::getInstance()->getWinSize();
	auto startItem = MenuItemImage::create(
		"start_game.png",
		"start_game.png",
		CC_CALLBACK_1(LocalplayScene::onClickFunc,this));
	startItem->setTag(2);
	startItem->setScale(0.5);
	startItem->setPosition(Point(size.width/2,300));


	// create menu, it's an autorelease Ref
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
	
}
void LocalplayScene::showCallFunc(Ref* ref)
{
	startPoke->setVisible(true);
}
void LocalplayScene::timeout(Ref* b)
{
	auto node=dynamic_cast<Node*>(b);
	if (this->getChildByTag(23431))
	{
		this->removeChildByTag(23431);
	}
	node->removeFromParentAndCleanup(true);
	log("time out");

}
//fa pai jiao zhu
void LocalplayScene::Timer(float dt)
{
	
	currentTime=getCurrentTime();
	if (currentTime>=startTime+countTime)//运行一次后赋值
	{  
		countTime=120;
		playDealPokeAni(pokesize);
		pokesize--;
		if (pokesize<0)
		{
			this->unschedule(schedule_selector(LocalplayScene::Timer));
			auto size=Director::getInstance()->getWinSize();
             if (this->getChildByTag(23431))
             {
             	this->removeChildByTag(23431);
             }
			if(UserInfo::getInstance()->getBanker()!=3)//显示等待叫主倒计时
            {
                Clock* clock=Clock::create(10,Point(size.width/2,size.height/2),this,time_func_selector(LocalplayScene::timeout));
                this->addChild(clock,10);

                if (this->getChildByTag(23431))
				{
					this->removeChildByTag(23431);
				}
				auto node=Node::create();
				this->addChild(node,10,23431);
				
				BaseManager::getInstance()->showNode(node,typeidList,CC_CALLBACK_1(LocalplayScene::SelectBanker,this),true);
            }
				
			for (int i=0;i<playPokeRectList.size();i++)
			{
				isSelect.push_back(false);
			}
			
            log("banker = %d",UserInfo::getInstance()->getBanker());
			LocalGameServer::getInstance()->deal_banker();
		}
		startTime=getCurrentTime();
		
		//log("timer count");
	}

}
//sort poke
unsigned int LocalplayScene::LocalSort::sequence(PokeData data)
{
	int value=0;

	//type 6- 9 data 1
	if (data.data==1)
	{
		value+=data.data+4;
		value+=data.type+2;
	}
	else if(data.data<=13&&data.data>1)
	{
		//2-5
		if (data.data==9)
		{
			value+=data.data-8;
			value+=data.type+1;
		}
		else
		{
			if (data.type==UserInfo::getInstance()->getType())
			{
				value+=data.data*10+10;
				//log("value = %d data = %d",value,data.data);
			}
			else
			{
				value+=data.data*10;
				value+=(data.type+1)*1000;
				if (data.type==0)
				{
					//log("type 0 value = %d data = %d",value,data.data);
				}
			}
		}

	}
	//joker type 0 1 data 15 14
	else if (data.data==14)
	{
		value+=data.data-14;
		value+=data.type-4;
	}
	//0
	else if (data.data==15)
	{
		value+=data.data-15;
		value+=data.type-5;
	}
	//value+=data.type*1000;
	//value+=data.color;
	return value;
}
long LocalplayScene::getCurrentTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}
void LocalplayScene::onClickFunc(Ref *b)
{
	//SimpleAudioEngine::getInstance()->playEffect("sound/btn.mp3");
	auto node= dynamic_cast<Node*>(b);
	int tag=node->getTag();
	switch (tag)
	{
	case 1:
		break;
	case 2://start game
		{

			gameReset();//即是开始又是重新开始
			//LocalGameServer::getInstance()->register_services(3,this,deal_done_selector( LocalplayScene::server_mess));

			node->setVisible(false);
			log("start game");

			//rule->dealPoleAnimation();
			//startTime=getCurrentTime();
			//this->schedule(schedule_selector(LocalplayScene::Timer));
			////card_1061@2x.png
			////playDealPokeAni();
			//playPokeList = rule->getRolePokeList(3);
			//std::map<int,int> worldID;
			//worldID.insert(std::pair<int,int>(0,0));//xi
			//worldID.insert(std::pair<int,int>(1,1));//bei
			//worldID.insert(std::pair<int,int>(2,2));//dong
			//worldID.insert(std::pair<int,int>(3,3));//nan and local role
			//UserInfo::getInstance()->setRoleWorldId(worldID);
			//
			////开始游戏，不代表要处理发牌了，暂定为开始发牌，改一下设定
	

			//pokesize=playPokeList.size()-1;
			//Robot* bot=new Robot(rule->getRolePokeList(0),0);
			//Robot* bot1=new Robot(rule->getRolePokeList(1),1);
			//Robot* bot2=new Robot(rule->getRolePokeList(2),2);

			//robotList.push_back(bot);
			//robotList.push_back(bot1);
			//robotList.push_back(bot2);
		}
		break;
	case 3: //start poke
		{
			
			std::vector<PokeData>m_data;
			for (int i=0;i<isSelect.size();i++)
			{
				if (isSelect[i])
				{
					PokeData data=playPokeList[isSelect.size()-i-1];
					m_data.push_back(data);
					//CommonUtils::deleteDataByKey(playPokeList,data.data,data.type);
				}
				
			}
			if (m_data.size()>0)
			{
				if (GamePokeManager::getInstance()->isCanDonePoke(m_data,playPokeList))
				{
					for (int i=0;i<m_data.size();i++)
					{
						CommonUtils::deleteDataByKey(playPokeList,m_data[i].data,m_data[i].type);
					}

					isSelect.clear();
					for (int i=0;i<playPokeList.size();i++)
					{
						isSelect.push_back(false);
					}
					roleCardPngList.clear();

					for (int i=(int)playPokeList.size()-1;i>=0;i--)
					{
						PokeData m_data=playPokeList[i];
						if (m_data.data>=14)
						{
							int d=1061+13*4+m_data.data-14;
							char str[126]={0};
							sprintf(str,"card_%d@2x.png",d);
							PokePNG strpng;
							strpng.strpng=str;
							strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
							roleCardPngList.push_back(strpng);

						}
						else
						{
							int d=1061+(m_data.data-1)*4+m_data.type;
							char str[126]={0};
							sprintf(str,"card_%d@2x.png",d);
							PokePNG strpng;
							strpng.strpng=str;
							strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
							roleCardPngList.push_back(strpng);
						}
					}

				}
				else
				{
					m_data.clear();
				}

			}
			
			if (m_data.size()>0)
			{
				node->setVisible(false);
				FreshCardNode();
				LocalGameServer::getInstance()->getClientPokeData(3,m_data);
				int size=0;
				if (playPokeList.size()==0)
				{
					size=LocalGameServer::getInstance()->deal_poke_done(3);
					LocalGameServer::getInstance()->deal_last_poke(3);
				}
				else
				{
					LocalGameServer::getInstance()->deal_done(3);
				}
				
			}
		}
		break;
	case 4://kou di
		{
			std::vector<PokeData>m_data;
			for (int i=0;i<isSelect.size();i++)
			{
				if (isSelect[i])
				{
					PokeData data=playPokeList[isSelect.size()-i-1];
					m_data.push_back(data);
					CommonUtils::deleteDataByKey(playPokeList,data.data,data.type);
				}

			}
			UserInfo::getInstance()->setEightPoke(m_data);
			m_data.clear();
			isSelect.clear();
			for (int i=0;i<playPokeList.size();i++)
			{
				isSelect.push_back(false);
			}
			roleCardPngList.clear();

			for (int i=(int)playPokeList.size()-1;i>=0;i--)
			{
				PokeData m_data=playPokeList[i];
				if (m_data.data>=14)
				{
					int d=1061+13*4+m_data.data-14;
					char str[126]={0};
					sprintf(str,"card_%d@2x.png",d);
					PokePNG strpng;
					strpng.strpng=str;
					strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
					roleCardPngList.push_back(strpng);

				}
				else
				{
					int d=1061+(m_data.data-1)*4+m_data.type;
					char str[126]={0};
					sprintf(str,"card_%d@2x.png",d);
					PokePNG strpng;
					strpng.strpng=str;
					strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
					roleCardPngList.push_back(strpng);
				}

			}
			FreshCardNode();
			//LocalGameServer::getInstance()->getClientPokeData(3,m_data);
			//LocalGameServer::getInstance()->deal_done(3);

			auto size=Director::getInstance()->getWinSize();


			startPoke = MenuItemImage::create(
				"dialog_btn.png",
				"dialog_btn.png",
				CC_CALLBACK_1(LocalplayScene::onClickFunc,this));
			startPoke->setTag(3);
			startPoke->setPosition(Point(size.width/2,350));
			startPoke->setVisible(true);

			auto m_poke_label=LabelTTF::create(LoadString(str_chupai),"Arial",30);
			m_poke_label->setPosition(Point(startPoke->getContentSize().width/2,startPoke->getContentSize().height/2));
			startPoke->addChild(m_poke_label);

			auto menu = Menu::create(startPoke, NULL);
			menu->setPosition(Point::ZERO);
			this->addChild(menu, 10);
            node->getParent()->removeFromParentAndCleanup(true);
			LocalGameServer::getInstance()->deal_poke_end();//扣底牌结束，开始牌整理robot

		}
		break;
	}
}
void LocalplayScene::showRobotPoke(std::vector<PokeData> data,int id)
{
	auto m_node=Node::create();
	this->addChild(m_node,5-id);
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
		auto k_card=Sprite::create(str);
		k_card->setScale(0.5);
		k_card->setPosition(Point(size.width/2-350+i*30,size.height/2+id*50));
		k_card->setAnchorPoint(Point::ZERO);
		m_node->addChild(k_card);
	}

}
void LocalplayScene::freshCardPngList(int size)
{
	roleCardPngList.clear();
	for (int i=(int)playPokeList.size();i>size+1;i--)
	{
		PokeData m_data=playPokeList[i-1];
		if (m_data.data>=14)
		{
			int d=1061+13*4+m_data.data-14;
			char str[126]={0};
			sprintf(str,"card_%d@2x.png",d);
			PokePNG strpng;
			strpng.strpng=str;
			strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
			roleCardPngList.push_back(strpng);

		}
		else
		{
			int d=1061+(m_data.data-1)*4+m_data.type;
			char str[126]={0};
			sprintf(str,"card_%d@2x.png",d);
			PokePNG strpng;
			strpng.strpng=str;
			strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
			roleCardPngList.push_back(strpng);
		}
	}
	
}
void LocalplayScene::playDealPokeAni(int key)
{
	PokeData m_data=playPokeList[key];
	if (m_data.data>=14)
	{
		int d=1061+13*4+m_data.data-14;
		char str[126]={0};
		sprintf(str,"card_%d@2x.png",d);
		PokePNG strpng;
		strpng.strpng=str;
		strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
		roleCardPngList.push_back(strpng);
		
	}
	else
	{
		int d=1061+(m_data.data-1)*4+m_data.type;
		char str[126]={0};
		sprintf(str,"card_%d@2x.png",d);
		PokePNG strpng;
		strpng.strpng=str;
		strpng.isMain=CommonUtils::checkMain(m_data,UserInfo::getInstance()->getType());
		roleCardPngList.push_back(strpng);
	}
	if (this->getChildByTag(23431))
	{
		this->removeChildByTag(23431);
	}
	auto node=Node::create();
	this->addChild(node,10,23431);
	
	if (m_data.data==9)
	{
		typeidList.push_back(m_data.type);
	}
	BaseManager::getInstance()->showNode(node,typeidList,CC_CALLBACK_1(LocalplayScene::SelectBanker,this));

	FreshCardNode();
//	if(UserInfo::getInstance()->getType()!=-1)
//		return;
    if(UserInfo::getInstance()->getKingCount()==2)
        return;
	for(int i=0;i<robotList.size();i++)
	{
		
		int ret=robotList[i]->retKingType(key);
        
		if(ret!=-1)
		{
            //已经叫主的牌，只可以保主
            if((UserInfo::getInstance()->getBanker()==i)&&(UserInfo::getInstance()->getKingCount()==2)&&ret!=UserInfo::getInstance()->getType())
            {
                return;
                
            }
            for(int j=0;j<3;j++)
            {
                ImageView* _dealer = static_cast<ImageView*>(Helper::seekWidgetByName(room_ui,__String::createWithFormat("dealer_%d",j)->getCString()));
                _dealer->setVisible(false);
            }

            log("robot deal poke type = %d robot id = %d",ret,i);
			//Image_27
			ImageView* _bankerType=static_cast<ImageView*>(Helper::seekWidgetByName(room_ui, "Image_27"));
			_bankerType->loadTexture(__String::createWithFormat("s_%d.png",ret)->getCString());

			ImageView* _dealer = static_cast<ImageView*>(Helper::seekWidgetByName(room_ui,__String::createWithFormat("dealer_%d",i)->getCString()));
			_dealer->setVisible(true);
			UserInfo::getInstance()->setType(ret);
			UserInfo::getInstance()->setBanker(i);
			std::sort(playPokeList.begin(),playPokeList.end(),LocalSort());
			freshCardPngList(pokesize);
			AutoNode* m_node=AutoNode::create();
            std::vector<PokeData>datalist;
            for(int i=0;i<UserInfo::getInstance()->getKingCount();i++)
            {
                PokeData data;
                data.data=9;
                data.type=ret;
                datalist.push_back(data);
            }
		//	data.color=0;
		//	data.count=0;
			
			
			m_node->ShowPoke(datalist,4,true);
			this->addChild(m_node,100);
		}
	}
		
}
void LocalplayScene::SelectBanker(Ref* obj)
{
	//SimpleAudioEngine::getInstance()->playEffect("sound/btn.mp3");
	auto node=dynamic_cast<Node*>(obj);
	int tag=node->getTag();
	UserInfo::getInstance()->setBanker(3);
	UserInfo::getInstance()->setType(tag-1000);
	log("banker tag = %d",tag-1000);
	std::sort(playPokeList.begin(),playPokeList.end(),LocalSort());
	freshCardPngList(pokesize);
	AutoNode* m_node=AutoNode::create();

	PokeData data;
	data.data=9;
	data.type=tag-1000;
//	data.color=0;
//	data.count=0;
	std::vector<PokeData>datalist;
	datalist.push_back(data);
	m_node->ShowPoke(datalist,4,true);
	this->addChild(m_node,100);



}
void LocalplayScene::FreshCardNode()
{
	if (this->getChildByTag(23458))
	{
		playPokeNodeList.clear();
		playPokeRectList.clear();
		this->removeChildByTag(23458);
	}
	auto node=Node::create();
	node->setPosition(Point::ZERO);
	this->addChild(node,10,23458);
	auto size=Director::getInstance()->getWinSize();
	

	int off_x=0;
	int off_y=0;


	//wei zhuang jia shi
	if (roleCardPngList.size()>25)
	{
		off_x=17;
		off_y=60;
	}
	else
	{
		off_x=23;
		off_y=60;
	}
	int offset=size.width/2-roleCardPngList.size()*off_x-40;
	
	for (int i=0;i<roleCardPngList.size();i++)
	{
		auto card=Sprite::create(roleCardPngList[i].strpng.c_str());

		card->setPosition(Point(offset+i*off_x*2,off_y));
		card->setAnchorPoint(Point::ZERO);
		node->addChild(card,5);

		if (roleCardPngList[i].isMain)
		{
			auto main_poke=Sprite::create("main_card_flag.png");
			main_poke->setPosition(Point(main_poke->getContentSize().width/2,main_poke->getContentSize().height/2));
			main_poke->setAnchorPoint(Point::ZERO);
			card->addChild(main_poke);
		}
		

		int m_x=offset+i*off_x*2+off_x-15;//tou ming du 5px
		int m_y=off_y;/*+card->getContentSize().height/2;*/


		int m_width=off_x*2;
		int m_height=card->getContentSize().height;
		auto rect=Rect(m_x,m_y,m_width,m_height);
		playPokeRectList.push_back(rect);
		playPokeNodeList.push_back(card);

	}
}
bool LocalplayScene::onTouchBegan(Touch* touch, Event* event)
{
	
	Point point = touch->getLocation();
	for (int i=0;i<playPokeRectList.size();i++)
	{
		if(playPokeRectList[i].containsPoint(point))
		{
			log("touch id = %d",i);
			selectPokeIdList.push_back(i);
			if (isSelect[i]==false)
			{
				isSelect[i]=true;
			}
			else
			{
				isSelect[i]=false;
			}
			//auto card=playPokeNodeList[i];
			//card->setPositionY(500);
		}
	}
	return true;
}
void LocalplayScene::onTouchMoved(Touch* touch, Event* event)
{
	Point point = touch->getLocation();
	for (int i=0;i<playPokeRectList.size();i++)
	{
		if(playPokeRectList[i].containsPoint(point))
		{
			
			if (!CommonUtils::CheckKey(selectPokeIdList,i))
			{
				selectPokeIdList.push_back(i);
				log("move touch id = %d",i);
				if (isSelect[i]==false)
				{
					isSelect[i]=true;
				}
				else
				{
					isSelect[i]=false;
				}
			}
			
			//auto card=playPokeNodeList[i];
			//card->setPositionY(500);
		}
	}
	//log("move local");
}
void LocalplayScene::onTouchEnded(Touch* touch, Event* event)
{
	if(this->getChildByTag(100))
	{
		this->removeChildByTag(100);
	}
	for (int i=0;i<selectPokeIdList.size();i++)
	{

		auto card=playPokeNodeList[selectPokeIdList[i]];
		//card->setPositionY(500);
		if (isSelect[selectPokeIdList[i]]==false)
		{
			//SimpleAudioEngine::getInstance()->playEffect("sound/btn.mp3");
			card->runAction(MoveTo::create(0.1,Point(card->getPositionX(),card->getPositionY()-50)));
		}
		else
		{
			card->runAction(MoveTo::create(0.1,Point(card->getPositionX(),card->getPositionY()+50)));
			//SimpleAudioEngine::getInstance()->playEffect("sound/btn.mp3");
		}
		
	}
	if (selectPokeIdList.size()>0)
	{
		if (this->getChildByTag(32354))
		{
			this->removeChildByTag(32354);
		}
		auto node=Node::create();
		node->setPosition(Point::ZERO);
		this->addChild(node,5,32354);
		if (startPoke!=nullptr)
		{
			startPoke->setEnabled(true);
		}
		//CommonUtils::GetMenu(this,"game","res/images/dialog/dialog_btn.png",CC_CALLBACK_1(LocalplayScene::onClickFunc,this),3,5,Point(200,450));
	}


	std::vector<PokeData>m_data;
	if(m_data.size()>0)
		m_data.clear();
	for (int i=0;i<isSelect.size();i++)
	{
		if (isSelect[i])
		{
			PokeData data=playPokeList[isSelect.size()-i-1];
			m_data.push_back(data);
		}

	}

	if (m_data.size()==8)//八个牌选择有问题
	{
		
		if (dealExternPoke!=nullptr)
		{
			dealExternPoke->setEnabled(true);
		}	
		
	}
	else if(m_data.size()>8)
	{
		if (dealExternPoke!=nullptr)
		{
			dealExternPoke->setEnabled(false);
		}	
	}

	if (!selectPokeIdList.empty())
	{
		selectPokeIdList.clear();
	}
}
