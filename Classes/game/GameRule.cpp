#include "../game/GameRule.h"
#include <algorithm>
#include <ctime>
USING_NS_CC;
//方0 黑1 红2 梅3

//配置的牌
PokeData dataEx[4][25]={
	{//1
	{1,8},
	{0,13},
	{3,3},
	{0,3},
	{1,3},
	{1,9},
	{0,6},
	{1,7},
	{1,12},
	{0,2},
	{0,6},
	{2,4},
	{1,1},
	{3,12},
	{1,12},
	{3,7},
	{1,10},
	{0,5},//0 10
	{3,1},
	{2,12},
	{2,4},
	{2,3},
	{2,7},
	{3,5},
	{5,14}
	},
	{//2
	{1,13},
	{1,7},
	{2,6},
	{1,1},
	{0,4},
	{2,13},
	{0,9},
	{3,9},
	{1,11},
	{2,9},
	{2,8},
	{5,15},
	{2,9},
	{3,12},
	{2,10},
	{1,13},
	{1,5},
	{1,5},//0,8
	{0,7},
	{1,9},
	{3,5},
	{3,6},
	{1,4},
	{1,11},
	{1,2}
	},
	{//3
	{5,15},
	{2,5},
	{1,6},
	{3,2},
	{2,5},
	{0,1},
	{3,2},
	{2,6},
	{2,13},
	{3,8},
	{3,7},
	{3,10},
	{3,10},
	{0,13},
	{3,4},
	{0,2},
	{2,2},
	{3,4},
	{0,12},
	{2,11},
	{0,4},
	{1,4},
	{2,3},
	{1,8},
	{0,12}
	},
	{//4
	{1,3},
	{0,10},//0,5
	{1,6},
	{3,11},
	{2,10},
	{0,3},
	{2,11},
	{3,6},
	{1,10},
	{5,14},
	{2,12},
	{0,10},
	{2,8},
	{3,1},
	{0,11},
	{3,9},
	{2,1},
	{1,2},
	{3,11},
	{0,9},
	{2,1},
	{0,1},
	{2,2},
	{3,3},
	{0,8}//1,5
	}
};

//>>>>>>>>>>>>>extern
PokeData externData[]={
	{2,7},
	{3,13},
	{0,5},
	{3,8},
	{0,7},
	{0,8},
	{0,11},
	{3,13}
};




