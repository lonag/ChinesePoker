#include "../robot/RobotAI.h"
#include <ctime>
#include "cocos2d.h"
USING_NS_CC;
//0 1 2 3 0 1 2 3 0 1 2 3
//const static int RandData[]={1,0,2,3,2,3,0,1,2,0,1,3};

static long CurrTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}



RobotAI::RobotAI(std::vector<PokeListItem>_item,int bank):_listitem(_item)
{
	this->bank=bank;
	srand((unsigned int)CurrTime());//�������������
	//
}
RobotAI::~RobotAI()
{

}
void RobotAI::restart(std::vector<PokeListItem>_item,int bank)
{
	clear();
	_listitem=_item;
	this->bank=bank;
}
void RobotAI::clear()
{
	if(_listitem.size())
		_listitem.clear();

	if(_delList.size())
		_delList.clear();
}
std::vector<DeleteItem> RobotAI::AIDeletePoke()
{
	return _delList;
}
void RobotAI::reset()
{
	if(_delList.size())
		_delList.clear();
}
std::vector<PokeData> RobotAI::AIDealPoke()
{
	reset();
	log("random = %d",randomInt());
	//������
	if (aiDealSixPoke().size()>0)
		return aiDealSixPoke();

	//�ĸ���
	if(aiDealFourPoke().size()>0)
		return aiDealFourPoke();
	//aa k
	if(aiDealAAKPoke().size()>0)
		return aiDealAAKPoke();
	//����B
	if(aiB().size()>0)
		return aiB();
	//����
	if(aiDealXXPoke().size()>0)
		return aiDealXXPoke();
	//a
	if(aiDealAPoke().size()>0)
		return aiDealAPoke();
	//����A
	if(aiA().size()>0)
		return aiA();
	//����B����Ҫ������������ϣ��ٿ���
	//����
	if(aiDealXPoke().size()>0)
		return aiDealXPoke();
	std::vector<PokeData> _ret;
	
	return _ret;//size  ==0 
}
/**
@brief ������У��
@param ������
@ret   ������
*/
inline static int pokeType(PokeData& _data)
{
	if(_data.data==1){return 4;}
	else if(_data.data==9){return 4;}
	else if(_data.data>=14){return 4;}
	return _data.type;
}
std::vector<PokeData> RobotAI::aiDealXXPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==2&&(*it)._list.size()>=2)
		{
			//Ĭ�ϳ����Ķ���
			int len=(int)(*it)._list.size();
			_retlist.push_back((*it)._list[len-2]);
			_retlist.push_back((*it)._list[len-1]);

			_item.size=2;
			_item.type=pokeType((*it)._list[len-2]);//����������
			_item.data.push_back((*it)._list[len-2].data);
			_item.data.push_back((*it)._list[len-1].data);

			_delList.push_back(_item);
			return _retlist;
		}
	}

	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
//����������,û���������Ҫ����
std::vector<PokeData> RobotAI::aiDealXPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	int i_random=randomInt();
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1&&(*it).type==i_random)//ֻ��һ�β�Ҫ���¼������ֵ
		{
			_retlist.push_back((*it)._list[0]);
			_item.size=1;
			_item.type=pokeType((*it)._list[0]);
			_item.data.push_back((*it)._list[0].data);
			_delList.push_back(_item);
			return _retlist;
		}
		i_random=randomInt();
	}
	//�������ȣ����������˵
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		_retlist.push_back((*it)._list[0]);
		_item.size=(*it).size;
		_item.type=pokeType((*it)._list[0]);
		_item.data.push_back((*it)._list[0].data);
		_delList.push_back(_item);
		return _retlist;
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 

}
std::vector<PokeData> RobotAI::aiDealAPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1)
		{
			for(int k=0;k<(*it)._list.size();k++)
			{
				if((*it)._list[k].data==13)
				{
					_retlist.push_back((*it)._list[k]);
					_item.size=1;
					_item.type=pokeType((*it)._list[0]);
					_item.data.push_back((*it)._list[k].data);
					_delList.push_back(_item);
					return _retlist;
				}
			}
			
		}
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
std::vector<PokeData> RobotAI::aiDealAAKPoke()
{
	std::vector<PokeData>_retlist;
	int type=-1;
	DeleteItem _item;
	
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==2&& (*it).type!=bank)
		{
			for(int i=0;i<(*it)._list.size();i++)
			{
				if((*it)._list[i].data==13)
				{
					type=(*it).type;
					_retlist.push_back((*it)._list[i]);
					_retlist.push_back((*it)._list[i+1]);
					//
					_item.size=2;
					_item.type=type;

					_item.data.push_back((*it)._list[i].data);
					_item.data.push_back((*it)._list[i+1].data);
					_delList.push_back(_item);
					
					break;
				}
			}
			//return _retlist;
		}
		if(type!=-1)
			break;
	}
	if(type!=-1)
	{
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==1&& (*it).type==type)
			{
				for(int i=0;i<(*it)._list.size();i++)
				{
					if((*it)._list[i].data==12)
					{
						_retlist.clear();

						_retlist.push_back((*it)._list[i]);//k


						_item.size=1;
						_item.type=type;

						_item.data.clear();//clear

						_item.data.push_back((*it)._list[i].data);
						_delList.clear();
						_delList.push_back(_item);

						return _retlist;
					}
				}

			}
		}
		return _retlist;
	}
		
	//�п��ܳ��ּ�����û���Ƶ����������ûk


	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
