#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
USING_NS_CC;
class CommonUtils
{
public:
	static void deleteDataByKey(std::vector<PokeData>&data ,int key,int type);
	static PokeData&  findKey(std::vector<PokeData>&data ,int key);
	static bool CheckKey(std::vector<int>&data,int key);

	static void GetMenu(Node* node,std::string str,std::string pngName,const ccMenuCallback& callback,int tag,int order,Point& p);

	static void ShowPoke(std::vector<PokeData>& data,int id);

	static void ShowUserInfo(Node* node);

	static Point ShowTipsPoint(int id);

	static Point ShowClockPoint(int id);
	//check a
	static PokeData checkA(std::vector<PokeData>&data,int type);
	//check aa k
	static PokeData checkAAK(std::vector<PokeData>&data,int type);

	//check x
	static PokeData checkX(std::vector<PokeData>&data,int id,int type);
	//check main
	static bool checkMain(PokeData& data,int type);
public:
	static bool checkExistNotMainPoke(std::vector<PokeData>& data,int type);
};
#endif