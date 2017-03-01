#ifndef _USER_INFO_H_
#define _USER_INFO_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
struct EndPokeData
{
	int big;//哪个大
	std::vector<PokeData> lastdata;//最后大的一方是不是主牌，只有主牌才要考虑最后算积分

};
USING_NS_CC;
class UserInfo
{
public:
	UserInfo();
	~UserInfo();
	static UserInfo* getInstance();
	CC_SYNTHESIZE(std::string,password,Password);
	CC_SYNTHESIZE(int,type,Type);
	CC_SYNTHESIZE(int,banker,Banker);
	CC_SYNTHESIZE(int,firstType,FirstType);//first type

	CC_SYNTHESIZE(std::vector<PokeData>,firstPoke,FirstPoke);//first listpoke
	CC_SYNTHESIZE(std::vector<PokeData>,eightPoke,EightPoke);//eight listpoke
	CC_SYNTHESIZE(int,count,Count);
	CC_SYNTHESIZE(bool,isExistCount,IsExistCount);//is count
//1 2 
    CC_SYNTHESIZE(int,kCnt,KingCount);
    
	CC_SYNTHESIZE(bool,isMusic,IsMusic);//
	CC_SYNTHESIZE(bool,isSound,IsSound);//
	CC_SYNTHESIZE(EndPokeData,iEndData,IEndData);//最后哪个大
	CC_SYNTHESIZE(bool,iBankerMode,BankerMode);//叫主模式 单排， 对子 ，三2叫主，这几类
	void setRoleWorldId(std::map<int,int> idlist);
	std::map<int,int>roleWorldId;
	std::map<int,int> getRoleWorldId();
	

};
#endif