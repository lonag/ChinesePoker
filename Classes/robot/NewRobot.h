#ifndef _new_robot_h_
#define _new_robot_h_
#include "cocos2d.h"
#include "../game/GameRule.h"
#include "../common/sortObj.h"
#include "../robot/RobotAI.h"

//设计bug,当对子拆分之后没做处理，还来在对子列表里面，应该移到单牌列表里面才可以，加个刷新函数


class NewRobot  : public sortRef<PokeData>
{
public:

	//length list poke
	//相同大小的牌的集合
	//牌分类
	/**
	@brief 出牌处理
	@param 列表
	*/
	void pokeFilerPool(std::vector<PokeData> &datalist);
	/**
	@brief 底牌处理
	@param 列表
	*/
	void pokeExtraPkFilter(std::vector<PokeData> &datalist);
	/**
	@brief 出牌处理
	@param robot id
	*/
	bool PokeServer(int id);

	int getPokeData();
private:
	//判断正主
	inline bool pokeKingPoke(PokeData& data);
	//判断牌类型
	inline int pokeType(PokeData& _data);
	//判读主牌
    bool pokeMainPoke(PokeData& data){return false;}
	//对子
	void pokeFilerDoublePoke(std::vector<PokeData>& datalist,int tag);
	//四个牌
	void pokeFilterDoubleDoublePoke(std::vector<PokeData>& datalist,int tag);
	//六个牌
	void pokeFilterSixPoke(std::vector<PokeData>& datalist,int tag);

	//six king poke
	void pokeFilterSixKingPoke(std::vector<PokeData> &datalist,int tag);
	//
	void pokeFilterKingPoke(std::vector<PokeData>& datalist,int tag);
	

	void PushItem(std::vector<PokeData>& dalalist,int size,int type);
	/**
	@brief 对子拆分后刷新列表
	@param 列表，大小，类型,牌
	*/

	void FreshFilterPoke(std::vector<PokeData>&datalist,int size,int type,int data,int count);


private:
	size_t size;
	int type;
	int bank;
	int firsttype;
	int id;
	int bigPokeId;
	std::vector<PokeData> _firstpoke;
	std::vector<PokeData> _xxlist;
	std::vector<PokeData >_retlist;
	std::vector<DeleteItem>_dellist;
	std::vector<PokeData> _biglist;
	/**
	@brief 消分
	@param 牌的类型
	@param 牌类型
	*/
	bool filterPkCount(int fsize=-1,int ftype=-1,int flen=0,int* tag=NULL);//0 表示不确定
	/**
	@brief 消小牌
	@param 牌的类型
	@param 牌类型
	*/
	bool filterPkLarge(int size,int type,int len,std::vector<PokeData> _list);//0 表示不考虑
	/**
	@brief 清空xxlist
	*/
	inline void clearxxlist();
	/**
	@brief 拆分单牌
	@param 出牌长度
	@param 牌类型
	*/
	bool splitSingle(int len,int type);//delete 问题很多，当四个牌时，要组合几种类型才可以出牌
	bool splitDouble(int len,int type);
	/**
	@brief 拆分单牌
	@param 出牌长度 默认为四个
	@param 牌类型
	*/
	bool splitDoubleDoule(int type,int len=4);

	/**
	@brief 拆分单牌
	@param 出牌长度 默认为六个
	@param 牌类型
	*/
	bool splitSix(int type,int len=6);
	/**
	@brief 主牌消牌的处理
	@param id robot id
	*/
	bool checkKingMainPoke(int id);
	/**
	@brief 主牌要的处理
	@param id robot id
	*/
	bool checkKingBigPoke(int id);

	/**
	@brief 处理并处理大起的牌
	@param id robot id
	*/
	bool checkPokeDone(int id);
	/**
	@brief 处理当前牌没情况
	@param id robot id
	*/

	//策略
	/**
	@brief 处理策略牌玩法
	@param id robot id
	*/
	bool checkAiA(int id);
	/**
	@brief 处理策略牌玩法
	@param id robot id
	*/
	bool checkAiB(int id);

	bool checkOtherSinglePoke(int id);
	bool checkDoublePoke(int id);
	bool checkDoubleDoublePoke(int id);

	bool checkSixPoke(int id);
	bool dealPoke(std::vector<PokeData> _poke);
	void deletePoke(std::vector<int> _poke,int _size,int _type);//大 头没 删 >>DeleteItem
	void deletePoke(std::vector<DeleteItem>_item);
	
public:
	void RobotAIDealPoke();
	RobotAI* ai;
private:
	void splitRobotData(const int type,PokeData& data);
	bool checkCompare(PokeData& a,PokeData& b);
public:
	//按大小排序
	virtual unsigned int sequence(PokeData  data);
private:
	//size list
	//size type list
	// 0 1 2 3 4 (正主)

	std::map<int,std::vector<PokeData>>_list[5];
	std::vector<PokeListItem> _listitem;

	int randomInt(int max=4);
	bool checkHave(int n);
	std::vector<int> randlist;
public:
	std::vector<PokeListItem> GetListItem();
public:
	//------------------------robot策略分析与处理--------------------------------
	//记录其它玩家的已出牌数据，提取关键数据进行分析，来应对，做出不一样的判断
	//比如我要出kk时可以判断，其他玩家有没有AA,或这个type的牌有没，就可以放心出
	//比如我想出k时判断其他玩家的牌，主要是庄家的牌，看有没，有就可以出，没有的话
	//就只能呵呵了
	//消分的话看可以消分，不可以的话就不要乱出牌
	struct typeCount
	{
		int count;
		int type;
	};
	struct dataCount
	{
		int data;
		int count;
		int type;
		int size;
	};
	void registerTypeCount(int count,int type);
	void registerDataCount(int data,int count,int type,int size);
	//特征数据分析引擎
	bool analysis();
public:
	struct donePoke
	{
		int data;
		int cnt;
	};
	//叫主相关
	void getListData(std::vector<PokeData>& datalist);
	int dealDataByIdx(int idx);
	std::vector<PokeData> dealBankerPoke();
	//根据当前牌型算个数和百分比
	//达到要求是就叫主 >5 个总数的 20% -- %30%左右
private:
	std::vector<PokeData> pokeList;
	int typeCntList[4];//type,cnt
	std::vector<donePoke> bankedDataList;//已有的主牌类型，但是牌型没达到要求的，等待满足条件来叫主
};
#endif//