std::vector<PokeData> RobotAI::aiDealSixPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==6)
		{
			_retlist.push_back((*it)._list[0]);
			_retlist.push_back((*it)._list[1]);
			_retlist.push_back((*it)._list[2]);
			_retlist.push_back((*it)._list[3]);
			_retlist.push_back((*it)._list[4]);
			_retlist.push_back((*it)._list[5]);

			_item.size=6;
			_item.type=pokeType((*it)._list[0]);//У�������ж�
			_item.data.push_back((*it)._list[0].data);
			_item.data.push_back((*it)._list[1].data);
			_item.data.push_back((*it)._list[2].data);
			_item.data.push_back((*it)._list[3].data);
			_item.data.push_back((*it)._list[4].data);
			_item.data.push_back((*it)._list[5].data);

			_delList.push_back(_item);
			return _retlist;
		}
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}

std::vector<PokeData> RobotAI::aiDealFourPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==4)
		{
			_retlist.push_back((*it)._list[0]);
			_retlist.push_back((*it)._list[1]);
			_retlist.push_back((*it)._list[2]);
			_retlist.push_back((*it)._list[3]);

			_item.size=4;
			_item.type=pokeType((*it)._list[0]);//У�������ж�
			_item.data.push_back((*it)._list[0].data);
			_item.data.push_back((*it)._list[1].data);
			_item.data.push_back((*it)._list[2].data);
			_item.data.push_back((*it)._list[3].data);

			_delList.push_back(_item);
			return _retlist;
		}
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
/*
*@brief ����B �����Ӵ���4��ʱ�����߸���С��5��ʱ����ʼ�����ӣ���������ʼ��
*/
std::vector<PokeData> RobotAI::aiB()
{
	std::vector<PokeData>_retlist;
	_delList.clear();
	int iCount=0;//�����е��Ƶĸ���
	int iKingCnt=0;//�������Ӹ���
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1)
		{
			if(!((*it).type!=bank&&(*it).type!=4))
			{
				iCount+=(*it)._list.size();
			}
		}
	}
	//�������Ӹ���
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==2&&(*it).type==bank&&(*it).type==4)
		{
			iKingCnt+=(*it)._list.size();
		}
	}

	DeleteItem _item;
	if(iCount<5||iKingCnt>=4)
	{
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==2&&(*it).type==4)
			{
				_retlist.push_back((*it)._list[0]);
				_retlist.push_back((*it)._list[1]);
				_item.size=2;
				_item.type=pokeType((*it)._list[0]);

				_item.data.push_back((*it)._list[0].data);
				_item.data.push_back((*it)._list[1].data);
				_delList.push_back(_item);
				return _retlist;
			}
		}
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
std::vector<PokeData> RobotAI::aiA()
{
	std::vector<PokeData>_retlist;
	_delList.clear();
	int iCount=0;//�����е��Ƶĸ���
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1)
		{
			if(!((*it).type==bank&&(*it).type==4))
			{
				iCount+=(*it)._list.size();
			}
		}
	}
	DeleteItem _item;
	if(iCount<7)
	{
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==1&&((*it).type==bank||(*it).type==4))
			{
				_retlist.push_back((*it)._list[0]);
				_item.size=1;
				_item.type=pokeType((*it)._list[0]);
				_item.data.push_back((*it)._list[0].data);
				_delList.push_back(_item);
				return _retlist;
			}
		}
	}
	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
int RobotAI::randomInt(int max)
{
	return rand()%max+0;
}