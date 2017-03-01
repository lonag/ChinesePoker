#ifndef _GAME_POKE_MANAGER_H_
#define _GAME_POKE_MANAGER_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
USING_NS_CC;
class GamePokeManager
{
public:
	GamePokeManager();
	~GamePokeManager();
	static GamePokeManager* getInstance();
	/**
	@brief 获取牌的id
	*/
	int checkWhoBig(std::map<int,std::vector<PokeData>>pokeList,int type);
	/**
	@brief 判断牌的大小
	@param 一回合里牌的列表
	@param 牌对应的id类型
	@param 主牌类型
	*/
	int compareWhoBig(std::map<int,std::vector<PokeData>>pokeList,std::vector<int>idlist,int type);

	/**
	@brief 副牌一个排的比较
	@param pokebig
	@param type
	*/
	bool compareOnePoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type);
	/**
	@brief 副牌两个排的比较
	@param pokebig
	@param type
	*/
	bool compareTwoPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type);
	bool compareFourPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type);
	bool compareSixPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type);
	bool compareZhuPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type);
	bool checkMainTypePoke(std::map<int,std::vector<PokeData>>pokeList,int type);

	bool isCanDonePoke(std::vector<PokeData> willdata,std::vector<PokeData> youdata);


	int selectBanker(std::vector<int>data,int id);
	std::map<int,std::vector<int>>bankerlist;
	int winID;
};
#endif