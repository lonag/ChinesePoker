#ifndef _USER_INFO_H_
#define _USER_INFO_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
struct EndPokeData
{
	int big;//�ĸ���
	std::vector<PokeData> lastdata;//�����һ���ǲ������ƣ�ֻ�����Ʋ�Ҫ������������

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
	CC_SYNTHESIZE(EndPokeData,iEndData,IEndData);//����ĸ���
	CC_SYNTHESIZE(bool,iBankerMode,BankerMode);//����ģʽ ���ţ� ���� ����2�������⼸��
	void setRoleWorldId(std::map<int,int> idlist);
	std::map<int,int>roleWorldId;
	std::map<int,int> getRoleWorldId();
	

};
#endif