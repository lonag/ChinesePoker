#include "../robot/Robot.h"
#include "../game/LocalGameServer.h"
#include "../game/RobotRule.h"
#include "../common/CommonUtils.h"
#include "../scene/Toast.h"
#include "../common/Clock.h"
#include "../common/UserInfo.h"
#include "../game/PokeRule.h"
#include "../common/BaseManager.h"
#include "../log/logger.h"
Robot::Robot(std::vector<PokeData> robotPokeList,int id)
{
	this->robotPokeList=robotPokeList;
	this->id=id;
	ai=new NewRobot();
	ai->getListData(robotPokeList);
	
	LocalGameServer::getInstance()->register_services(id,this,deal_done_selector(Robot::server_mess));
	//auto scene=Director::getInstance()->getRunningScene();
	//auto node=Node::create();
	//scene->addChild(node,10-id,23457+id);
	//BaseManager::getInstance()->showRobotPoke(node,ai->GetListItem(),id);//20140831
}
Robot::~Robot()
{
}
void Robot::server_mess(Ref* obj,int key)
{
	log("robot key = %d",key);
	if (key>4)
	{
		switch (key)
		{
		case 5:
			{
				Clock* clock=Clock::create(10,Point(CommonUtils::ShowClockPoint(id)),this,time_func_selector(Robot::banker_time_out));
				auto scene=Director::getInstance()->getRunningScene();
				
				scene->addChild(clock,10);
			}
			break;
		case 6:
			{
				LocalGameServer::getInstance()->deal_pokerlist();//底牌展示完成
			}
			break;
		case 7:
			{
				std::vector<PokeData> externPoke = UserInfo::getInstance()->getEightPoke();
				for(int i=0;i<externPoke.size();i++)
				{
					robotPokeList.push_back(externPoke[i]);
				}
				std::sort(robotPokeList.begin(),robotPokeList.end(),Robot());
				ai->pokeFilerPool(robotPokeList);//延迟调用,主确定后再说，先分组用于叫主
				ai->dealBankerPoke();
				LocalGameServer::getInstance()->deal_poke_end();//扣底牌结束，开始牌整理robot
			}
			break;
		case 8:
			{

			}
			break;
		case 9://发牌结束了
			{
				//等待扣底牌后发这条指令
				//整理后再显示出来
				if(UserInfo::getInstance()->getBanker()!=id)
				{
					std::sort(robotPokeList.begin(),robotPokeList.end(),Robot());
					ai->pokeFilerPool(robotPokeList);//延迟调用,主确定后再说，先分组用于叫主
				}
				auto scene=Director::getInstance()->getRunningScene();
				auto node=Node::create();
				scene->addChild(node,10-id,23457+id);
				BaseManager::getInstance()->showRobotPoke(node,ai->GetListItem(),id);//20140831
				LocalGameServer::getInstance()->deal_poke_robot(id);
			}
			break;
		case 10:
			{
				//通知庄家出牌
				log("deal id = %d",id);
				auto size=Director::getInstance()->getWinSize();
	
				Clock* clock=Clock::create(2,Point(CommonUtils::ShowClockPoint(id)),this,time_func_selector(Robot::timeout));
				auto scene=Director::getInstance()->getRunningScene();
				scene->addChild(clock,10);
			}
			break;
		case 12://处理最后一首牌，不要倒计时等待，直接出牌
			{
				donePoke();
			}
			break;
		}
		return;
	}
	log("deal id = %d",id);
	auto size=Director::getInstance()->getWinSize();
	
	Clock* clock=Clock::create(3,Point(CommonUtils::ShowClockPoint(id)),this,time_func_selector(Robot::timeout));
	auto scene=Director::getInstance()->getRunningScene();
	scene->addChild(clock,10);
	
}
void Robot::banker_time_out(Ref* b)
{
	auto node=dynamic_cast<Node*>(b);
	node->removeFromParentAndCleanup(true);
	auto scene=Director::getInstance()->getRunningScene();
	Toast::showToast(scene,"hello",CommonUtils::ShowTipsPoint(id));
	LocalGameServer::getInstance()->deal_banker_poke(id);
}
void Robot::timeout(Ref* b)
{
	auto node=dynamic_cast<Node*>(b);
	node->removeFromParentAndCleanup(true);
	log("time out");
	int bigId=LocalGameServer::getInstance()->getWhoBigId();
	checkPokeType(LocalGameServer::getInstance()->getClientBigData(bigId),bigId);
	//LocalGameServer::getInstance()->deal_done(id);
	
	auto scene=Director::getInstance()->getRunningScene();
	if (scene->getChildByTag(23457+id))
	{
		scene->removeChildByTag(23457+id);
	}
	
	auto m_node=Node::create();
	scene->addChild(m_node,10-id,23457+id);
	BaseManager::getInstance()->showRobotPoke(m_node,ai->GetListItem(),id);//新的方法20140831
}
void Robot::donePoke()
{	
	log("done poke");
	//int bigId=LocalGameServer::getInstance()->getWhoBigId();
	//checkPokeType(LocalGameServer::getInstance()->getClientBigData(bigId),bigId);
	//LocalGameServer::getInstance()->deal_done(id);
	
	ai->PokeServer(id);
	
	int size=0;

	size=ai->getPokeData();
	
	LocalGameServer::getInstance()->deal_poke_done(id);
	
	


	auto scene=Director::getInstance()->getRunningScene();
	if (scene->getChildByTag(23457+id))
	{
		scene->removeChildByTag(23457+id);
	}
	
	auto m_node=Node::create();
	scene->addChild(m_node,10-id,23457+id);
	BaseManager::getInstance()->showRobotPoke(m_node,ai->GetListItem(),id);//新的方法20140831
}
//current zhuang jia type big poke id = big
void Robot::checkPokeType(std::vector<PokeData> type,int big)
{
	ai->PokeServer(id);
	
	int size=0;

	size=ai->getPokeData();

	if (size==0)
	{
		size=LocalGameServer::getInstance()->deal_poke_done(id);
	}
	else
		LocalGameServer::getInstance()->deal_done(id);
	
}
int Robot::retKingType(int idx)
{
	return ai->dealDataByIdx(idx);
}
//template<typename T>
unsigned int Robot::sequence(PokeData data)
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

			value+=data.data*10;
			value+=(data.type+1)*1000;
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