#include "../game/GamePokeManager.h"
#include "../common/UserInfo.h"
#include "../game/RobotRule.h"
#include "../game/PokeRule.h"
static GamePokeManager* instance=NULL;
GamePokeManager::GamePokeManager()
{
	winID=-1;
}
GamePokeManager::~GamePokeManager()
{

}
GamePokeManager* GamePokeManager::getInstance()
{
	if (instance==NULL)
	{
		instance=new GamePokeManager();
		return instance;
	}
	return instance;
}
int GamePokeManager::compareWhoBig(std::map<int,std::vector<PokeData>>pokeList,std::vector<int>idlist,int type)
{
	std::map<int,std::vector<PokeData>>::iterator it=pokeList.begin();
	if (pokeList.size()<=1)
	{
		winID=it->first;
		return winID;
	}
	std::vector<PokeData> bigdata=pokeList.find(winID)->second;
	std::vector<PokeData> data=pokeList.find(idlist[idlist.size()-1])->second;
	//log("win = %d",winID);
	//����
	if (checkMainTypePoke(pokeList,type))
	{
		//�����ƵıȽϴ�С
		//���Ʋ������ƣ����³����ƱȽϣ�ֻҪ�������;ʹ�
		if (bigdata[0].type!=type&&!PokeRule::filterMainPoke(bigdata[0]))
		{
			switch (data.size())
			{
			case 1:
				{
					if (data[0].type==type||PokeRule::filterMainPoke(data[0]))
					{
						winID=idlist[idlist.size()-1];
					}
				}
				break;
			case 2:
				{
					/**
					*���ж��ǲ����������ǵĻ���ֻҪ�ж��ǲ���һ�����
					*����Ҫ�ж��ǲ���ͬ���ͺʹ�Сһ�����ǵĻ�����
					*/
					if(PokeRule::filterMainPoke(data[0])&&PokeRule::filterMainPoke(data[1]))
					{
						if (data[0].data==data[1].data&&data[0].type==data[1].type)
						{
							winID=idlist[idlist.size()-1];
						}
					}
					else if (data[0].type==type&&data[1].type==type)
					{
						if (data[0].data==data[1].data)
						{
							winID=idlist[idlist.size()-1];
						}
					}
				}
				break;
			case 4:
				{

				}
				break;
			default:
				break;
			}
		}
		
		else if(bigdata[0].type==type||PokeRule::filterMainPoke(bigdata[0]))
		{
			bool isdatatype=false;
			for (int i=0;i<data.size();i++)
			{
				if (data[i].type==type||PokeRule::filterMainPoke(data[i]))
				{
					isdatatype=true;
				}
			}
			//�¼ӵ���Ҳ������
			//Ҫ�Ƚϵ��ƶ������ƣ�������
			if (isdatatype)
			{
				switch (data.size())
				{
				case 1:
					{
						if (PokeRule::CalculatePoint(data[0],type,bigdata[0].type)>PokeRule::CalculatePoint(bigdata[0],type,bigdata[0].type))
						{
							winID=idlist[idlist.size()-1];
						}
					}
					break;
				case 2:
					{
						//������ҲҪһ�����Ƕ��ӣ�ok?
						if (data[0].data==data[1].data&&data[0].type==data[1].type)
						{
							if (PokeRule::CalculatePoint(data[0],type,bigdata[0].type)>PokeRule::CalculatePoint(bigdata[0],type,bigdata[0].type))
							{
								winID=idlist[idlist.size()-1];
							}
						}
					}
					break;
				case 4:
					{

					}
					break;
				default:
					break;
				}
			}
		}
		
	}
	else//���ƵıȽ�
	{
		switch (data.size())
		{
		case 1:
			{
				if (compareOnePoke(data,bigdata,type))
				{
					winID=idlist[idlist.size()-1];
				}
			}
			break;
		case 2:
			{
				if (compareTwoPoke(data,bigdata,type))
				{
					winID=idlist[idlist.size()-1];
				}
			}
			break;
		case 4:
			{
				if (compareFourPoke(data,bigdata,type))
				{
					winID=idlist[idlist.size()-1];
				}
			}
		case 6:
			{
				//����û����Ĭ���������Ǵ�ģ����ܼ����д���Ŀ��ܣ����������ݶ���������
				if (compareSixPoke(data,bigdata,type))
					winID=idlist[idlist.size()-1];

			}
		}

	}
	//log("win id = %d   end id = %d",winID,idlist[idlist.size()-1]);
	return winID;

}
bool GamePokeManager::checkMainTypePoke(std::map<int,std::vector<PokeData>>pokeList,int type)
{
	for(std::map<int,std::vector<PokeData>>::iterator it=pokeList.begin();it!=pokeList.end();++it)
	{
		std::vector<PokeData> m_pokelist=it->second;
		for (int i = 0; i < m_pokelist.size(); i++)
		{
			if(m_pokelist[i].data==1)     {return true;}
			if(m_pokelist[i].data==9)     {return true;}
			if(m_pokelist[i].data==14)    {return true;}
			if (m_pokelist[i].data==15)   {return true;}
			if(m_pokelist[i].type==type)  {return true;}
		}
	}
	
	return false;
}
int GamePokeManager::checkWhoBig(std::map<int,std::vector<PokeData>>pokeList,int type)
{
	//deal poke robot and role;
	std::map<int,std::vector<PokeData>>::iterator itbengin=pokeList.begin();

	std::vector<PokeData> data=itbengin->second;
	int id=itbengin->first;
	++itbengin;
	for(std::map<int,std::vector<PokeData>>::iterator it=itbengin;it!=pokeList.end();++it)
	{
		//zhu error
		if(compareZhuPoke(data,it->second,type))
		{
			 data=it->second;
			 id=it->first;
			 log("zhu com = %d",id);

		}
		else
		{
			switch (data.size())
			{
			case 1:
				{
					if (compareOnePoke(data,it->second,type))
					{
						data=it->second;
						id=it->first;
					}
				}
				break;
			case 2:
				{
					if (compareTwoPoke(data,it->second,type))
					{
						data=it->second;
						id=it->first;
					}
				}
				break;
			}
// 			if(data[0].data<it->second[0].data)
// 		    {
// 
// 			     data=it->second;
// 			     id=it->first;
// 		     }
		}
		
	}
	return id;
	
	
}
bool GamePokeManager::compareZhuPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type)
{
	//filter zheng zhu
	return false;
	if (pokeBig[0].type==poke[0].type&&pokeBig[0].type==type)
	{
		if (pokeBig[0].data<poke[0].data)
		{
			return true;
		}
	}
}