GameRule::GameRule()
{

}
GameRule::~GameRule()
{

}
bool GameRule::checkIdExist(int id)
{
	bool exist=false;
	for (int i=0;i<idList.size();i++)
	{
		if (id==idList[i])
		{
			exist=true;
			return exist;
		}
	}
	return exist;
}
long GameRule::GetCurrentTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}
void GameRule::restart()
{
	for(int i=0;i<5;i++)
	{
		rolePokeList[i].clear();
	}
	idList.clear();
	pokeList.clear();
}
void GameRule::randDone()
{
	srand((unsigned int)GetCurrentTime());

	int count = rand()%108+1;
	idList.push_back(count);

	while (idList.size()<108)
	{
		int count = rand()%108+1;
		//CCLog("rand = %d",count);
		if (checkIdExist(count))
		{

		}
		else
		{
			idList.push_back(count);
		}

	}


}
bool GameRule::initPoke()
{
	bool bRet=false;
	do 
	{
		//考虑填一份数据，就不要每次发牌就去for 一次，节省效率
		//类似查表的思路
		for (int type=0;type<4;type++)
		{
			for (int data=1;data<=13;data++)
			{
				PokeData m_data;		
				m_data.type=type;
				m_data.data=data;
				pokeList.push_back(m_data);
			}
		}	
		for (int type=0;type<4;type++)
		{
			for (int data=1;data<=13;data++)
			{
				PokeData m_data;		
				m_data.type=type;
				m_data.data=data;
				pokeList.push_back(m_data);
			}
		}	
		//
		for (int i=0;i<2;i++)
		{
			for (int data=14;data<=15;data++)
			{
				PokeData m_data;
				m_data.type=5;
				m_data.data=data;
				pokeList.push_back(m_data);
			}
		}
		bRet=true;
	} while (0);
	return bRet;
}
void GameRule::dealPoke()
{
	//init poke
	randDone();
	//
	if (initPoke())
	{
		std::vector<PokeData> m_pokeDataList;
		for (int i=0;i<108;i++)
		{
			//printf("%d ",idList[i]);
			//log("idlist = %d",idList[i]);
			PokeData m_data=pokeList[idList[i]-1];

			if (m_data.data>=14)
			{
				int d=1061+13*4+m_data.data-14;
				char str[126]={0};
				sprintf(str,"ddz/card/card_%d@2x.png",d);
				//log("png = %s",str);

			}
			else
			{
				int d=1061+(m_data.data-1)*4+m_data.type;
				char str[126]={0};
				sprintf(str,"ddz/card/card_%d@2x.png",d);
				//log("i = %d png = %s",i,str);
			}


			m_pokeDataList.push_back(m_data);
		}
		pokeList.clear();
		pokeList=m_pokeDataList;
	}
	
}
//second func step
void GameRule::dealPoleAnimation()
{
	/*dealPoke();
	for (int role=0;role<4;role++)
	{
		log(">>>>>>>>>>>>>>>>id = %d",role);
		for (int i=0;i<25;i++)
		{
			
			PokeData data=pokeList[role*25+i];
			rolePokeList[role].push_back(data);
			log("{%d,%d},",data.type,data.data);
		}
	}*/
	//用做的数据代替随机数据，调试方便
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<25;j++)
		{
			PokeData data;
			data.type=dataEx[i][j].type;
			data.data=dataEx[i][j].data;
			rolePokeList[i].push_back(data);
		}
	}
	//
	for (int role=3;role<4;role++)
	{
		std::sort(rolePokeList[role].begin(),rolePokeList[role].end(),/*GameRule::PokeSort()*/GameRule());
	}
}
std::vector<PokeData> GameRule::getExternPoke()
{
	/*for (int i=100;i<108;i++)
	{
		PokeData data=pokeList[i];
		rolePokeList[4].push_back(data);
	}*/
	for(int i=0;i<8;i++)
	{
		PokeData data;
		data.type=externData[i].type;
		data.data=externData[i].data;
		rolePokeList[4].push_back(data);
	}
	return rolePokeList[4];
}
std::vector<PokeData> GameRule::getExternPoke(int banker)
{
	log(">>>>>>>>>>>>>extern");
	/*for (int i=100;i<108;i++)
	{
		PokeData data=pokeList[i];
		rolePokeList[banker].push_back(data);
		log("{%d,%d},",data.type,data.data);
	}*/

	//
	for(int i=0;i<8;i++)
	{
		PokeData data;
		data.type=externData[i].type;
		data.data=externData[i].data;
		rolePokeList[banker].push_back(data);
	}
	//std::sort(rolePokeList[banker].begin(),rolePokeList[banker].end(),/*GameRule::PokeSort()*/GameRule());
	pokeList.clear();
	return rolePokeList[banker];

}
//template<typename T>
unsigned int GameRule::sequence(PokeData data)
{
	int value=0;

	//type 6- 9 data 1
	if (data.data==1)
	{
		value+=data.data+4;
		value+=data.type+2;
	}
	else if(data.data<=13&&data.data>1)
	{
		//2-5
		if (data.data==9)
		{
			value+=data.data-8;
			value+=data.type+1;
		}
		else
		{

			value+=data.data*10;
			value+=(data.type+1)*1000;
		}

	}
	//joker type 0 1 data 15 14
	else if (data.data==14)
	{
		value+=data.data-14;
		value+=data.type-4;
	}
	//0
	else if (data.data==15)
	{
		value+=data.data-15;
		value+=data.type-5;
	}
	//value+=data.type*1000;
	//value+=data.color;
	return value;
}
unsigned int GameRule::PokeSequence(PokeData data)
{
	int value=0;
	
	//type 6- 9 data 1
	if (data.data==1)
	{
		value+=data.data+4;
		value+=data.type+2;
	}
	else if(data.data<=13&&data.data>1)
	{
		//2-5
		if (data.data==9)
		{
			value+=data.data-8;
			value+=data.type+1;
		}
		else
		{
			value+=data.data*10;
			value+=data.type*1000;
		}
		
	}
	//joker type 0 1 data 15 14
	else if (data.data==14)
	{
		value+=data.data-14;
		value+=data.type-4;
	}
	//0
	else if (data.data==15)
	{
		value+=data.data-15;
		value+=data.type-5;
	}
	//value+=data.type*1000;
	//value+=data.color;
	return value;
}
//0 -3
std::vector<PokeData> GameRule::getRolePokeList(int id)
{
	return this->rolePokeList[id];
}