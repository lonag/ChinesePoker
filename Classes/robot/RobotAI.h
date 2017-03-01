#ifndef _robot_ai_h_
#define _robot_ai_h_
#include "cocos2d.h"
#include "../game/GameRule.h"
/**
*策略的应用规则：
*1.穿插入既有的规则里面，协调已有的判断条件，所以策略，要发牌结束后就定
*2.中途定的话判断规则不大好处理
*/
//----------------------------人工智能算法------------------------------------------------------------
/**
*杀主的判断,消分的处理Ｖ
*直接插入现有判断就行但是要判断大小Ｖ
*对子消牌时，要考虑尽量不消分，和大牌如（A或K），一般考虑单排就行了，不要考虑对牌，这种，可以留着有用，这种要多一步的数据检索Ｘ
*考虑加入随机判定的处理AI，增加多变性X
*第一手牌的随机判定，和消牌的随机判定，利用随机列表
*偷杀策略（当手里牌叫多，主牌有分，或副牌有分时果断杀主）
*双超策略（手里主牌有对子，和大王，就留着手牌，进行双扣，判定这一策略后，不在出对子）攻
*机器人扣底牌，扣单牌就行了,扣分，留大牌
*机器人什么时候开始要出主牌，个数 副牌没对子，分多了
*
*/
//robot
class RobotAI 
{
public:
	//处理随机因子，处理ai等级，将问题细分，根据等级判断要不要处理
	//将问题封装成每一个函数
	//ai算法核心，方便语言间移植
	RobotAI(std::vector<PokeListItem>_item,int bank);
	~RobotAI();
public:
	std::vector<PokeData> AIDealPoke();
	std::vector<DeleteItem> AIDeletePoke();
	std::vector<DeleteItem> _delList;
	void clear();
	void restart(std::vector<PokeListItem>_item,int bank);
private:
	void reset();
private:
	std::vector<PokeData> aiDealFourPoke();
	std::vector<PokeData> aiDealAAKPoke();
	std::vector<PokeData> aiDealXXPoke();
	std::vector<PokeData> aiDealXPoke();
	std::vector<PokeData> aiDealAPoke();
	std::vector<PokeData> aiDealSixPoke();
	std::vector<PokeData> aiA();//策略a
	std::vector<PokeData> aiB();//策略b
	//std::vector<PokeData> aiC();//策略c
private:
	std::vector<PokeListItem>_listitem;
	int bank;
	int randomInt(int max=4);
};
#endif