#ifndef _GAME_RULE_H_
#define _GAME_RULE_H_
#include "../common/sortObj.h"
#include "cocos2d.h"
struct PokeData
{
	int type;//1 to 4 5 little and big;
	int data;//1 to 13; 14 little 15 big;
};

struct DeleteItem
{
	std::vector<int> data;
	int size;
	int type;
};
struct PokeListItem
{
	int size;
	int type;
	std::vector<PokeData> _list;
};
struct PokePNG
{
	std::string strpng;
	bool isMain;
};
class GameRule :public sortObj<PokeData>
{
public:
	GameRule();
	~GameRule();
public:
	void randDone();
	bool checkIdExist(int id);
	std::vector<int> idList;
	std::vector<PokeData> pokeList;
	bool initPoke();
	void dealPoke();
	void dealPoleAnimation();
	void restart();
public:
// 	    1
// 	0       2
// 	    3

	
	virtual unsigned int sequence(PokeData t);


	static unsigned int PokeSequence(PokeData data);

	std::vector<PokeData> rolePokeList[5];//4 local player and 8 di pai
	

public:
	std::vector<PokeData> getRolePokeList(int id);
	std::vector<PokeData> getExternPoke(int banker);
	std::vector<PokeData> getExternPoke();

	long GetCurrentTime();
};

#endif
