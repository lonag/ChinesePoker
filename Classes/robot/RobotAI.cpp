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
	srand((unsigned int)CurrTime());//设置随机数因子
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
	//六个牌
	if (aiDealSixPoke().size()>0)
		return aiDealSixPoke();

	//四个牌
	if(aiDealFourPoke().size()>0)
		return aiDealFourPoke();
	//aa k
	if(aiDealAAKPoke().size()>0)
		return aiDealAAKPoke();
	//策略B
	if(aiB().size()>0)
		return aiB();
	//对子
	if(aiDealXXPoke().size()>0)
		return aiDealXXPoke();
	//a
	if(aiDealAPoke().size()>0)
		return aiDealAPoke();
	//策略A
	if(aiA().size()>0)
		return aiA();
	//策略B可能要跟其他类型耦合，再考虑
	//单牌
	if(aiDealXPoke().size()>0)
		return aiDealXPoke();
	std::vector<PokeData> _ret;
	
	return _ret;//size  ==0 
}
/**
@brief 牌类型校正
@param 牌数据
@ret   牌类型
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
			//默认出最大的对子
			int len=(int)(*it)._list.size();
			_retlist.push_back((*it)._list[len-2]);
			_retlist.push_back((*it)._list[len-1]);

			_item.size=2;
			_item.type=pokeType((*it)._list[len-2]);//类型有问题
			_item.data.push_back((*it)._list[len-2].data);
			_item.data.push_back((*it)._list[len-1].data);

			_delList.push_back(_item);
			return _retlist;
		}
	}

	std::vector<PokeData> _ret;
	return _ret;//size  ==0 
}
//其他牌类型,没多大的随机性要考虑
std::vector<PokeData> RobotAI::aiDealXPoke()
{
	std::vector<PokeData>_retlist;
	DeleteItem _item;
	int i_random=randomInt();
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1&&(*it).type==i_random)//只有一次不要重新计算随机值
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
	//出个牌先，解决报错再说
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
		
	//有可能出现加入了没出牌的情况，比如没k


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
			_item.type=pokeType((*it)._list[0]);//校正类型判断
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
			_item.type=pokeType((*it)._list[0]);//校正类型判断
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
*@brief 策略B 当对子大于4对时，或者复牌小于5个时，开始出对子，从正主开始出
*/
std::vector<PokeData> RobotAI::aiB()
{
	std::vector<PokeData>_retlist;
	_delList.clear();
	int iCount=0;//副牌中单牌的个数
	int iKingCnt=0;//正主对子个数
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
	//正主对子个数
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
	int iCount=0;//副牌中单牌的个数
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