bool GamePokeManager::compareOnePoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type)
{
	//log("one poke data = %d big = %d",poke[0].data,pokeBig[0].data);
	if(poke[0].data>pokeBig[0].data&&poke[0].type==pokeBig[0].type)
	{
		return true;
	}
	return false;
}
bool GamePokeManager::compareTwoPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type)
{
// 	log("two 1 poke data = %d big = %d",poke[0].data,pokeBig[0].data);
// 	log("two 2 poke data = %d big = %d",poke[1].data,pokeBig[1].data);
	if (poke[0].data==poke[1].data&&poke[0].type==poke[1].type&&poke[0].type==pokeBig[0].type)
	{
		if (pokeBig[0].data==pokeBig[1].data&&pokeBig[0].type==pokeBig[1].type)
		{
			if (poke[0].data>pokeBig[0].data)
			{
				return true;
			}
		}
	}
	else
	{
		//main poke
	}
	return false;
}
bool GamePokeManager::compareFourPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type)
{
	return false;
}
bool GamePokeManager::compareSixPoke(std::vector<PokeData> poke,std::vector<PokeData> pokeBig,int type)
{
	return false;
}
int GamePokeManager::selectBanker(std::vector<int>data,int id)
{
	if (bankerlist.empty())
	{
		return id;
		bankerlist.insert(std::pair<int,std::vector<int>>(id,data));
	}
	else
	{
		
	}

	return 1;
}
bool GamePokeManager::isCanDonePoke(std::vector<PokeData> willdata,std::vector<PokeData> youdata)
{
	std::vector<PokeData>firstlist=UserInfo::getInstance()->getFirstPoke();


	if (firstlist.size()==0)
	{
		switch (willdata.size())
		{
		case 1:
			{
				return true;
			}
			break;
		case 2:
			{
				if (willdata[0].data==willdata[1].data&&willdata[0].type==willdata[1].type)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;
		case 4:
			{
				//return true;
				//2222
				bool isTWO=true;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].data!=1||PokeRule::checkXX(willdata,willdata[i].type,true).size()!=1)
					{
						isTWO=false;
					}
				}
				if (isTWO)
				{
					return true;
				}
				//aa22 
				if (PokeRule::isExistXX(willdata,13,UserInfo::getInstance()->getType()))
				{
					for (int i = 0; i < 4; i++)
					{
						if (i!=UserInfo::getInstance()->getType())
						{
							if (PokeRule::isExistXX(willdata,1,i))
							{
								return true;
							}
							
						}
					}
				}
				
				//joker ...
				//1010 1010 zhneg fu
				bool isTen=true;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].data!=9||PokeRule::checkXX(willdata,willdata[i].type,true).size()!=1)
					{
						isTen=false;
					}
				}
				if (isTen)
				{
					return true;
				}
				//
				bool isAllType=true;
				int type=willdata[0].type;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].type!=type)
					{
						isAllType=false;
					}
				}
				if (isAllType)
				{
					if (PokeRule::checkXX(willdata,willdata[0].type).size()==2)
					{
						std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(willdata,willdata[0].type);
						
						std::vector<int> idlist;
						for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
						{
							idlist.push_back(it->first);
						}
						if (idlist[0]==idlist[1]-1)
						{
							return true;
						}
						if (idlist[0]==8&&idlist[1]==10)
						{
							return true;
						}

// 						if (it->first+1==(++it)->first)
// 						{
// 							return true;
// 						}
					}
					else
					{
						return false;
					}
				}
				return false;

			}
			break;
		case 6:
			{
				//return true;
				//22 22 22
				bool isTWO=true;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].data!=1||PokeRule::checkXX(willdata,willdata[i].type,true).size()!=1)
					{
						isTWO=false;
					}
				}
				if (isTWO)
				{
					return true;
				}
				//aa 22 
				if (PokeRule::isExistXX(willdata,13,UserInfo::getInstance()->getType()))
				{
					for (int i = 0; i < 4; i++)
					{
						if (i!=UserInfo::getInstance()->getType())
						{
							if (PokeRule::isExistXX(willdata,1,i))
							{
								return true;
							}
							
						}
					}
				}
				
				//joker ...
				//1010 1010 zhneg fu
				bool isTen=true;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].data!=9||PokeRule::checkXX(willdata,willdata[i].type,true).size()!=1)
					{
						isTen=false;
					}
				}
				if (isTen)
				{
					return true;
				}
				//
				bool isAllType=true;
				int type=willdata[0].type;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].type!=type)
					{
						isAllType=false;
					}
				}
				if (isAllType)
				{
					if (PokeRule::checkXX(willdata,willdata[0].type).size()==3)
					{
						std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(willdata,willdata[0].type);
						
						std::vector<int> idlist;
						for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
						{
							idlist.push_back(it->first);
						}
						//44 55 66
						if (idlist[0]==idlist[1]-1==idlist[2]-2)
						{
							return true;
						}
						//88 10 11
						if (idlist[0]==8&&idlist[1]==10&&idlist[2]==11)
						{
							return true;
						}

// 						if (it->first+1==(++it)->first)
// 						{
// 							return true;
// 						}
					}
					else
					{
						return false;
					}
				}
				return false;
			}
			break;
		default:
			return false;
			break;
		}
	}
	//size ==0�����
	//size >0
	if (!PokeRule::filterMainPoke(firstlist[0])&&firstlist[0].type!=UserInfo::getInstance()->getType())
	{
		//�����Ƹ���ҳ����Ƹ�����һ��ʱ��ֱ��false
		if(firstlist.size()!=willdata.size())
		{
			return false;
		}
		int firsttype=firstlist[0].type;
		switch (firstlist.size())
		{
		case 1:
			{
				if (willdata[0].type==firsttype&&!PokeRule::filterMainPoke(willdata[0]))
				{
					return true;
				}
				else
				{
					std::vector<PokeData>typedata=RobotRule::TypePoke(youdata,firsttype);
					if (typedata.size()>0)
					{
						return false;
					}
					return true;
				}
			}
			break;
		case 2:
			{
				std::vector<PokeData>typedata=RobotRule::TypePoke(youdata,firsttype);
				if (typedata.size()>=2)
				{
					if (PokeRule::checkXX(youdata,willdata[0].type).size()>=1)
					{
						std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(youdata,willdata[0].type);
						if (xxlist.find(willdata[0].data)!=xxlist.end()&&xxlist.find(willdata[1].data)!=xxlist.end())
						{
							return true;
						}
						return false;

					}
				}
				if (typedata.size()==0)
				{
					return true;
				}

				//else 
				int count=0;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].type==firsttype&&!PokeRule::filterMainPoke(willdata[i]))
					{
						count++;
					}
				}
				if (count==firstlist.size())
				{
					return true;
				}
				else
				{
					std::vector<PokeData>typedata=RobotRule::TypePoke(youdata,firsttype);
					if (typedata.size()==count)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			break;
		case 4:
			{
				//return true;
				int count=0;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].type==firsttype&&!PokeRule::filterMainPoke(willdata[i]))
					{
						count++;
					}
				}
				if (count==firstlist.size())
				{
					return true;
				}
				else
				{
					std::vector<PokeData>typedata=RobotRule::TypePoke(youdata,firsttype);
					if (typedata.size()==count)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			break;
		case 6:
			{
				//return true;
				int count=0;
				for (int i = 0; i < willdata.size(); i++)
				{
					if (willdata[i].type==firsttype&&!PokeRule::filterMainPoke(willdata[i]))
					{
						count++;
					}
				}
				if (count==firstlist.size())
				{
					return true;
				}
				else
				{
					std::vector<PokeData>typedata=RobotRule::TypePoke(youdata,firsttype);
					if (typedata.size()==count)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			break;
		default:
			return false;
			break;
		}
		return false;
	}
	else
	{
		//�����ж��ӣ�Ҫ�����ӣ����û�У�������������
		if(willdata.size()==2)
		{
			if(willdata[0].data!=willdata[1].data)//���Ƕ��ӣ����ж����������
			{
					//�������ж���û
				std::vector<PokeData> datalist;
				for(int i=0;i<youdata.size();i++)
				{
					if(PokeRule::filterMainPoke(youdata[i]))
					{
						datalist.push_back(youdata[i]);

					}
				}
				for(int i=0;i<datalist.size()-1;i++)
				{
					if(datalist[i].data==datalist[i+1].data&&datalist[i].type==datalist[i+1].type)
					{
						//break;
						return false;
					}
				}
			}
		
		}
		//zhu 
		int firsttype=UserInfo::getInstance()->getType();
		int count=0;
		for (int i = 0; i < willdata.size(); i++)
		{
			if (willdata[i].type==firsttype||PokeRule::filterMainPoke(willdata[i]))
			{
				count++;
			}
		}
		if (count==firstlist.size())
		{
			return true;
		}
		else
		{
			std::vector<PokeData>typedata=RobotRule::MainAndTypePoke(youdata,firsttype);
			if (typedata.size()==count)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	return true;
}