#ifndef _poke_rule_h_
#define _poke_rule_h_
#include "../game/GameRule.h"
#include "../common/sortObj.h"
class PokeRule : public sortRef<PokeData>
{
public:
	PokeRule();
	~PokeRule();
public:
	int checkRule(std::vector<PokeData>& data);

	bool checkTwo(std::vector<PokeData>& data);
	bool checkFour(std::vector<PokeData>& data);

	static bool checkType(std::vector<PokeData>& data,int type);
	//same type big data or type small;
	static PokeData checkBigData(std::vector<PokeData>& data,std::vector<PokeData> type);

	//same type xiao fen data;
	static std::vector<PokeData> checkGifts(std::vector<PokeData>& data,int type);

	//robot big poke
	static std::vector<PokeData> dealPokeBigData(std::vector<PokeData>& data,int key);

	//is have banker data; type = banker
	static bool  checkBankerPoke(std::vector<PokeData>& data,int type);

	static PokeData dealBankerPoke(PokeData bigdata,std::vector<PokeData>& data,int type);

	//
	static PokeData dealMainBankerPoke(PokeData bigdata,std::vector<PokeData>& data,int type);
public:
	//two or four or more poke

	//size 0 = error not exist XX poke
	static std::map<int,std::vector<PokeData>> checkXX(std::vector<PokeData>& data,int type,bool ischeckmain=false);
	static std::vector<PokeData> dealXXPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id);
	//deal xiao pai
	static std::vector<PokeData> dealXiaoPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id);
	//deal xiao main poke
	static std::vector<PokeData> dealXiaoMainPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id);

	static std::vector<PokeData> getMinDataPoke(std::vector<PokeData>& data,int size);

	//filter main poke
	static bool filterMainPoke(PokeData data);
	//single one XX same type one poke
	static std::vector<PokeData> getMinXiaoPoke(std::vector<PokeData>& data,int size,int type);
public:
	virtual unsigned int sequence(PokeData  data);
public:
	//four poke
	static std::vector<PokeData> dealMorePoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id);
	//check type xx
	static std::map<int,std::vector<PokeData>> checktypeXX(std::vector<PokeData>& data,int type,bool ischeckmain=false);
	static void releaselist(std::vector<PokeData>& data);


	static bool isExistXX(std::vector<PokeData>& data,int key,int type,bool ischeckmain=false);

	//calc point 
	static int CalculatePoint(PokeData data,int type,int firsttype);
};
#endif