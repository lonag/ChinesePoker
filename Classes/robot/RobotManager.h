#ifndef _robot_manager_h_
#define _robot_manager_h_
#include "cocos2d.h"
#include "../robot/Robot.h"
class RobotManager
{
public:
	static RobotManager* getInstance();
	void addListener(std::string str,Robot *bot);
	void dealEvent(std::string str);
	std::map<std::string,Robot*> robotList;
};
#endif