#ifndef _robot_rule_h_
#define _robot_rule_h_
#include "../game/GameRule.h"
class RobotRule
{
public:
	static std::vector<PokeData> NotMainAndTypePoke(std::vector<PokeData>&data,int type);

	static std::vector<PokeData> MainAndTypePoke(std::vector<PokeData>&data,int type);

	static std::vector<PokeData> NotMainPoke(std::vector<PokeData>&data,int type);
	//
	static std::vector<PokeData> NotTypePoke(std::vector<PokeData>&data,int type);
	//
	static std::vector<PokeData> TypePoke(std::vector<PokeData>&data,int sametype);
	//
	//xiao fen
	static bool Deal_count(std::vector<PokeData>&bigdata,int seq/*di ji ge chu pai*/);
};
#endif