#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "cocos2d.h"
#include "../game/GameRule.h"
#include "../robot/NewRobot.h"
#include "../common/sortObj.h"
USING_NS_CC;
class Robot : public Ref,public sortObj<PokeData>
{
public:
	Robot(std::vector<PokeData> robotPokeList,int id);
	Robot(){}
	~Robot();
	std::vector<PokeData> robotPokeList;
	int id;
	void timeout(Ref* b);
	void donePoke();
	void banker_time_out(Ref* b);
public:
	void checkPokeType(std::vector<PokeData> type,int big);
public:
	void server_mess(Ref* obj,int key);
	int retKingType(int idx);
private:
	NewRobot *ai;
public:
	virtual unsigned int sequence(PokeData t);
};
#endif