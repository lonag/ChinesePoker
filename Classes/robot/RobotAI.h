#ifndef _robot_ai_h_
#define _robot_ai_h_
#include "cocos2d.h"
#include "../game/GameRule.h"
/**
*���Ե�Ӧ�ù���
*1.��������еĹ������棬Э�����е��ж����������Բ��ԣ�Ҫ���ƽ�����Ͷ�
*2.��;���Ļ��жϹ��򲻴�ô���
*/
//----------------------------�˹������㷨------------------------------------------------------------
/**
*ɱ�����ж�,���ֵĴ����
*ֱ�Ӳ��������жϾ��е���Ҫ�жϴ�С��
*��������ʱ��Ҫ���Ǿ��������֣��ʹ����磨A��K����һ�㿼�ǵ��ž����ˣ���Ҫ���Ƕ��ƣ����֣������������ã�����Ҫ��һ�������ݼ�����
*���Ǽ�������ж��Ĵ���AI�����Ӷ����X
*��һ���Ƶ�����ж��������Ƶ�����ж�����������б�
*͵ɱ���ԣ��������ƽж࣬�����з֣������з�ʱ����ɱ����
*˫�����ԣ����������ж��ӣ��ʹ��������������ƣ�����˫�ۣ��ж���һ���Ժ󣬲��ڳ����ӣ���
*�����˿۵��ƣ��۵��ƾ�����,�۷֣�������
*������ʲôʱ��ʼҪ�����ƣ����� ����û���ӣ��ֶ���
*
*/
//robot
class RobotAI 
{
public:
	//����������ӣ�����ai�ȼ���������ϸ�֣����ݵȼ��ж�Ҫ��Ҫ����
	//�������װ��ÿһ������
	//ai�㷨���ģ��������Լ���ֲ
	RobotAI(std::vector<PokeListItem>_item,int bank);
	~RobotAI();
public:
	std::vector<PokeData> AIDealPoke();
	std::vector<DeleteItem> AIDeletePoke();
	std::vector<DeleteItem> _delList;
	void clear();
	void restart(std::vector<PokeListItem>_item,int bank);
private:
	void reset();
private:
	std::vector<PokeData> aiDealFourPoke();
	std::vector<PokeData> aiDealAAKPoke();
	std::vector<PokeData> aiDealXXPoke();
	std::vector<PokeData> aiDealXPoke();
	std::vector<PokeData> aiDealAPoke();
	std::vector<PokeData> aiDealSixPoke();
	std::vector<PokeData> aiA();//����a
	std::vector<PokeData> aiB();//����b
	//std::vector<PokeData> aiC();//����c
private:
	std::vector<PokeListItem>_listitem;
	int bank;
	int randomInt(int max=4);
};
#endif