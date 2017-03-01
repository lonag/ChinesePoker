#include "../game/PokeRule.h"
#include "../common/UserInfo.h"
#include "../game/RobotRule.h"
#include "../game/LocalGameServer.h"
#include "../common/CommonUtils.h"
PokeRule::PokeRule()
{

}
PokeRule::~PokeRule()
{

}
//std::sort
int PokeRule::checkRule(std::vector<PokeData>& data)
{
	switch (data.size())
	{
	case 1:
		return 1;
		break;
	case 2:
		{
			if (checkTwo(data))
			{
				return 2;
			}
			else
			{
				return 0;
			}
			
			
		}
		break;
	case 4:
		return 4;
		break;
	case 8:
		return 8;
		break;
	default:
		return 0;//not deal;
		break;
	}
}
bool PokeRule::checkTwo(std::vector<PokeData>& data)
{
	bool bRet=false;
	//PokeData one=data[0];
	//PokeData two=data[1];
	/*if (one.color==two.color&&one.data==two.data&&one.type==one.type)
	{
		bRet=true;
	}*/
	return bRet;
}
bool PokeRule::checkFour(std::vector<PokeData>& data)
{
	bool bRet=false;
	//4455 5566 
	//1414 1515
	std::vector<int> statelist;
	for (int i=0;i<statelist.size();i++)
	{
		statelist.push_back(0);
	}
	PokeData m_data=data[0];
	for (int i=1;i<4;i++)
	{
		
		if (m_data.data==data[i].data)
		{
			statelist[0]=1;
		}
		/*if (m_data.color==data[i].color)
		{
			statelist[1]=2;
		}*/
		if (m_data.data==data[i].data+1)
		{
			statelist[2]=3;
		}
		if (m_data.data-1==data[i].data)
		{
			statelist[3]=4;
		}
	}
	if (!(statelist[0]==statelist[1]==statelist[2]==statelist[3]))
	{

		if (statelist[0]==1&&statelist[1]==2&&(statelist[2]==3||statelist[3]==4))
		{
			bRet=true;
		}
	}
	
	return bRet;
}
bool PokeRule::checkType(std::vector<PokeData>& data,int type)
{
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type==type)
		{
			if (!filterMainPoke(data[i]))
			{
				return true;
			}
			
		}
	}
	return false;
}
PokeData PokeRule::checkBigData(std::vector<PokeData>& data,std::vector<PokeData> type)
{

	std::vector<PokeData>typePokeList;
	bool ismain=false;
	//main poke
	if (type[0].data==9||type[0].data==1||type[0].data>=14)
	{
		ismain=true;

	}
	std::vector<PokeData>sameTypeData;
	int firsttype=UserInfo::getInstance()->getFirstType();
	if (firsttype==UserInfo::getInstance()->getType())
	{
		ismain=true;
	}
	if (ismain)
	{
		for (int i=0;i<data.size();i++)
		{
			if (filterMainPoke(data[i]))
			{
				sameTypeData.push_back(data[i]);
			}
		}
		int key=UserInfo::getInstance()->getType();
		if (sameTypeData.size()>0)
		{
			PokeData bigData=type[0];
			bool isBig=false;
			for (int i=0;i<sameTypeData.size();i++)
			{

				if (CalculatePoint(bigData,bigData.type,firsttype)<CalculatePoint(sameTypeData[i],sameTypeData[i].type,firsttype))
				{
					bigData=sameTypeData[i];
					isBig=true;
				}
			}
			if (!isBig)
			{
				//zhu zui xiao de
				std::vector<PokeData>zhuPoke;
				for (int i=0;i<data.size();i++)
				{
					if (key==data[i].type)
					{
						zhuPoke.push_back(data[i]);
					}
				}
				if (zhuPoke.size()>0)
				{
					return getMinDataPoke(zhuPoke,1)[0];
				}

				//zheng zhu zui xiao de
				PokeData smallData=sameTypeData[0];
				for (int i=0;i<sameTypeData.size();i++)
				{
					if (CalculatePoint(smallData,smallData.type,firsttype)>CalculatePoint(sameTypeData[i],sameTypeData[i].type,firsttype))
					{
						smallData=sameTypeData[i];
					}
				}
				return smallData;
			}
			else
			{
				return bigData;
			}
		}

	}
////////////////////////////////////////////////////////////////////////////////////////////////////
	//fu pai chu li suan fa	
	for (int i=0;i<data.size();i++)
	{
		if (firsttype==data[i].type)
		{
			if (!filterMainPoke(data[i]))
			{
				sameTypeData.push_back(data[i]);
			}
			
		}
	}
	if (!sameTypeData.empty())
	{
		PokeData bigData=type[0];
		bool isBig=false;
		for (int i=0;i<sameTypeData.size();i++)
		{
			
			if (bigData.data<sameTypeData[i].data)
			{
				bigData=sameTypeData[i];
				isBig=true;
			}
		}
		if (!isBig)
		{
			PokeData smallData=sameTypeData[0];
			for (int i=0;i<sameTypeData.size();i++)
			{
				if (smallData.data>sameTypeData[i].data)
				{
					smallData=sameTypeData[i];
				}
			}
			return smallData;
		}
		else
		{
			return bigData;
		}
	}
	else
	{
		for (int i=0;i<data.size();i++)
		{
			if (!filterMainPoke(data[i]))
			{
				return data[i];
			}
		}
	}
	return data[0];
}
std::vector<PokeData> PokeRule::checkGifts(std::vector<PokeData>& data,int type)
{
	std::vector<PokeData>giftlist;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type==type&&!filterMainPoke(data[i]))
		{
			giftlist.push_back(data[i]);
		}
	}
	if (giftlist.size()>0)
	{
		std::vector<PokeData> giftdata;
		for (int i=0;i<data.size();i++)
		{
			if (data[i].type==type)
			{
				if (data[i].data==4||data[i].data==12)
				{
					giftdata.push_back(data[i]);
				}
			}
		}
		giftlist.clear();
		return giftdata;
	}
	else
	{
		std::vector<PokeData> giftdata;
		for (int key=0;key<4;key++)
		{
			for (int i=0;i<data.size();i++)
			{
				if (data[i].type==key)
				{
					if (data[i].data==4||data[i].data==12)
					{
						giftdata.push_back(data[i]);
					}
				}
			}
		}
		return giftdata;

	}
	
}
//处理玩家牌
std::vector<PokeData> PokeRule::dealPokeBigData(std::vector<PokeData>& data,int key)
{
	std::vector<PokeData> m_datalist;
	//aa22 
	//99jj and aabb xx (x+1)(x+1)
	for (int i = 0; i < 4; i++)
	{
		for (int j=0;j<data.size();j++)
		{
			if (checkXX(data,i).size()>=2)
			{
				std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,i);
				std::vector<int>idlist;
				for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
				{
					idlist.push_back(it->first);
				}
				for (int key=0;key<xxlist.size()-1;key++)
				{
					if (idlist[key]==idlist[key+1]-1)
					{
						//报错，？？？
						std::vector<PokeData>showData=xxlist.find(idlist[key])->second;
						showData.push_back(xxlist.find(idlist[key+1])->second[0]);
						showData.push_back(xxlist.find(idlist[key+1])->second[1]);

						idlist.clear();
						xxlist.clear();
						return showData;
					}
				}
				for (int key=0;key<xxlist.size()-1;key++)
				{
					//99 jj
					if (idlist[key]==8&&idlist[key+1]==10)
					{
						std::vector<PokeData>showData=xxlist.find(key)->second;
						showData.push_back(xxlist.find(key+1)->second[0]);
						showData.push_back(xxlist.find(key+1)->second[1]);
						idlist.clear();
						xxlist.clear();
						return showData;
					}
				}
				
			}
		}
	}
	//22 22   有问题
	std::vector<PokeData>twolist;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].data==1)
		{
			twolist.push_back(data[i]);
		}
	}
	if (checkXX(twolist,UserInfo::getInstance()->getType()).size()>=2)
	{
		std::vector<PokeData>showPoke;
		std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(twolist,UserInfo::getInstance()->getType());
		for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
		{
			if (it->second[0].type==UserInfo::getInstance()->getType())
			{
				showPoke=it->second;
			}
			if (showPoke.size()>0)
			{
				showPoke.push_back(it->second[0]);
				showPoke.push_back(it->second[1]);
			}
			if (showPoke.size()==4)
			{
				xxlist.clear();
				twolist.clear();
				return showPoke;
			}
		}
	}
	//10 10 10 10
	std::vector<PokeData>tenlist;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].data==9)
		{
			tenlist.push_back(data[i]);
		}
	}
	if (checkXX(tenlist,UserInfo::getInstance()->getType()).size()>=2)
	{
		std::vector<PokeData>showPoke;
		std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(tenlist,UserInfo::getInstance()->getType());
		for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
		{
			if (it->second[0].type==UserInfo::getInstance()->getType())
			{
				showPoke=it->second;
			}
			if (showPoke.size()>0)
			{
				showPoke.push_back(it->second[0]);
				showPoke.push_back(it->second[1]);
			}
			if (showPoke.size()==4)
			{
				xxlist.clear();
				twolist.clear();
				return showPoke;
			}
		}

	}
	

	//--------------------------------------------------------华丽的分割线---------------------------------------------------------------
	//check AAK and AA
	for (int i=0;i<4;i++)
	{
		if (i!=key)
		{
			//if(CommonUtils::checkAAK(data,i).data!=-1)
			//{
			//	m_datalist.push_back(CommonUtils::checkAAK(data,i));
			//	return m_datalist;
			//}
			bool IsHaveAA=false;
			std::vector<PokeData> retData;
			if (checkXX(data,i).size()>0)
			{
				std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,i);
				for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
				{
					if (it->first==13)
					{
						retData=it->second;
						IsHaveAA=true;
						//return it->second;
					}
				}
			}
			if (IsHaveAA)
			{
				for(int i=1;i<data.size();i++)
				{
					if(retData[0].type==data[i].type &&data[i].data==12)
					{
						retData.clear();
						retData.push_back(data[i]);
						return retData;
					}
				}

				//retData;
			}
			
			
		}
	}
	//check AA 还是要检测，要不会拆分AA
	for (int i=0;i<4;i++)
	{
		if (i!=key)
		{
			if (checkXX(data,i).size()>0)
			{
				std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,i);
				for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
				{
					if (it->first==13)
					{
						return it->second;
					}
				}
			}
		}
	}
	//check A	
	if(CommonUtils::checkA(data,key).data!=-1)
	{
		for (int i=0;i<4;i++)
		{
			if (i!=key)
			{
				m_datalist.push_back(CommonUtils::checkA(data,key));
				return m_datalist;
			}
		}
	}
	//check XX
	for (int i=0;i<4;i++)
	{
		if (i!=key)
		{
			if (checkXX(data,i).size()>0)
			{
				std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,i);
				std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();
				return it->second;
			}
		}
	}
	//quan wei zheng zhu huo fu pai hen  shao di yu wu ge
	//全为正主牌，或副牌很少，低于五个了
	std::vector<PokeData>fuPoke;
	
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type!=key)
		{
			fuPoke.push_back(data[i]);
		}
	}	
	
	
	if (fuPoke.size()<5)
	{
		fuPoke.clear();//释放资源
		//chu 2 poke
		std::vector<PokeData>zhuPoke;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].data==1&&!PokeRule::isExistXX(data,1,UserInfo::getInstance()->getType(),true))
			{
				zhuPoke.push_back(data[i]);
			}
		}
		if (zhuPoke.size()>0)
		{
			m_datalist.push_back(zhuPoke[0]);//为什么出一个？？ 对子不可以出？
			zhuPoke.clear();
			return m_datalist;
		}
	}
	//deal single poke
	//处理单牌
	int type=-1;
	for (int i=0;i<4;)
	{
		if (i!=key)
		{
			if(PokeRule::checkType(data,i))
			{
				type=i;
				break;
			}
			else
			{
				i++;
			}
		}
		else
		{
			i++;
		}
	}
	//////////////////////////////华丽的分割线///////////////////////////////////////////////////////
	if (type==-1)
	{
		//type=key;//mei fu le
		//std::vector<PokeData>sameTypeData;
		//for (int i=0;i<data.size();i++)
		//{
		//	if (type==data[i].type||filterMainPoke(data[i]))
		//	{
		//		sameTypeData.push_back(data[i]);//没副了，还要判断？
		//	}
		//}
		//优化算法
		std::vector<PokeData>sameTypeData=data;//不要做判断了
		PokeData bigData=sameTypeData[0];
		for (int i=0;i<sameTypeData.size();i++)
		{

			if (bigData.data<sameTypeData[i].data)
			{
				bigData=sameTypeData[i];//出最大的牌，一定吗？
			}
		}
		m_datalist.push_back(bigData);
		return m_datalist;	

	}
	//有副牌 其他的不知
	std::vector<PokeData>sameTypeData;
	for (int i=0;i<data.size();i++)
	{
		if (type==data[i].type&&!filterMainPoke(data[i]))//？ 过滤干嘛
		{
			sameTypeData.push_back(data[i]);
		}
	}
	if(sameTypeData.size()==0)
	{
		m_datalist.push_back(data[0]);
		return m_datalist;
	}
	//要是全是正主，可？
	//empty() zhu fu pai mei le   bug
	PokeData bigData=sameTypeData[0];
	for (int i=0;i<sameTypeData.size();i++)
	{

		if (bigData.data<sameTypeData[i].data)
		{
			bigData=sameTypeData[i];
		}
	}
	m_datalist.push_back(bigData);
	return m_datalist;	

}
bool PokeRule::checkBankerPoke(std::vector<PokeData>& data,int type)
{
	for(int i=0;i<data.size();i++)
	{
		if(type==data[i].type)
		{
			return true;
		}
	}
	return false;
}
PokeData PokeRule::dealMainBankerPoke(PokeData bigdata,std::vector<PokeData>& data,int type)
{
	std::vector<PokeData>typePokeList;
	//main poke
	int firsttype=UserInfo::getInstance()->getFirstType();
	std::vector<PokeData>firstpoke=UserInfo::getInstance()->getFirstPoke();
	if (filterMainPoke(firstpoke[0]))
	{
		firsttype=3;
		firstpoke.clear();
	}
	//有人杀主
	//if (firsttype!=type)
	//{
	//	for(int i=0;i<data.size();i++)
	//	{
	//		if (firsttype==data[i].type)
	//		{
	//			if (!filterMainPoke(data[i]))
	//			{
	//				if (!isExistXX(data,data[i].data,type))
	//				{
	//					typePokeList.push_back(data[i]);
	//				}

	//			}
	//		}
	//	}
	//	if (typePokeList.size()==0)
	//	{
	//		for(int i=0;i<data.size();i++)
	//		{
	//			if (firsttype==data[i].type)
	//			{
	//				if (!filterMainPoke(data[i]))
	//				{
	//					typePokeList.push_back(data[i]);
	//				}
	//			}
	//		}
	//	}
	//	if (typePokeList.size()>0)
	//	{
	//		return getMinDataPoke(typePokeList,1)[0];
	//	}
	//	else
	//	{
	//		for (int j=0;j<4;j++)
	//		{
	//			for(int i=0;i<data.size();i++)
	//			{
	//				if (j==data[i].type&&j!=type)
	//				{
	//					if (!filterMainPoke(data[i]))
	//					{
	//						typePokeList.push_back(data[i]);
	//					}
	//				}
	//			}
	//		}
	//		if (typePokeList.size()>0)
	//		{
	//			return getMinDataPoke(typePokeList,1)[0];
	//		}
	//		else
	//		{
	//			return getMinDataPoke(data,1)[0];
	//		}
	//	}
	//}
	//main poke
	for(int i=0;i<data.size();i++)
	{
		if (type==data[i].type&&!filterMainPoke(data[i]))
		{
			if (!isExistXX(data,data[i].data,type))
			{
				typePokeList.push_back(data[i]);
			}

		}
	}
	//
	if (typePokeList.size()>0)
	{
		return getMinDataPoke(typePokeList,1)[0];
	}
	else
	{
		for(int i=0;i<data.size();i++)
		{
			if (type==data[i].type&&!filterMainPoke(data[i]))
			{
				typePokeList.push_back(data[i]);
			}
		}
		
	}
	//
	if (typePokeList.size()>0)
	{
		return getMinDataPoke(typePokeList,1)[0];
	}
	else
	{
		for(int i=0;i<data.size();i++)
		{
			if (filterMainPoke(data[i]))
			{
				if (!isExistXX(data,data[i].data,type))
				{
					typePokeList.push_back(data[i]);
				}

			}
		}
		if (typePokeList.size()>0)
		{
			return getMinDataPoke(typePokeList,1)[0];
		}
		else
		{
			for(int i=0;i<data.size();i++)
			{
				if (filterMainPoke(data[i]))
				{
				    typePokeList.push_back(data[i]);
				}
			}
			if (typePokeList.size()>0)
			{
				return getMinDataPoke(typePokeList,1)[0];
			}
		}
	}
	return getMinDataPoke(data,1)[0];
}
PokeData PokeRule::dealBankerPoke(PokeData bigdata,std::vector<PokeData>& data,int type)
{
	bool ismain=false;
	std::vector<PokeData>typePokeList;
	std::vector<PokeData>firstpoke=UserInfo::getInstance()->getFirstPoke();
	for(int i=0;i<firstpoke.size();i++)
	{
		if(firstpoke[i].data==9||firstpoke[i].data==1||firstpoke[i].data>=14)
		{
			ismain=true;
		}
	}
	
	//main poke
	int firsttype=UserInfo::getInstance()->getFirstType();
	
	if (firsttype==type)
	{
		ismain=true;
	}
	if (ismain)
	{
		firstpoke.clear();
		//处理第一手牌是主牌 的函数
		return dealMainBankerPoke(bigdata,data,type);
	}
	//----------------------------华丽的分割线-------------------------------------------
	ismain=false;
	//杀主 10 2 joker?
	if (bigdata.data==9||bigdata.data==1||bigdata.data>=14||bigdata.data==type)
	{
		ismain=true;
	}
	if(ismain)
	{
		for(int i=0;i<data.size();i++)
		{
			if(firsttype==data[i].type&&!filterMainPoke(data[i]))
			{
				ismain=false;
				break;
			}
		}
		if(ismain)
		{
			std::vector<PokeData> mainpoke;
			//大牌是正主牌
			if(filterMainPoke(bigdata))
			{
				for(int i=1;i<data.size();i++)
				{
					if(filterMainPoke(data[i]))
					{
						if(bigdata.data==14 && data[i].data==15)
						{
							return data[i];
						}
						if(bigdata.data==9 && firstpoke[0].type!=type)
						{
							if(data[i].data==9&& data[i].type==type)
							{
								return data[i];
							}
							if(data[i].data>=14)
							{
								return data[i];
							}
						}
						if(bigdata.data==9 && firstpoke[0].type==type)
						{
							if(data[i].data>=14)
							{
								return data[i];
							}
						}
						if(bigdata.data==1 && firstpoke[0].type!=type)
						{
							if(data[i].data==9||data[i].data>=14||(data[i].data==1 && data[i].type==type))
							{
								return data[i];
							}
						}
						if(data[i].data==9 && data[i].data>=14)
							return data[i];
					}
				}
			}
			firstpoke.clear();
			for(int i=1;i<data.size();i++)
			{
				if(data[i].type==type)
				{
					if(data[i].data>bigdata.data)
					{
						return data[i];
					}
				}
			}
		}
			//处理杀主的主牌处理
			//return dealMainBankerPoke(bigdata,data,type);
	}
	//副牌 不拆对？
	for(int i=0;i<data.size();i++)
	{
		if (firsttype==data[i].type)
		{
			if (!filterMainPoke(data[i]))
			{
				if (!isExistXX(data,data[i].data,firsttype))
				{
					typePokeList.push_back(data[i]);
				}
			}
		}
	}
	//出大牌，或最小的牌
	if (typePokeList.size()>0)
	{
		bool isExist=false;
		for (int i=0;i<typePokeList.size();i++)
		{
			if (typePokeList[i].data>bigdata.data)
			{
				bigdata=typePokeList[i];
				isExist=true;
			}
		}
		if (isExist)
		{
			return bigdata;
		}
		else
		{
			return getMinDataPoke(typePokeList,1)[0];
		}
	}
	//副牌 ，拆对

	if (typePokeList.size()==0)
	{
		for(int i=0;i<data.size();i++)
		{
			if (firsttype==data[i].type)
			{
				if (!filterMainPoke(data[i]))
				{
					typePokeList.push_back(data[i]);
				}
			}
		}
		if (typePokeList.size()>0)
		{
			return getMinDataPoke(typePokeList,1)[0];
		}
	}
	//当前门没有，考虑杀主
	
	//有分  加个判断，要是副牌很多时，用正主杀，待。。。。。。。。。
	if (typePokeList.size()==0)
	{
		//same type = 0
		//it have count, can kill it;//有分，处理杀主，没分了
		if (UserInfo::getInstance()->getIsExistCount())
		{
			std::vector<PokeData> pokedata=RobotRule::TypePoke(data,type);
			for (int i=0;i<pokedata.size();i++)
			{
				// 5和k 杀主
				if (pokedata[i].data==4||pokedata[i].data==12)
				{
					if (!isExistXX(pokedata,pokedata[i].data,type))
					{
						return pokedata[i];
					}
				}
			}
			//没分杀主
			for (int i=0;i<pokedata.size();i++)
			{
				// 小牌 杀主  2 10
				
				if (!isExistXX(pokedata,pokedata[i].data,type))
				{
					return pokedata[i];
				}
					
				
			}
		}
	}
	//没分  副牌就5个左右时，用正主出牌
	if (typePokeList.size()==0)
	{
		std::vector<PokeData> pokedata=RobotRule::TypePoke(data,type);
		for (int i=0;i<pokedata.size();i++)
		{
			// 5和k 杀主
			if (pokedata[i].data==4||pokedata[i].data==12)
			{
				if (!isExistXX(pokedata,pokedata[i].data,type))
				{
					return pokedata[i];
				}
			}
		}
		//没分杀主
		for (int i=0;i<pokedata.size();i++)
		{
			// 小牌 杀主  2 10
				
			if (!isExistXX(pokedata,pokedata[i].data,type))
			{
				return pokedata[i];
			}	
		}
	}
	//主牌   随便消一门牌,一下处理
	int bankertype=UserInfo::getInstance()->getType();
	for (int key=0;key<4;key++)
	{
        if (key!=bankertype)
        {
			for(int i=0;i<data.size();i++)
			{
				if (key==data[i].type)
				{
					if (!filterMainPoke(data[i]))
					{
						if (!isExistXX(data,data[i].data,key))
						{
							typePokeList.push_back(data[i]);
						}

					}
				}
			}
        }
	}
	//
	if (typePokeList.size()==0)
	{
		for (int key=0;key<4;key++)
		{
			if (key!=bankertype)
			{
				for(int i=0;i<data.size();i++)
				{
					if (key==data[i].type)
					{
						if (!filterMainPoke(data[i]))
						{
							typePokeList.push_back(data[i]);
						}
					}
				}
			}
		}

	}
	else 
	{
		return getMinDataPoke(typePokeList,1)[0];
	}
	//
	if (typePokeList.size()==0)
	{
		for(int i=0;i<data.size();i++)
		{
			if (bankertype==data[i].type)
			{
				if (!filterMainPoke(data[i]))
				{
					typePokeList.push_back(data[i]);
				}
			}
		}	
	}
	else 
	{
		return getMinDataPoke(typePokeList,1)[0];
	}
	//
	if (typePokeList.size()==0)
	{
		for(int i=0;i<data.size();i++)
		{
			if (bankertype==data[i].type)
			{
			    typePokeList.push_back(data[i]);
			}
		}	
	}
	else 
	{
		return getMinDataPoke(typePokeList,1)[0];
	}
	//bug
	return  getMinDataPoke(data,1)[0];
}

