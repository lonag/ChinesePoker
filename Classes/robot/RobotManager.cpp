#include "../robot/RobotManager.h"
static RobotManager* instance=NULL;
RobotManager* RobotManager::getInstance()
{
	if (instance==NULL)
	{
		instance=new RobotManager();
		return instance;
	}
	return instance;
}
void RobotManager::addListener(std::string str,Robot *bot)
{
	robotList[str]=bot;
}
void RobotManager::dealEvent(std::string str)
{
	if (robotList.find(str)!=robotList.end())
	{
		//Robot* bot=robotList.find(str)->second;
		//bot
	}
}