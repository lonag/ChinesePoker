#include "../common/UserInfo.h"
static UserInfo* instance=NULL;
UserInfo::UserInfo()
{
	banker=3;
	type=-1;
	firstType=-1;
	count=0;
	isExistCount=false;
	isMusic=false;
	isSound=false;
	iBankerMode=0;
    kCnt=0;
}
UserInfo::~UserInfo()
{
	
}
UserInfo* UserInfo::getInstance()
{
	if (instance==NULL)
	{
		instance= new UserInfo();
		return instance;
	}
	return instance;
}
void UserInfo::setRoleWorldId(std::map<int,int> idlist)
{
	this->roleWorldId=idlist;
}
std::map<int,int> UserInfo::getRoleWorldId()
{
	return this->roleWorldId;
}