//two or more poke
std::map<int,std::vector<PokeData>>  PokeRule::checkXX(std::vector<PokeData>& data,int type,bool ischeckmain/*=false*/)
{
	
	std::vector<PokeData>sametypePoke;
	for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
	{

		if (type==it->type&&!ischeckmain)
		{
			if (!filterMainPoke((*it)))
			{
				sametypePoke.push_back((*it));
			}
		}
		//
		if (ischeckmain&&filterMainPoke((*it)))
		{
			sametypePoke.push_back((*it));
		}
	}
	std::map<int,std::vector<PokeData>>XXlist;
	for (int i=0;i+1<sametypePoke.size();i++)
	{

		if (sametypePoke[i].data==sametypePoke[i+1].data)
		{
			if (ischeckmain)
			{
				if (sametypePoke[i].type==sametypePoke[i+1].type)
				{
					std::vector<PokeData> XXdata;
					XXdata.push_back(sametypePoke[i]);
					XXdata.push_back(sametypePoke[i+1]);
					XXlist[sametypePoke[i].data]=XXdata;
				}
			}
			else
			{
				if (!filterMainPoke(sametypePoke[i]))
				{
					std::vector<PokeData> XXdata;
					XXdata.push_back(sametypePoke[i]);
					XXdata.push_back(sametypePoke[i+1]);
					XXlist[sametypePoke[i].data]=XXdata;
				}
			}
		}
	}
	if (XXlist.size()>0)
	{
		return XXlist;
	}
	else
	{
		std::map<int,std::vector<PokeData>> datalist;
		return datalist;
	}
}
std::vector<PokeData> PokeRule::dealXXPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id)
{

	//??
	bool ismain=false;
	if (bigdata[0].data==1||bigdata[0].data==9||bigdata[0].data>=14)
	{
		ismain=true;
	}
	int key=UserInfo::getInstance()->getType();
	if (type==key)
	{
		ismain=true;
	}
	if (ismain)
	{
		if (PokeRule::checkXX(data,key,true).size()>0)
		{
			std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,key,true);
			for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
			{
				if (CalculatePoint(bigdata[0],key,type)<CalculatePoint(it->second[0],key,type))
				{
					return it->second;
				}
			}
			std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();
			return it->second;
		}
		else if (PokeRule::checkXX(data,type).size()>0)
		{
			std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,type);
			for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
			{
				if (CalculatePoint(bigdata[0],key,type)<CalculatePoint(it->second[0],key,type))
				{
					return it->second;
				}
			}
			std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();
			return it->second;
		}
		else
		{
			//不要处理对子 ok
			return dealXiaoPoke(data,bigdata,key,big,id);

		}
	}
	if (PokeRule::checkXX(data,type).size()>0)
	{
		std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,type);
		for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
		{
			if (bigdata[0].data<it->first)
			{
				return it->second;
			}
		}
		std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();
		return it->second;
	}
	else
	{
		//same type = 0
		//it have count, can kill it;
		if (UserInfo::getInstance()->getIsExistCount()&&RobotRule::TypePoke(data,type).size()==0)
		{
			if (PokeRule::checkXX(data,key).size()>0)
			{
				std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(data,key);
				std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();
				return it->second;
			}
		}
		return dealXiaoPoke(data,bigdata,type,big,id);
		
	}
}
bool PokeRule::filterMainPoke(PokeData data)
{
	if(data.data==1)                   {return true;}
	if(data.data==9)                   {return true;}
	if(data.data==14||data.data==15)   {return true;}	
	return false;
}
//? 0817  修正处理 ，简化问题，不重复判断
std::vector<PokeData> PokeRule::dealXiaoMainPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id)
{
	//主牌处理?
	std::vector<PokeData>sametypePoke;
	for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
	{
		if((*it).type==UserInfo::getInstance()->getType())
		{
			sametypePoke.push_back((*it));
		}
	}
	if(sametypePoke.size()<2)
	{
		for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
		{
			if(filterMainPoke((*it)))
			{
				sametypePoke.push_back((*it));
			}
		}
	}
	if(sametypePoke.size()>=2)
	{
		return getMinDataPoke(sametypePoke,2);
	}
	//副牌 不拆分对子，其实问题不大了，牌不多了
	if(sametypePoke.size()==1)
	{
		sametypePoke.push_back(getMinDataPoke(data,1)[0]);
		return sametypePoke;
	}
	return getMinDataPoke(data,2);
	
}
//不要处理对子，到这步对子处理完了
std::vector<PokeData> PokeRule::dealXiaoPoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id)
{
	bool ismain=false;
	if (bigdata[0].data==1||bigdata[0].data==9||bigdata[0].data>=14)
	{
		ismain=true;
	}
	if (type==UserInfo::getInstance()->getType())
	{
		ismain=true;
	}
	std::vector<PokeData>sametypePoke;
	if (ismain)
	{
		//不要处理对子
		dealXiaoMainPoke(data,bigdata,type,big,id);
	}
	//filter fen
	std::vector<PokeData>fenData;
	if (id==1&&big==3)
	{
		if (RobotRule::Deal_count(bigdata,LocalGameServer::getInstance()->getClientDataSize()))
		{
			std::vector<PokeData>robotData=PokeRule::checkGifts(data,type);
			if (robotData.size()>=2)
			{
				return getMinDataPoke(robotData,2);
			}
			if (robotData.size()==1)
			{
				fenData=robotData;
				robotData.clear();
			}
		}
	}
	if ((big==0||big==2)&&id!=1)
	{
		if (RobotRule::Deal_count(bigdata,LocalGameServer::getInstance()->getClientDataSize()))
		{
			std::vector<PokeData>robotData=PokeRule::checkGifts(data,type);
			if (robotData.size()>=2)
			{
				return getMinDataPoke(robotData,2);
			}
			if (robotData.size()==1)
			{
				fenData=robotData;
				robotData.clear();
			}
		}
	}
	else
	{

	}
	//有当前type排
	for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
	{
		if (type==it->type&&!filterMainPoke((*it)))
		{
			if (!isExistXX(data,(*it).data,type))
			{
				sametypePoke.push_back((*it));
			}
		}
	}
	//考虑当前排没了的处理。。。。。。。。
	if (sametypePoke.size()>0)
	{

		if (sametypePoke.size()==1)
		{
			std::vector<PokeData> m_data;
			m_data.push_back(sametypePoke[0]);
			//bu xiao zhu bu xiao fen
			m_data.push_back(getMinXiaoPoke(data,1,type)[0]);
			return m_data;
		}
		else
		{
			if (fenData.size()==1)
			{
				for (int i=0;i<sametypePoke.size();i++)
				{
					if (fenData[0].data!=sametypePoke[i].data)
					{
						fenData.push_back(sametypePoke[i]);
					}
					if (fenData.size()==2)
					{
						sametypePoke.clear();
						return fenData;
					}
				}
				
			}
			return getMinDataPoke(sametypePoke,2);
		}
	}
	else
	{
		//主牌过滤有问题
		for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
		{
			//只过滤了正主？  待改。。。。。。。。。。。。。。
			//修正。0812
			if ((*it).type!=UserInfo::getInstance()->getType()&&!filterMainPoke((*it)))
			{
				if (!isExistXX(data,(*it).data,(*it).type))
				{
					sametypePoke.push_back((*it));
				}
			}	
		}
		//识别主牌有问题，到这步
		if (sametypePoke.size()>=2)
		{
			return getMinDataPoke(sametypePoke,2);
		}
		else
		{
			//修正主牌3 的判断问题0812
			sametypePoke.clear();
			for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
			{
				if (!filterMainPoke((*it)))
				{
					if (!isExistXX(data,(*it).data,(*it).type))
					{
						sametypePoke.push_back((*it));
					}
				}	
			}
			if (sametypePoke.size()>=2)
			{
				return getMinDataPoke(sametypePoke,2);
			}
			else
			{
				for (std::vector<PokeData>::iterator it=data.begin();it!=data.end();++it)
				{

					if (!filterMainPoke((*it)))
					{
						if (!isExistXX(data,(*it).data,(*it).type))
						{
							sametypePoke.push_back((*it));
						}
					}	
				}
				if (sametypePoke.size()>=2)
				{
					return getMinDataPoke(sametypePoke,2);
				}
			}
			
		}
		return getMinDataPoke(data,2);
	}
}
std::vector<PokeData> PokeRule::getMinXiaoPoke(std::vector<PokeData>& data,int size,int type)
{
	std::vector<PokeData> pokelist;
	for (int i=0;i<data.size();i++)
	{
		if (!filterMainPoke(data[i]))
		{
			if (data[i].type!=UserInfo::getInstance()->getType())
			{
				if (isExistXX(data,data[i].data,type))
				{
					pokelist.push_back(data[i]);
				}
			}
		}
	}
	if (pokelist.size()>=size)
	{
		return getMinDataPoke(pokelist,size);
	}
	releaselist(pokelist);
	//
	for (int i=0;i<data.size();i++)
	{
		if (!filterMainPoke(data[i]))
		{
			if (data[i].type!=UserInfo::getInstance()->getType())
			{
				
				pokelist.push_back(data[i]);
			}
		}
	}
	if (pokelist.size()>=size)
	{
		return getMinDataPoke(pokelist,size);
	}
	releaselist(pokelist);
	//
	for (int i=0;i<data.size();i++)
	{
		if (!filterMainPoke(data[i]))
		{
		    pokelist.push_back(data[i]);	
		}
	}
	if (pokelist.size()>=size)
	{
		return getMinDataPoke(pokelist,size);
	}
	releaselist(pokelist);
	//
	return getMinDataPoke(data,size);

}
std::vector<PokeData> PokeRule::getMinDataPoke(std::vector<PokeData>& data,int size)
{
	std::sort(data.begin(),data.end(),PokeRule());
	std::vector<PokeData> m_data;
	for (int i=0;i<size;i++)
	{
		m_data.push_back(data[i]);
	}
	return m_data;
}
/////////////////////////////////////////////////////////
unsigned int PokeRule::sequence(PokeData data)
{
	int value=0;
	value+=data.data*100;
	return value;
}
//////////////////////////////////////////////////////////////
//poke count > =4
std::vector<PokeData> PokeRule::dealMorePoke(std::vector<PokeData>& data,std::vector<PokeData>& bigdata,int type,int big,int id)
{
	int bigsize=(int)bigdata.size();
	std::vector<PokeData>sametypedatalist;
	std::vector<PokeData>returndatalist;
	//主牌 处理部分
	int mainkey=UserInfo::getInstance()->getType();
	type=UserInfo::getInstance()->getFirstType();
	
	
	//正主
	std::vector<PokeData> mainPoke;
	if(filterMainPoke(bigdata[0])||bigdata[0].type==mainkey)
	{
		for(int i=0;i<data.size();i++)
		{
			if(filterMainPoke(data[i]))
			{
				//
				mainPoke.push_back(data[i]);
				type=mainkey;
			}
		}
	}
	//副牌
	for (int i=0;i<data.size();i++)
	{
		if (!filterMainPoke(data[i]))
		{
			if (type==data[i].type)
			{
				sametypedatalist.push_back(data[i]);
			}
		}
	}

	if (sametypedatalist.size()>=bigsize)
	{
		if (checkXX(sametypedatalist,type).size()>=2)
		{
			std::map<int,std::vector<PokeData>> xxlist=PokeRule::checkXX(sametypedatalist,type);
			std::vector<int>idlist;
			for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
			{
				idlist.push_back(it->first);
			}
			for (int key=0;key<xxlist.size()-1;key++)
			{
				if (idlist[key]==idlist[key+1]-1)
				{
					if(xxlist.find(key)!=xxlist.end())
					{
						std::vector<PokeData>showData=xxlist.find(key)->second; 
						showData.push_back(xxlist.find(key+1)->second[0]);
						showData.push_back(xxlist.find(key+1)->second[1]);
						idlist.clear();
						xxlist.clear();
						return showData;
					}
					
				}
			}
			for (int key=0;key<xxlist.size()-1;key++)
			{
				//99 jj
				if (idlist[key]==8&&idlist[key+1]==10)
				{
					std::vector<PokeData>showData=xxlist.find(key)->second;
					showData.push_back(xxlist.find(key+1)->second[0]);
					showData.push_back(xxlist.find(key+1)->second[1]);
					idlist.clear();
					xxlist.clear();
					return showData;
				}
			}
			//xx aa
			for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
			{
				returndatalist.push_back(it->second[0]);
				returndatalist.push_back(it->second[1]);
			}
			returndatalist.clear();
			returndatalist=getMinDataPoke(sametypedatalist,4);
			return returndatalist;
		}
		else if(checkXX(sametypedatalist,type).size()==1)
		{
			//副牌对子 一或 没有的处理
			std::map<int,std::vector<PokeData>> xxlist;
			
			xxlist=PokeRule::checkXX(sametypedatalist,type);

			returndatalist.clear();
			for (std::map<int,std::vector<PokeData>>::iterator it=xxlist.begin();it!=xxlist.end();++it)
			{
				returndatalist.push_back(it->second[0]);
				returndatalist.push_back(it->second[1]);
			}
			if(mainPoke.size()>2)//包含正主时 
			{
				if(checkXX(mainPoke,type,true).size()>1)
				{
					std::map<int,std::vector<PokeData>> xxmainlist=PokeRule::checkXX(mainPoke,type,true);
					for (std::map<int,std::vector<PokeData>>::iterator it=xxmainlist.begin();it!=xxmainlist.end();++it)
					{
						returndatalist.push_back(it->second[0]);
						returndatalist.push_back(it->second[1]);
					}
					xxmainlist.clear();
					xxlist.clear();
					return returndatalist;
				}
			}
		}
		else if(checkXX(sametypedatalist,type).size()==0)
		{
			std::map<int,std::vector<PokeData>> xxlist;
			if(mainPoke.size()>2)//包含正主时 
			{
				if(checkXX(mainPoke,type,true).size()>1)
				{
					std::map<int,std::vector<PokeData>> xxmainlist=PokeRule::checkXX(mainPoke,type,true);
					returndatalist.push_back(xxmainlist[0][0]);
					returndatalist.push_back(xxmainlist[0][1]);
					xxmainlist.clear();
					xxlist.clear();
					//return returndatalist;
				}
			}
			std::vector<PokeData> retData;
			if(returndatalist.size()==2)
			{
				retData.push_back(returndatalist[0]);
				retData.push_back(returndatalist[1]);
				for(int k=1;k<retData.size();k++)
				{
					if(sametypedatalist[k].data!=returndatalist[0].data&&sametypedatalist[k].data!=returndatalist[1].data)
					{
						retData.push_back(sametypedatalist[k]);
						if(retData.size()==4)
						{
							return retData;
						}

					}
				}
			}

		}
		if(returndatalist.size()>=4)
		{
			return getMinDataPoke(returndatalist,4);
		}
		else if(returndatalist.size()<4 && returndatalist.size()>=1)
		{
			std::vector<PokeData> retData;
			for(int i=1;i<returndatalist.size();i++)
			{
				retData.push_back(returndatalist[i]);
			}
			for(int k=1;k<retData.size();k++)
			{
				if(sametypedatalist[k].data!=returndatalist[0].data&&sametypedatalist[k].data!=returndatalist[1].data)
				{
					retData.push_back(sametypedatalist[k]);
					if(retData.size()==4)
					{
						return retData;
					}

				}
			}
		}
	}
	//要是对子 只有一个，还要出两个牌，要怎么处理，以处理
	//处理消分
	if (big==3&&id==1)
	{
		for (int i=0;i<data.size();i++)
		{
			if (data[i].type!=type&&data[i].type!=UserInfo::getInstance()->getType())
			{
				if (!filterMainPoke(data[i])&&!isExistXX(data,data[i].data,data[i].type))
				{
					if (data[i].data==4||data[i].data==12)
					{
						if (sametypedatalist.size()!=4)
						{
							sametypedatalist.push_back(data[i]);
						}
					}
				}
			}
		}
	}
	//处理消分
	if ((big==0||big==2)&&id!=1)
	{
		for (int i=0;i<data.size();i++)
		{
			if (data[i].type!=type&&data[i].type!=UserInfo::getInstance()->getType())
			{
				if (!filterMainPoke(data[i])&&!isExistXX(data,data[i].data,data[i].type))
				{
					if (data[i].data==4||data[i].data==12)
					{
						if (sametypedatalist.size()!=4)
						{
							sametypedatalist.push_back(data[i]);
						}
					}
				}
			}
		}
	}
	//filter  fen
	if (sametypedatalist.size()==bigsize)
	{
		return sametypedatalist;
	}
	//end
	//大于4 个牌的处理，变态形容。。。。。。。。。
	//size <4;
	std::vector<PokeData>otherpoke;
	if (sametypedatalist.size()>0&&sametypedatalist.size()<4)
	{
		for (int i=0;i<data.size();i++)
		{
			if (data[i].type!=type&&data[i].type!=UserInfo::getInstance()->getType())
			{
				if (!filterMainPoke(data[i])&&!isExistXX(data,data[i].data,data[i].type))
				{
					otherpoke.push_back(data[i]);
				}
			}
		}
	}
	int size=(int)sametypedatalist.size()+(int)otherpoke.size();
	if (size>=4)
	{
		returndatalist.clear();
		returndatalist=getMinDataPoke(otherpoke,4-(int)sametypedatalist.size());
		for (int i=0;i<sametypedatalist.size();i++)
		{
			returndatalist.push_back(sametypedatalist[i]);
		}
		return returndatalist;
	}
	else{
		releaselist(otherpoke);
		releaselist(returndatalist);

	}

	for (int i=0;i<data.size();i++)
	{
		if (data[i].type!=type&&data[i].type!=UserInfo::getInstance()->getType())
		{
			if (!filterMainPoke(data[i]))
			{
				otherpoke.push_back(data[i]);
			}
		}
	}
	size=(int)sametypedatalist.size()+(int)otherpoke.size();
	if (size>=4)
	{
		returndatalist.clear();
		returndatalist=getMinDataPoke(otherpoke,4-(int)sametypedatalist.size());
		for (int i=0;i<sametypedatalist.size();i++)
		{
			returndatalist.push_back(sametypedatalist[i]);
		}
		return returndatalist;
	}
	else
	{
		releaselist(otherpoke);
		releaselist(returndatalist);
	}
	//

	for (int i=0;i<data.size();i++)
	{
		if (data[i].type!=type)
		{
			if (!filterMainPoke(data[i]))
			{
				otherpoke.push_back(data[i]);
			}
		}
	}
	size=(int)sametypedatalist.size()+(int)otherpoke.size();

	if (size>=4)
	{
		returndatalist.clear();
		returndatalist=getMinDataPoke(otherpoke,4-(int)sametypedatalist.size());
		for (int i=0;i<sametypedatalist.size();i++)
		{
			returndatalist.push_back(sametypedatalist[i]);
		}
		return returndatalist;
	}
	else
	{
		releaselist(otherpoke);
		releaselist(returndatalist);
	}

	//

	for (int i=0;i<data.size();i++)
	{
		if (data[i].type!=type)
		{
			otherpoke.push_back(data[i]);
		}
	}
	size=(int)sametypedatalist.size()+(int)otherpoke.size();

	if (size>=4)
	{
		returndatalist.clear();
		returndatalist=getMinDataPoke(otherpoke,4-(int)sametypedatalist.size());
		for (int i=0;i<sametypedatalist.size();i++)
		{
			returndatalist.push_back(sametypedatalist[i]);
		}
		return returndatalist;
	}
	else
	{
		releaselist(otherpoke);
		releaselist(returndatalist);
	}

	//
	//returndatalist.clear();
	if (sametypedatalist.size()==0)
	{
		for(int i=0;i<data.size();i++)
		{
			if (!filterMainPoke(data[i])&&data[i].type!=UserInfo::getInstance()->getType())
			{
				if (!isExistXX(data,data[i].data,data[i].type))
				{
					returndatalist.push_back(data[i]);
				}
			}
		}
	}
	if (returndatalist.size()>=4)
	{
		return getMinDataPoke(returndatalist,4);
	}	
	//release
	releaselist(sametypedatalist);
	return getMinDataPoke(data,4);
}
std::map<int,std::vector<PokeData>> PokeRule::checktypeXX(std::vector<PokeData>& data,int type,bool ischeckmain/*=false*/)
{
	std::vector<PokeData>sametypelist;
	for (int i=0;i<data.size();i++)
	{
		if (data[i].type==type)
		{
			if (!filterMainPoke(data[i]))
			{
				sametypelist.push_back(data[i]);
			}
			
		}
		if (ischeckmain)
		{
			if (filterMainPoke(data[i]))
			{
				sametypelist.push_back(data[i]);
			}
		}
	}
	std::map<int,std::vector<PokeData>>XXlist;
	if (sametypelist.size()>2)
	{
		for (int i = 0; i < sametypelist.size()-1; i++)
		{
			if (ischeckmain)
			{
				if (sametypelist[i].data==sametypelist[i+1].data&&sametypelist[i].type==sametypelist[i+1].type)
				{
					std::vector<PokeData>xxpoke;
					xxpoke.push_back(sametypelist[i]);
					xxpoke.push_back(sametypelist[i+1]);
					XXlist[sametypelist[i].data]=xxpoke;
				}
			}
			if (sametypelist[i].data==sametypelist[i+1].data)
			{
				std::vector<PokeData>xxpoke;
				xxpoke.push_back(sametypelist[i]);
				xxpoke.push_back(sametypelist[i+1]);
				XXlist[sametypelist[i].data]=xxpoke;
			}
		}
	}
	
	releaselist(sametypelist);
	return XXlist;
}
void PokeRule::releaselist(std::vector<PokeData>& data)
{
	if (data.size()>0)
	{
		data.clear();
	}
}
bool PokeRule::isExistXX(std::vector<PokeData>& data,int key,int type,bool ischeckmain/*=false*/)
{
	std::map<int,std::vector<PokeData>>XXlist=checktypeXX(data,type,true);
	if (XXlist.find(key)!=XXlist.end())
	{
		return true;
		
	}
	if (!XXlist.empty())
	{
		XXlist.clear();
	}
	return false;
}
int PokeRule::CalculatePoint(PokeData data,int type,int firsttype)
{
	int value=0;
	//14000 - 15000
	if (data.data>=14)
	{
		value+=data.data*1000;
	}
	//9000 - 10000
	else if (data.data==9)
	{
		value+=data.data*1000;
		if (data.type==type)
		{
			value+=1000;
		}
	}
	//7000 - 8000 
	else if (data.data==1)
	{
		value+=data.data*7000;
//		value+=data.color*100;
		if (data.type==type)
		{
			value+=1000;
		}
	}
	else
	{
		//
		if (data.type==type)
		{
			value+=5000;
		}
		value+=data.data*100;
	}
	return value;
}