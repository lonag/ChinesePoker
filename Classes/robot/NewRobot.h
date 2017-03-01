#ifndef _new_robot_h_
#define _new_robot_h_
#include "cocos2d.h"
#include "../game/GameRule.h"
#include "../common/sortObj.h"
#include "../robot/RobotAI.h"

//���bug,�����Ӳ��֮��û�����������ڶ����б����棬Ӧ���Ƶ������б�����ſ��ԣ��Ӹ�ˢ�º���


class NewRobot  : public sortRef<PokeData>
{
public:

	//length list poke
	//��ͬ��С���Ƶļ���
	//�Ʒ���
	/**
	@brief ���ƴ���
	@param �б�
	*/
	void pokeFilerPool(std::vector<PokeData> &datalist);
	/**
	@brief ���ƴ���
	@param �б�
	*/
	void pokeExtraPkFilter(std::vector<PokeData> &datalist);
	/**
	@brief ���ƴ���
	@param robot id
	*/
	bool PokeServer(int id);

	int getPokeData();
private:
	//�ж�����
	inline bool pokeKingPoke(PokeData& data);
	//�ж�������
	inline int pokeType(PokeData& _data);
	//�ж�����
    bool pokeMainPoke(PokeData& data){return false;}
	//����
	void pokeFilerDoublePoke(std::vector<PokeData>& datalist,int tag);
	//�ĸ���
	void pokeFilterDoubleDoublePoke(std::vector<PokeData>& datalist,int tag);
	//������
	void pokeFilterSixPoke(std::vector<PokeData>& datalist,int tag);

	//six king poke
	void pokeFilterSixKingPoke(std::vector<PokeData> &datalist,int tag);
	//
	void pokeFilterKingPoke(std::vector<PokeData>& datalist,int tag);
	

	void PushItem(std::vector<PokeData>& dalalist,int size,int type);
	/**
	@brief ���Ӳ�ֺ�ˢ���б�
	@param �б���С������,��
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
	@brief ����
	@param �Ƶ�����
	@param ������
	*/
	bool filterPkCount(int fsize=-1,int ftype=-1,int flen=0,int* tag=NULL);//0 ��ʾ��ȷ��
	/**
	@brief ��С��
	@param �Ƶ�����
	@param ������
	*/
	bool filterPkLarge(int size,int type,int len,std::vector<PokeData> _list);//0 ��ʾ������
	/**
	@brief ���xxlist
	*/
	inline void clearxxlist();
	/**
	@brief ��ֵ���
	@param ���Ƴ���
	@param ������
	*/
	bool splitSingle(int len,int type);//delete ����ܶ࣬���ĸ���ʱ��Ҫ��ϼ������Ͳſ��Գ���
	bool splitDouble(int len,int type);
	/**
	@brief ��ֵ���
	@param ���Ƴ��� Ĭ��Ϊ�ĸ�
	@param ������
	*/
	bool splitDoubleDoule(int type,int len=4);

	/**
	@brief ��ֵ���
	@param ���Ƴ��� Ĭ��Ϊ����
	@param ������
	*/
	bool splitSix(int type,int len=6);
	/**
	@brief �������ƵĴ���
	@param id robot id
	*/
	bool checkKingMainPoke(int id);
	/**
	@brief ����Ҫ�Ĵ���
	@param id robot id
	*/
	bool checkKingBigPoke(int id);

	/**
	@brief ��������������
	@param id robot id
	*/
	bool checkPokeDone(int id);
	/**
	@brief ����ǰ��û���
	@param id robot id
	*/

	//����
	/**
	@brief ����������淨
	@param id robot id
	*/
	bool checkAiA(int id);
	/**
	@brief ����������淨
	@param id robot id
	*/
	bool checkAiB(int id);

	bool checkOtherSinglePoke(int id);
	bool checkDoublePoke(int id);
	bool checkDoubleDoublePoke(int id);

	bool checkSixPoke(int id);
	bool dealPoke(std::vector<PokeData> _poke);
	void deletePoke(std::vector<int> _poke,int _size,int _type);//�� ͷû ɾ >>DeleteItem
	void deletePoke(std::vector<DeleteItem>_item);
	
public:
	void RobotAIDealPoke();
	RobotAI* ai;
private:
	void splitRobotData(const int type,PokeData& data);
	bool checkCompare(PokeData& a,PokeData& b);
public:
	//����С����
	virtual unsigned int sequence(PokeData  data);
private:
	//size list
	//size type list
	// 0 1 2 3 4 (����)

	std::map<int,std::vector<PokeData>>_list[5];
	std::vector<PokeListItem> _listitem;

	int randomInt(int max=4);
	bool checkHave(int n);
	std::vector<int> randlist;
public:
	std::vector<PokeListItem> GetListItem();
public:
	//------------------------robot���Է����봦��--------------------------------
	//��¼������ҵ��ѳ������ݣ���ȡ�ؼ����ݽ��з�������Ӧ�ԣ�������һ�����ж�
	//������Ҫ��kkʱ�����жϣ����������û��AA,�����type������û���Ϳ��Է��ĳ�
	//���������kʱ�ж�������ҵ��ƣ���Ҫ��ׯ�ҵ��ƣ�����û���оͿ��Գ���û�еĻ�
	//��ֻ�ܺǺ���
	//���ֵĻ����������֣������ԵĻ��Ͳ�Ҫ�ҳ���
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
	//�������ݷ�������
	bool analysis();
public:
	struct donePoke
	{
		int data;
		int cnt;
	};
	//�������
	void getListData(std::vector<PokeData>& datalist);
	int dealDataByIdx(int idx);
	std::vector<PokeData> dealBankerPoke();
	//���ݵ�ǰ����������Ͱٷֱ�
	//�ﵽҪ���Ǿͽ��� >5 �������� 20% -- %30%����
private:
	std::vector<PokeData> pokeList;
	int typeCntList[4];//type,cnt
	std::vector<donePoke> bankedDataList;//���е��������ͣ���������û�ﵽҪ��ģ��ȴ���������������
};
#endif//