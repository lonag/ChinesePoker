#include "../game/RobotRule.h"
#include "../game/PokeRule.h"
std::vector<PokeData> RobotRule::NotMainAndTypePoke(std::vector<PokeData>&data,int type)
{
	std::vector<PokeData>rule;
	for (int i=0;i<data.size();i++)
	{
		if (!PokeRule::filterMainPoke(data[i])&&data[i].type!=type)
		{
			rule.push_back(data[i]);
		}
	}
	return rule;
}
std::vector<PokeData> RobotRule::MainAndTypePoke(std::vector<PokeData>&data,int type)
{
	std::vector<PokeData>rule;
	for (int i=0;i<data.size();i++)
	{
		if (PokeRule::filterMainPoke(data[i])||data[i].type==type)
		{
			rule.push_back(data[i]);
		}
	}
	return rule;
}
std::vector<PokeData> RobotRule::NotMainPoke(std::vector<PokeData>&data,int type)
{
	std::vector<PokeData>rule;
	for (int i=0;i<data.size();i++)
	{
		if (!PokeRule::filterMainPoke(data[i]))
		{
			rule.push_back(data[i]);
		}
	}
	return rule;
}
//
std::vector<PokeData> RobotRule::NotTypePoke(std::vector<PokeData>&data,int type)
{
	std::vector<PokeData>rule;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type!=type)
		{
			rule.push_back(data[i]);
		}
	}
	return rule;
}
//
std::vector<PokeData> RobotRule::TypePoke(std::vector<PokeData>&data,int sametype)
{
	std::vector<PokeData>rule;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type==sametype&&!PokeRule::filterMainPoke(data[i]))
		{
			rule.push_back(data[i]);
		}
	}
	return rule;
}
bool RobotRule::Deal_count(std::vector<PokeData>&bigdata,int seq/*di ji ge chu pai*/)
{
	if (seq==3)
	{
		return true;
	}
	switch (bigdata.size())
	{
	case 1:
		{
			if (bigdata[0].data==13)
			{
				return true;
			}
			if (bigdata[0].data==14||bigdata[0].data==15)
			{
				return true;
			}
		}
		break;
	case 2:
		{
			if (bigdata[0].data==13&&bigdata[0].data==13)
			{
				return true;
			}
			if ((bigdata[0].data==14&&bigdata[1].data==14)||(bigdata[0].data==15&&bigdata[1].data==15))
			{
				return true;
			}
		}
		break;
	case 4:
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}