#include "../robot/NewRobot.h"
#include "../common/UserInfo.h"
#include "../game/LocalGameServer.h"
#include <ctime>
//const static int RandData[]={2,3,1,0,2,3,2,3,0,1,2,0,1,3,0,3,2,1,3,2,1,3,2,1,3,0,1,2,3,0,2,3,1,3,2,1,0,1,2,3};//12

void NewRobot::RobotAIDealPoke()
{
	//
	dealPoke(ai->AIDealPoke());//ai≥ˆ≈∆
	//…æ≈∆√ª¥¶¿Ì
	deletePoke(ai->AIDeletePoke());//…æ≥˝≈∆µƒ¥¶¿Ì
}
std::vector<PokeListItem> NewRobot::GetListItem()
{
	//log(">>>>>>>>>>>>>>>>>>>>size = %d",this->_listitem.size());
	return this->_listitem;
}
static long CurrTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}

	



//÷˜µƒ∂‘◊””–Œ Ã‚£¨ ∂±≤ª¡À,∂‘£®“—∏ƒ£©
bool NewRobot::PokeServer(int id)
{
	//log(">>>>>>>>>>>>>>>random = %d",randomInt());
	
	log("robot>>>>>> %d<<<<<<<<<<<<< ",id);
	if(_retlist.size())
		_retlist.clear();
	if(_dellist.size())
		_dellist.clear();
	clearxxlist();
	this->id=id;
	//√ø¥Œ≥ˆ≈∆£¨œ»≈–∂œ◊Ó¥Ûµƒ≈∆£¨Œ™∫Û√Êµƒ≥ˆ≈∆Ã·Ωª≤Œøº
	bigPokeId=LocalGameServer::getInstance()->getWhoBigId();
	_biglist=LocalGameServer::getInstance()->getClientBigData(bigPokeId);
	//size=4;
	//type=4;
	
	
	if(_firstpoke.size()>0)
	{
		_firstpoke.clear();
	}
	_firstpoke=UserInfo::getInstance()->getFirstPoke();
	if(_firstpoke.size()==0)
	{
		//ai ≥ˆ≈∆
		ai=new RobotAI(_listitem,bank);
		RobotAIDealPoke();
		if(getPokeData()==0)
		{
			LocalGameServer::getInstance()->deal_last_poke();
		}
			
		return true;
	}

	firsttype=pokeType(_firstpoke[0]);
	type=firsttype;
	size=_firstpoke.size();

	

	//÷˜≈∆“™øº¬«”√’˝÷˜¥Ú∆ ÷˜≈∆“≤ø…“‘¥Ú∆
	if(checkKingBigPoke(id))
		return true;
	

	//’‚¿ÔŒﬁ–Ë≈–∂œ£¨ «≤ª «÷˜≈∆£¨”¶Œ™”≈œ»øº¬«÷˜≈∆£¨µ•∂¿¥¶¿Ì’˝÷˜£¨æÕ––¡À£ø£ø
	//≤ª––£¨ªπ «“™∑÷ø™¥¶¿Ì£¨º–‘⁄¿Ô√Ê¥¶¿Ì£¨≤ª£¨µ•∂¿£¨¡–≥ˆ¿¥
	if(checkPokeDone(id))
		return true;
	
	//Õ¨¿‡–Õµ•≈∆ªπ√ª¥¶¿Ì£¨±ÿ–Îøº¬«≤∑÷∂‘◊”£¨4∏ˆ≈∆µƒ«Èøˆ

	log("funtction>>checkDoublePoke");
	//size ==2
	if(checkDoublePoke(id))
	{
		//ÃÌº”¥Ú∆µƒ¥¶¿Ì
		return true;
	}
	log("funtction>>checkDoubleDoublePoke");
	//size ==4
	//-------------------------------------------------------------
	if(checkDoubleDoublePoke(id))
	{
		//ÃÌº”¥Û∆µƒ≤Ÿ◊˜
		return true;
	}
	//size = 6
	if(checkSixPoke(id))
		return true;


	//-------------------------------------------------------------
	//øº¬«∆‰À˚≈∆–Õµƒ≈∆≥ˆ¥¶¿Ì¡˜≥Ã£¨◊ﬂ“ª±È
	log("funtction>>checkKingMainPoke");
	//≤Â»Î
	//œ¬√Êøº¬«÷˜≈∆µƒ¥¶¿Ì £¨∞¸∫¨ ÷˜≈∆ ∫Õ’˝÷˜
	if(checkKingMainPoke(id))
	{
		return true;
	}
	log("funtction>>checkOtherSinglePoke");
	//∆‰À¸≈∆–Õµƒµ•≈∆
	if(checkOtherSinglePoke(id))
	{
		return true;
	}
	
	//
	return false;
}
bool NewRobot::checkPokeDone(int id)
{
	log("<NewRobot::checkPokeDone> check Done");
	clearxxlist();

	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==size&&(*it).type==type)
		{
			_xxlist.clear();
			_xxlist=(*it)._list;
			break;
		}
	}
	if(_xxlist.size()>0)
	{
		DeleteItem m_cItem;
		m_cItem.size=(int)size;
		m_cItem.type=type;

		_retlist.clear();
		//”–»±œ›£¨µ±¥Û≈∆ «÷˜≈∆…±÷˜ ±æÕ”–Œ Ã‚£¨¥¶¿Ì≤ª¡À
		if(checkCompare(_biglist[0],_xxlist[_xxlist.size()-1]))
		//if(_biglist[0].data<_xxlist[_xxlist.size()-1].data)//”–◊Ó¥Ûµƒ≥ˆ◊Ó¥Ûµƒ
		{
			if(_retlist.size()<size)
			{
				m_cItem.data.push_back(_xxlist[_xxlist.size()-1].data);
				_retlist.push_back(_xxlist[_xxlist.size()-1]);
				if(size==2&&_xxlist.size()>=2)
				{
					//∂‘◊”“™º”‘ÿ¡Ω∏ˆ
					m_cItem.data.push_back(_xxlist[_xxlist.size()-2].data);
					_retlist.push_back(_xxlist[_xxlist.size()-2]);
				}
				if(size==4&&_xxlist.size()>=4)
				{
					//º”‘ÿ»˝∏ˆ
					m_cItem.data.push_back(_xxlist[_xxlist.size()-2].data);
					_retlist.push_back(_xxlist[_xxlist.size()-2]);
					m_cItem.data.push_back(_xxlist[_xxlist.size()-3].data);
					_retlist.push_back(_xxlist[_xxlist.size()-3]);
					m_cItem.data.push_back(_xxlist[_xxlist.size()-4].data);
					_retlist.push_back(_xxlist[_xxlist.size()-4]);
				}
			}
				
		}
		//for(int i=0;i<_xxlist.size();i++)//±»ΩœÃ´…Ÿ¡À (i<size)  i<_xxlist.size()ª·±®¥Ì
		//{
		//	//‘›«“≥ˆ±»¥Û≈∆¥Ûµƒ≈∆æÕ––
		//	if(_biglist[0].data<_xxlist[i].data)
		//	{
		//		if(_retlist.size()<size)
		//		{
		//			m_cItem.data.push_back(_xxlist[i].data);
		//			_retlist.push_back(_xxlist[i]);
		//		}
		//		
		//	}
		//}
		//¥Û≤ª∆
		if(_retlist.size()==0)
		{
			for(int i=0;i<size;i++)
			{
				m_cItem.data.push_back(_xxlist[i].data);//ª·≥¨≥ˆ∑∂Œß£¨ ˝◊È‘ΩΩÁ£¨≤ªø…ƒ‹≥ˆœ÷∞°
				_retlist.push_back(_xxlist[i]);
			}
		}
		//º”∂œ—‘µ˜ ‘¥˙¬Î
		CCAssert(_retlist.size()==size,"_retlist size != size");
		_xxlist.clear();
		//return _retlist;
		//std::vector<DeleteItem> _dellist;
		_dellist.push_back(m_cItem);
		deletePoke(_dellist);
		//∂‘◊”µƒ¥¶¿Ì£¨√ªΩ¯––
		return dealPoke(_retlist);
	}
	return false;
}
inline bool NewRobot::checkCompare(PokeData& a,PokeData& b)
{
	int a_type=pokeType(a);
	int b_type=pokeType(b);
	
	if(a_type==b_type)
	{
		return a.data<b.data?1:0;
	}
	return false;
}
bool NewRobot::checkAiA(int id)
{
	//ai
	return false;
}
bool NewRobot::checkAiB(int id)
{
	//ai
	return false;
}
//’‚∏ˆ «∏…¬Ô£ø
bool NewRobot::checkKingBigPoke(int id)
{
	clearxxlist();
	if(firsttype==bank)
	{
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==size&&(*it).type==4)
			{
				//_xxlist.clear();//’‚¿Ô“ª∂®Œ™ø’
				_xxlist=(*it)._list;
				break;
			}
		}
		if(_xxlist.size()>0)
		{
			DeleteItem m_cItem;
			m_cItem.size=(int)size;
			m_cItem.type=4;

			_retlist.clear();
			for(int i=0;i<size;i++)
			{
				_retlist.push_back(_xxlist[i]);
				m_cItem.data.push_back(_xxlist[i].data);
			}
			//º”∂œ—‘µ˜ ‘¥˙¬Î
			CCAssert(_retlist.size()==size,"_retlist size > size");
			_xxlist.clear();

			//std::vector<DeleteItem> _dellist;
			_dellist.push_back(m_cItem);
			deletePoke(_dellist);
			//return _retlist;
			return dealPoke(_retlist);
		}
		//big poke >>it must compare with big Poke.
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==size&&(*it).type==bank)
			{
				//_xxlist.clear();//’‚¿Ô“ª∂®Œ™ø’
				_xxlist=(*it)._list;
				break;
			}
		}
		if(_xxlist.size()>0)
		{
			DeleteItem m_cItem;
			m_cItem.size=(int)size;
			m_cItem.type=bank;

			_retlist.clear();
			for(int i=0;i<size;i++)
			{
				_retlist.push_back(_xxlist[i]);
				m_cItem.data.push_back(_xxlist[i].data);
			}
			//º”∂œ—‘µ˜ ‘¥˙¬Î
			CCAssert(_retlist.size()==size,"_retlist size > size");
			_xxlist.clear();

			//std::vector<DeleteItem> _dellist;
			_dellist.push_back(m_cItem);
			deletePoke(_dellist);

			//return _retlist;
			return dealPoke(_retlist);
		}
	}
	//>>it must compare with big poke.
	if(firsttype==4)
	{
		int  m_type=0;
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).size==size&&(*it).type==4)
			{
				//_xxlist.clear();//’‚¿Ô“ª∂®Œ™ø’
				_xxlist=(*it)._list;
				break;
			}
		}
		if (_xxlist.size()==0)
		{
			for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
			{
				if((*it).size==size&&(*it).type==bank)
				{
					//_xxlist.clear();//’‚¿Ô“ª∂®Œ™ø’
					_xxlist=(*it)._list;
					m_type=bank;
					break;
				}
			}
		}
		else
			m_type=4;
		//
		if(_xxlist.size()>0)
		{
			
			DeleteItem m_cItem;
			m_cItem.size=(int)size;
			m_cItem.type=m_type;
			_retlist.clear();
			for(int i=0;i<size;i++)
			{
				if(_biglist[0].data<_xxlist[i].data)
				{
					_retlist.push_back(_xxlist[i]);
					m_cItem.data.push_back(_xxlist[i].data);

				}
			}
			//¥Û≤ª∆
			if(_retlist.size()==0)
			{
				for(int i=0;i<size;i++)
				{
					_retlist.push_back(_xxlist[i]);
					m_cItem.data.push_back(_xxlist[i].data);
				}
			}
			//º”∂œ—‘µ˜ ‘¥˙¬Î
			CCAssert(_retlist.size()==size,"_retlist size > size");
			_xxlist.clear();

			//std::vector<DeleteItem> _dellist;
			_dellist.push_back(m_cItem);
			deletePoke(_dellist);

			//return _retlist;
			return dealPoke(_retlist);
		}
	}
	return false;
}
//…æ≥˝≤Ÿ◊˜±»Ωœ¬È∑≥
//len ”–Œ Ã‚ ,µ±«∞≈∆ø…ƒ‹ªπ”–£¨µ´ «≤ªπª≈∆ ˝£¨π˝¬ÀµÙ’‚÷÷«Èøˆ£¨±‹√‚µ•≈∆±‰∂‘◊”

//ª·≤∑÷÷˜≈∆µƒ∂‘◊”
bool NewRobot::checkOtherSinglePoke(int id)
{
	clearxxlist();
	log("size = 1<size= %d>",(int)size);
	//”–Œ Ã‚ œ˚∑÷¥¶¿Ì≤ª∫√

	if(filterPkCount())//π˝¬À¿‡–Õ”–∞¸∫¨∑÷µƒ≈∆
	{
		return true;
		
	}
	log("function()>>>>checkOtherSinglePoke");
	randlist.clear();

	//type = 0 -> 4
	DeleteItem _item;
	//ÀÊª˙“Ú◊”≥ı ºªØ
	int i_random=randomInt();
	//randlist.push_back(i_random);
	int cnt=4;
	//if(bank==4)//bug Ã¯≤ª≥ˆµ›πÈ
	//	cnt+=1;
	log("rand end");
	while(randlist.size()<cnt)
	{
		log("rand size = %d",(int)randlist.size());
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			//ÃÌº”ÀÊª˙–‘ ¬º˛£¨»√¥¶¿Ì∏¸◊‘»ª“ªµ„	
			if((*it).size==1&&(*it).type!=firsttype&&(*it).type==i_random)//π˝¬À≈∆≤ª◊„µƒŒ Ã‚£¨µ´ «µ±«∞≈∆ªπ”–
			{
				//_xxlist.clear();
				_xxlist=(*it)._list;
				//std::vector<DeleteItem>_eraselist;
				//µ•≈∆
				//µΩ’‚¿Ô“ª∂®”–µƒ
				_item.size=1;
				_item.type=pokeType(_xxlist[0]);

				for(int i=0;i<_xxlist.size();i++)
				{
					if(size==6)//Ω´π˝¬À÷ª”√‘⁄6∏ˆ≈∆µƒ¥¶¿Ì÷–
						if(_xxlist[i].data==4||_xxlist[i].data==12)//”–∏ˆbug£¨◊Ó∫Û∑÷≈∆ª·π˝¬ÀµÙ£¨µº÷¬ª·¡Ù≈∆≥ˆ≤ª¡À
							continue;//’‚¿Ô≤ª¥¶¿Ì∑÷≈∆µƒº”»Î£¨√‚µ√÷ÿ∏¥¡À
					_retlist.push_back(_xxlist[i]);
					_item.data.push_back(_xxlist[i].data);
					if(_retlist.size()==size)
					{
						_dellist.push_back(_item);
						deletePoke(_dellist);
						return dealPoke(_retlist);
					}
					if(i+1==_xxlist.size())//???
					{
						_dellist.push_back(_item);
						_item.data.clear();//Ω´ ˝æ›«Âø’£¨œ¬“ª∏ˆ‘Ÿ”√
					}
					
				}
				//break;
			}
		}
		log("random poke = %d",i_random);
		i_random=randomInt();
	};
	log("random poking after");
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==1&&(*it).type!=firsttype)
		{
			//_xxlist.clear();
			_xxlist=(*it)._list;
			//std::vector<DeleteItem>_eraselist;
			//µ•≈∆
			//µΩ’‚¿Ô“ª∂®”–µƒ
			_item.size=1;
			_item.type=pokeType(_xxlist[0]);

			for(int i=0;i<_xxlist.size();i++)
			{
				if(size==6)//Ω´π˝¬À÷ª”√‘⁄6∏ˆ≈∆µƒ¥¶¿Ì÷–
					if(_xxlist[i].data==4||_xxlist[i].data==12)//”–∏ˆbug£¨◊Ó∫Û∑÷≈∆ª·π˝¬ÀµÙ£¨µº÷¬ª·¡Ù≈∆≥ˆ≤ª¡À
						continue;//’‚¿Ô≤ª¥¶¿Ì∑÷≈∆µƒº”»Î£¨√‚µ√÷ÿ∏¥¡À
				_retlist.push_back(_xxlist[i]);
				_item.data.push_back(_xxlist[i].data);
				if(_retlist.size()==size)
				{
					_dellist.push_back(_item);
					deletePoke(_dellist);
					return dealPoke(_retlist);
				}
				if(i+1==_xxlist.size())
				{
					_dellist.push_back(_item);
					_item.data.clear();//Ω´ ˝æ›«Âø’£¨œ¬“ª∏ˆ‘Ÿ”√
				}
			}
		}
	}
	log("size = 2 <del size =%lu>",_dellist.size());
	clearxxlist();
	//∂‘◊”
	//∆‰À¸≈∆–Õµƒdouble≈∆
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==2&&(*it).type!=firsttype)
		{
			_xxlist.clear();
			_xxlist=(*it)._list;
			//≤∑÷∂‘◊”
			_item.size=2;
			_item.type=pokeType(_xxlist[0]);//µΩ’‚¿Ô“ª∂®”–µƒ

			for(int i=0;i<_xxlist.size();i++)
			{
				//÷ÿ–¬…Ë÷√
				
				_retlist.push_back(_xxlist[i]);
				_item.data.push_back(_xxlist[i].data);

				if(_retlist.size()==size)
				{
					_dellist.push_back(_item);
					deletePoke(_dellist);
					//return _retlist;
					return dealPoke(_retlist);
				}
				if(_retlist.size()==_xxlist.size())
				{
					_dellist.push_back(_item);
				}
			}
			//break;
		}
	}
	
	clearxxlist();
	log("size = 4 <del size =%lu>",_dellist.size());
	//four ≈∆µƒ≤∑÷
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==4&&(*it).type!=firsttype)
		{
			_xxlist.clear();
			_xxlist=(*it)._list;
			//
			_item.size=4;
			_item.type=pokeType(_xxlist[0]);//µΩ’‚¿Ô“ª∂®”–µƒ

			for(int i=0;i<_xxlist.size();i++)
			{
				_retlist.push_back(_xxlist[i]);
				_item.data.push_back(_xxlist[i].data);

				if(_retlist.size()==size)
				{
					//return _retlist;
					_dellist.push_back(_item);
					deletePoke(_dellist);
					return dealPoke(_retlist);
				}
				if(_retlist.size()==_xxlist.size())
				{
					_dellist.push_back(_item);
				}
			}
			//break;
		}
	}	
	log("size = 6 <del size =%lu>",_dellist.size());
	//six ≈∆µƒ≤∑÷
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).size==4&&(*it).type!=firsttype)
		{
			_xxlist.clear();
			_xxlist=(*it)._list;
			//
			_item.size=6;
			_item.type=pokeType(_xxlist[0]);//µΩ’‚¿Ô“ª∂®”–µƒ

			for(int i=0;i<_xxlist.size();i++)
			{
				_retlist.push_back(_xxlist[i]);
				_item.data.push_back(_xxlist[i].data);

				if(_retlist.size()==size)
				{
					//return _retlist;
					_dellist.push_back(_item);
					deletePoke(_dellist);
					return dealPoke(_retlist);
				}
				if(_retlist.size()==_xxlist.size())
				{
					_dellist.push_back(_item);
				}
			}
			//break;
		}
	}	
	log(">>>>>----<del size =%lu>",_dellist.size());
	log(">>>>>_retlist size = %lu",_retlist.size());
	return false;//≥ˆ◊Ó∫Ûµƒ≈∆¡À
}
//Àƒ∏ˆ≈∆ “ª∏ˆ∂‘◊”£¨º”¡Ω∏ˆ‘”≈∆£¨ªÚ’ﬂ∆‰À˚¿‡–Õµƒ≈∆£¨delete”–Œ Ã‚99 45
//”√¡–±Ì»•∆•≈‰
void NewRobot::deletePoke(std::vector<DeleteItem>_item)
{
	for(int i=0;i<_item.size();i++)
	{
		int m_iType=_item[i].type;
		int m_sSize=_item[i].size;
		
		std::vector<int> _data=_item[i].data;
		//log("delete size = %d",_data.size());
		int n=0;
		for(std::vector<PokeListItem>::iterator it_item=_listitem.begin();it_item!=_listitem.end();)
		{
			if((*it_item).size==m_sSize&&(*it_item).type==m_iType)
			{
				for(std::vector<PokeData>::iterator it=(*it_item)._list.begin();it!=(*it_item)._list.end();)
				{
					if(n<_data.size())
					{
						if((*it).data==_data[n])
						{
							it=(*it_item)._list.erase(it);//ø…“‘÷ÿ∏¥ºÏÀ˜£¨…æ≥˝
							log(">>>>>>>>>>delete id = %d",_data[n]);
							log(">>>>>>>>>>delete type = %d",m_iType);
							n++;
							if(m_sSize==2&&n==_data.size()&&(*it_item)._list.size()>=3)
							{
								log("delete it again!");
								if((*it_item)._list[0].data!=(*it_item)._list[1].data)
								{
									
									//Ω´µ⁄“ª∏ˆ‘™Àÿ£¨“∆≥˝size==2 µƒ¡–±Ì¿Ô√Ê
									std::vector<PokeData> _insert;
									PokeData _insertData;
									_insertData.type=(*it).type;
									_insertData.data=(*it).data;
									_insert.push_back(_insertData);
									PushItem(_insert,1,m_iType);
									//
									it=(*it_item)._list.erase(it);//‘⁄…æ≥˝“ª¥Œ

								}
							}
							//4
							if(m_sSize==4&&n==_data.size()&&(*it_item)._list.size()>=3)
							{

							}
						}
						else
							it++;
					}
					else
						break;
				}
			}
			if((*it_item)._list.size()==0)
			{
				//
				it_item=_listitem.erase(it_item);
				break;
			}
			else
			{
				it_item++;
			}
		}
		
	}
	_dellist.clear();
}
bool NewRobot::checkKingMainPoke(int id)
{
	int bigtype=3;
	//”–ÕÊº“…±÷˜£¨ø¥“™≤ª“™≥ˆ¥¶¿Ì
	if(firsttype!=bank&&bigtype==bank)
	{
		//≈–∂œÕ¨¿‡–Õ≈∆”–√ª”–£¨æÕ––¡À
		//µΩ’‚≤Ω£¨Õ¨¿‡–Õ≈∆£¨“ª∂®√ª”–¡À£¨œÎ…±£¨æÕ…± £¨≤ª“™øº¬«
		//≤ª¥¶¿ÌÃ¯π˝£¨ok
		clearxxlist();
	    //typeµƒdouble≈∆
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if((*it).type==type&&(*it).size==size)
			{
				//_xxlist.clear();
				_xxlist=(*it)._list;
				break;
			}

		}
		std::vector<int>_eralist;
		//≤∑÷∂‘◊”
		for(int i=0;i<_xxlist.size();i++)
		{
			_retlist.push_back(_xxlist[i]);
			_eralist.push_back(_xxlist[i].data);
			if(_retlist.size()==size)
			{

				deletePoke(_eralist,2,type);
				dealPoke(_retlist);
				return true;
			}
		}
	}
	//¥¶¿Ìœ˚≈∆£¨æÕ––
	if(type==bank||type==4)
	{
		//÷˜≈∆¥¶¿Ì¡˜≥Ã

	}
	return false;
}
//Õ¨¿‡–Õ≈∆
bool NewRobot::checkDoubleDoublePoke(int id)
{
	if(size==4)
	{
		//÷ª“™≥ˆ¿Ì’˝÷˜µƒæÕ––£¨«∞√Êªπ“™≈–∂œø…“‘¥Ú∆µƒ≈∆£¨¬È∑≥£¨nima
		if(firsttype==bank||firsttype==4)
		{
			//œ»¥¶¿ÌÀƒ∏ˆ≈∆£¨‘Ÿ¥¶¿Ì¡Ω∏ˆ≈≈£¨±»Ωœ∏¥‘”“ªµ„
			if(splitDoubleDoule(4,4))
				return true;
			
			//¥¶¿Ì’˝÷˜ ¡Ω∏ˆ≈∆µƒ¥¶¿Ì
			if(splitDouble(4,4))
				return true;
		}
		//_retlist size==0 ±ÿ–Î «µƒ
		//œ»   ≈–∂œ∂‘◊”
		if(splitDouble(4,type))
			return true;
		//∫Û  ≈–∂œµ•≈∆
		if(splitSingle(4,type))
			return true;
		if(firsttype==bank||firsttype==4)
		{
			//µ±bank ≈∆√ª”–¡À ±∫Ú£¨‘⁄øº¬«’˝÷˜µƒµ•≈∆
			//¥¶¿Ìµ•≈∆
			if(splitSingle(4,4))
				return true;
		}
	}
	log("funtction>>checkDoubleDoublePoke <<_ret size >%lu<",_retlist.size());
	return false;
}
bool NewRobot::checkSixPoke(int id)
{
	if(size==6)
	{
		//÷ª“™≥ˆ¿Ì’˝÷˜µƒæÕ––£¨«∞√Êªπ“™≈–∂œø…“‘¥Ú∆µƒ≈∆£¨¬È∑≥£¨nima
		if(firsttype==bank||firsttype==6)
		{
			//¥¶¿Ì¡˘∏ˆ≈∆
			if (splitSix(4,6))
				return true;
			//œ»¥¶¿ÌÀƒ∏ˆ≈∆£¨‘Ÿ¥¶¿Ì¡Ω∏ˆ≈≈£¨±»Ωœ∏¥‘”“ªµ„
			if(splitDoubleDoule(6,4))
				return true;
			
			//¥¶¿Ì’˝÷˜ ¡Ω∏ˆ≈∆µƒ¥¶¿Ì
			if(splitDouble(6,4))
				return true;
		}
		//_retlist size==0 ±ÿ–Î «µƒ
		if (splitSix(type,6))
			return true;
		//œ»   ≈–∂œ∂‘◊”
		if(splitDouble(6,type))
			return true;
		//∫Û  ≈–∂œµ•≈∆
		if(splitSingle(6,type))
			return true;
		if(firsttype==bank||firsttype==6)
		{
			//µ±bank ≈∆√ª”–¡À ±∫Ú£¨‘⁄øº¬«’˝÷˜µƒµ•≈∆
			//¥¶¿Ìµ•≈∆
			if(splitSingle(6,4))
				return true;
		}
	}
	log("funtction>>checkSixPoke <<_ret size >%lu<",_retlist.size());
	return false;
}
bool NewRobot::checkDoublePoke(int id)
{
	if(size==2)
	{
		//¥¶¿Ì’˝÷˜µƒ∂‘◊”
		if(firsttype==bank||firsttype==4)
		{
			//¥¶¿Ìœ˚≈∆
			if(splitSingle(2,bank))
				return true;
			if(splitSingle(2,4))
				return true;
			if(splitDoubleDoule(2,bank))//≤∑÷Àƒ∏ˆ≈∆£¨≥ˆ∏ˆ∂‘◊”
				return true;
			if(splitDoubleDoule(2,4))
				return true;
			//√ª÷˜≈∆¡À£¨∏˙œ¬»•œ¬»•
			log("funtction>>checkDoublePoke  <king poke><<_ret size >%lu<",_retlist.size());
			return false;
		}

		//_retlist size==0 ±ÿ–Î «µƒ
		//∂‘◊”√ª”–≥ˆµ•≈∆
		if(splitSingle(2,type))
			return true;
		//∂‘◊”“ªø™ ºæÕøº¬«¡À
		//_retlist size ≤ª“ª∂®Œ™0£¨ø…Œ™ 1
		//∂‘◊”√ª”–≥ˆµ•≈∆,Õ¨¿‡–Õµƒµ•≈∆“≤√ª”–£¨≤ -> ≥ˆ¥Û”⁄2 µƒ≈∆,4 ∏ˆ≈∆ ≤
		if(splitDoubleDoule(2,type))
			return true;
		
		//µΩ¥ÀÕ¨¿‡–Õ≈∆“ªøº¬«ÕÍ£¨_retlist size ≤ª“ª∂®Œ™0
		//≤ªÕ¨¿‡–Õ≈∆ø…“‘Õ≥“ª¥¶¿Ì
	}
	log("funtction>>checkDoublePoke <<_ret size >%lu<",_retlist.size());
	return false;
}
//¥¶¿Ì…æ≈∆£¨‘ı√¥¥¶¿Ì
//0 1 2 3 4 5(‘”≈∆)
bool NewRobot::dealPoke(std::vector<PokeData> _poke)
{
	LocalGameServer::getInstance()->getClientPokeData(id,_poke);
	if(_xxlist.size())
		_xxlist.clear();
	return true;
}
void NewRobot::pokeExtraPkFilter(std::vector<PokeData> &datalist)
{
}
int NewRobot::getPokeData()
{
	int iCount=0;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		iCount+=(*it)._list.size();
	}
	return iCount;
}
//size == 2 ”–ø’¡–±Ì£ø£ø
void NewRobot::pokeFilerPool(std::vector<PokeData> &datalist)
{
	//init 
	srand((unsigned int)CurrTime());//…Ë÷√ÀÊª˙ ˝“Ú◊”
	bank=UserInfo::getInstance()->getType();
	//bank=3;//≥ˆ¿Ì≈∆ ±æÕ±ÿ–Î≥ı ºªØ
	std::vector<PokeData>_data[5];//0 1 2 3 4 5
	
	for(std::vector<PokeData>::iterator it =datalist.begin();it!=datalist.end();it++)
	{
		if(pokeKingPoke((*it)))
		{
			_data[5-1].push_back((*it));
		}
		else
		{
			_data[(*it).type].push_back((*it));
		}
			
	}
	datalist.clear();
	
	for(int i=0;i<5;i++)
	{
		if(_data[i].size()>0)
			pokeFilerDoublePoke(_data[i],i);
	}
}
void NewRobot::PushItem(std::vector<PokeData>& datalist,int size,int type)
{
	/*if(size==2)
	{
		log("double");
	}*/
	PokeListItem item;
	item.size=size;
	item.type=type;
	item._list=datalist;
	_listitem.push_back(item);
}
//√ª”√
void NewRobot::splitRobotData(const int type,PokeData& data)
{
	
}

void NewRobot::pokeFilerDoublePoke(std::vector<PokeData>& datalist,int tag)//tag =4 ’˝÷˜
{
	
	//∂‘≈∆≈≈–Ú
	std::sort(datalist.begin(),datalist.end(),NewRobot());

	std::vector<PokeData>_datalist;
	std::vector<PokeData> _eraselist;
	for(int i=0;i<datalist.size()-1;i++)
	{
		// 0 1 2 3 4
		if(tag==4)
		{
			//’˝÷˜≤ª «∞¥¿‡–Õ∑÷¿‡£¨“™øº¬«type
			//≤È∂‘◊”
			if(datalist[i].data==datalist[i+1].data&&datalist[i].type==datalist[i+1].type)
			{
				_datalist.push_back(datalist[i]);
				_datalist.push_back(datalist[i+1]);
				_eraselist.push_back(datalist[i]);
				_eraselist.push_back(datalist[i+1]);
			}
		}
		else
		{
			//≤È∂‘◊”
			if(datalist[i].data==datalist[i+1].data)
			{
				_datalist.push_back(datalist[i]);
				_datalist.push_back(datalist[i+1]);
				_eraselist.push_back(datalist[i]);
				_eraselist.push_back(datalist[i+1]);
			}
		}
	}
	//’˝÷˜“∆≥˝µƒ ±∫Ú“™º”¿‡–Õ≈–∂œ
	if(_eraselist.size()>0)
	{
		int k=0;
		for(std::vector<PokeData>::iterator it =datalist.begin();it!=datalist.end();)
		{
			if(k<_eraselist.size())
			{
				//int m_iData=(*it).data;
				//log("data = %d   e ==%d k  == %d",m_iData,_eraselist[k],k);
				if((*it).data==_eraselist[k].data&&(*it).type==_eraselist[k].type)
				{
					it=datalist.erase(it);
					k++;
				}
				else
					it++;
				
			}
			else
				break;
			
		}
		//4∏ˆ≈∆π˝¬À
		_eraselist.clear();
		if(_datalist.size()==4)
		{
			if(tag==4)
				pokeFilterKingPoke(_datalist,4);//4 ∏ˆ≈∆µƒ’˝÷˜≤≈“™«¯±≈–∂œ
			else
				pokeFilterDoubleDoublePoke(_datalist,tag);
		}
		else if (_datalist.size()==6)
			if (tag==4)
				pokeFilterSixKingPoke(_datalist,4);
			else
				pokeFilterSixPoke(_datalist,tag);
		else
			PushItem(_datalist,2,tag);
	}
	PushItem(datalist,1,tag);
	//_listA[1]=datalist;
}
void NewRobot::pokeFilterDoubleDoublePoke(std::vector<PokeData>& datalist,int tag)
{
	//
	std::vector<PokeData> _data;//four poke
	std::vector<int> _eraselist;
	for(int i=0;i<datalist.size()-3;i++)
	{
		if(datalist[i].data==datalist[i+3].data-1)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);

			_eraselist.push_back(datalist[i].data);
			_eraselist.push_back(datalist[i+1].data);
			_eraselist.push_back(datalist[i+2].data);
			_eraselist.push_back(datalist[i+3].data);
		}
		//99 jj
		else if(datalist[i].data==8&&datalist[i+3].data==10)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);

			_eraselist.push_back(8);
			_eraselist.push_back(8);
			_eraselist.push_back(10);
			_eraselist.push_back(10);
		}
	}
	if(_eraselist.size()>0)
	{
		int k=0;
		for(std::vector<PokeData>::iterator it=datalist.begin();it!=datalist.end();)
		{
			if(k<_eraselist.size())
			{
				//int m_iData=(*it).data;
				//log("data = %d   e ==%d k  == %d",m_iData,_eraselist[k],k);
				if((*it).data==_eraselist[k])
				{
					it=datalist.erase(it);
					k++;
				}
				else
					it++;
			}
			else
				break;
		}
		_eraselist.clear();
		PushItem(_data,4,tag);//”–≤≈±£¥Ê
		
	}
	PushItem(datalist,2,tag);
	//_listA[2]=datalist;
	//_listA[4]=_data;
}
void NewRobot::pokeFilterSixPoke(std::vector<PokeData>&datalist,int tag)
{
	//
	std::vector<PokeData> _data;//six poke
	std::vector<int> _eraselist;
	for(int i=0;i<datalist.size()-5;i++)
	{
		//33 44 55
		if(datalist[i].data==datalist[i+3].data-1&&datalist[i+3].data==datalist[i+5].data-1)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);
			_data.push_back(datalist[i+4]);
			_data.push_back(datalist[i+5]);

			_eraselist.push_back(datalist[i].data);
			_eraselist.push_back(datalist[i+1].data);
			_eraselist.push_back(datalist[i+2].data);
			_eraselist.push_back(datalist[i+3].data);
			_eraselist.push_back(datalist[i+4].data);
			_eraselist.push_back(datalist[i+5].data);
		}
		//99 jj qq
		else if(datalist[i].data==8&&datalist[i+3].data==10&&datalist[i+5].data==11)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);

			_eraselist.push_back(8);
			_eraselist.push_back(8);
			_eraselist.push_back(10);
			_eraselist.push_back(10);
			_eraselist.push_back(11);
			_eraselist.push_back(11);
		}
		//88 99 jj
		else if(datalist[i].data==7&&datalist[i+3].data==8&&datalist[i+5].data==10)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);
			_data.push_back(datalist[i+4]);
			_data.push_back(datalist[i+5]);

			_eraselist.push_back(7);
			_eraselist.push_back(7);
			_eraselist.push_back(8);
			_eraselist.push_back(8);
			_eraselist.push_back(10);
			_eraselist.push_back(10);
		}
	}
	if(_eraselist.size()>0)
	{
		int k=0;
		for(std::vector<PokeData>::iterator it=datalist.begin();it!=datalist.end();)
		{
			if(k<_eraselist.size())
			{
				//int m_iData=(*it).data;
				//log("data = %d   e ==%d k  == %d",m_iData,_eraselist[k],k);
				if((*it).data==_eraselist[k])
				{
					it=datalist.erase(it);
					k++;
				}
				else
					it++;
			}
			else
				break;
		}
		_eraselist.clear();
		PushItem(_data,6,tag);//”–≤≈±£¥Ê
	}
	//Œﬁ∑®πª≥…¡˘∏ˆ≈∆µƒ∂‘◊”£¨Ωª∏¯Àƒ∏ˆ≈∆∂‘◊”µƒ∫Ø ˝»•¥¶¿Ì

	if (datalist.size()==4)
		pokeFilterDoubleDoublePoke(datalist,tag);
	else 
		PushItem(datalist,2,tag);
	
}
void NewRobot::pokeFilterSixKingPoke(std::vector<PokeData>&datalist,int tag)
{
	std::vector<PokeData> _data;//four poke
	std::vector<PokeData> _eraselist;
	for(int i=0;i<datalist.size()-5;i++)
	{
		//22 22 22 aa aa aa
		// ÷˜≈∆∂®¡À£¨≤≈∑÷∂—
		if(datalist[i].data==datalist[i+3].data==datalist[i+5].data&&(datalist[i].type==bank||datalist[i+3].type==bank||datalist[i+5].type==bank))//bankªπ√ª≥ı ºªØ
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);
			_data.push_back(datalist[i+4]);
			_data.push_back(datalist[i+5]);

			_eraselist.push_back(datalist[i]);
			_eraselist.push_back(datalist[i+1]);
			_eraselist.push_back(datalist[i+2]);
			_eraselist.push_back(datalist[i+3]);
			_eraselist.push_back(datalist[i+4]);
			_eraselist.push_back(datalist[i+5]);
		}
	}
	if(_eraselist.size()>0)
	{
		int k=0;
		for(std::vector<PokeData>::iterator it=datalist.begin();it!=datalist.end();)
		{
			if(k<_eraselist.size())
			{
				if((*it).data==_eraselist[k].data&&(*it).type==_eraselist[k].type)
				{
					it=datalist.erase(it);
					k++;
				}
				else
				{
					it++;
				}
			}
			else
				break;
		}
		_eraselist.clear();
		PushItem(_data,6,tag);//”–≤≈±£¥Ê
	}
	//÷ÿ–¬Ωª∏¯Àƒ∏ˆ≈∆∫Ø ˝¥¶¿Ì
	if(datalist.size()==4)
		pokeFilterKingPoke(datalist,4);
	else
		PushItem(datalist,2,tag);
}

//¥¶¿ÌÀƒ∏ˆ≈∆   ”–bug
void NewRobot::pokeFilterKingPoke(std::vector<PokeData>& datalist,int tag)
{
	
	std::vector<PokeData> _data;//four poke
	std::vector<PokeData> _eraselist;
	for(int i=0;i<datalist.size()-3;i++)
	{
		//2222 aaaa
		// ÷˜≈∆∂®¡À£¨≤≈∑÷∂—
		if(datalist[i].data==datalist[i+3].data&&(datalist[i].type==bank||datalist[i+3].type==bank))//bankªπ√ª≥ı ºªØ
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);
			_eraselist.push_back(datalist[i]);
			_eraselist.push_back(datalist[i+1]);
			_eraselist.push_back(datalist[i+2]);
			_eraselist.push_back(datalist[i+3]);
		}
		// jj  JJ
		else if(datalist[i].data==14&&datalist[i+3].data==15)
		{
			_data.push_back(datalist[i]);
			_data.push_back(datalist[i+1]);
			_data.push_back(datalist[i+2]);
			_data.push_back(datalist[i+3]);
			_eraselist.push_back(datalist[i]);
			_eraselist.push_back(datalist[i+1]);
			_eraselist.push_back(datalist[i+2]);
			_eraselist.push_back(datalist[i+3]);
		}
	}
	if(_eraselist.size()>0)
	{
		int k=0;
		for(std::vector<PokeData>::iterator it=datalist.begin();it!=datalist.end();)
		{
			if(k<_eraselist.size())
			{
				if((*it).data==_eraselist[k].data&&(*it).type==_eraselist[k].type)
				{
					it=datalist.erase(it);
					k++;
				}
				else
				{
					it++;
				}
			}
			else
				break;
		}
		_eraselist.clear();
		PushItem(_data,4,tag);//”–≤≈±£¥Ê
	}
	PushItem(datalist,2,tag);
}
//’‚¿Ô…æ≥˝¡À£¨∆‰À˚µÿ∑ΩæÕ≤ª“™…æ≥˝¡À£¨∑≈‘⁄…æ≥˝µƒµÿ∑ΩÕ≥“ªÀ¢–¬£¨∫√œÒ∫√“ªµ„
//“™∏˙…æ≥˝∑Ω∑®Õ≥“ª∫√£¨“™≤ªª·≥ˆœ÷£¨…æ≥˝¡–±Ì∂‘≤ª…œ£¨≥ˆœ÷Œ Ã‚£¨»´≤ø…æ≥˝≤ª¡À
//“ª¥Œ¿Ô√Êªπ÷ª÷ß≥÷“ª¥Œ£¨ªπ”–≈–∂œ∂‘◊” «≤ª «»´≤ø…æ¡À£¨æÕ≤ª“™¥¶¿Ì’‚±ﬂ¬ﬂº≠¡À
//ª∞Àµ4 ∏ˆ≈∆µƒ¡À£¨≤∑÷¡À£¨“™–≠µ˜∫√≤≈––
void NewRobot::FreshFilterPoke(std::vector<PokeData>&datalist,int size,int type,int data,int count)
{
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).type==type&&(*it).size==size)
		{
			//_xxlist.clear();
			std::vector<PokeData> del_list=(*it)._list;
			//∂‘◊”’‚—˘ø…“‘£¨µ´ «4∏ˆ≈∆µƒ£¨“™µ•∂¿¥¶¿Ì
			for(std::vector<PokeData>::iterator v=del_list.begin();v!=del_list.end();)
			{
				bool isDel=false;
				if(count==2)
					isDel=false;//…æ≥˝¡Ω¥Œ£¨∂‘”⁄4∏ˆ≈∆’‚÷÷¿‡–Õµƒ≈∆£¨6∏ˆ≈∆£¨π˛π˛π˛¡À
				if((*v).data==data&&!isDel)//±æ…Ì÷ª…æ≥˝“ª¥Œ
				{
					v=del_list.erase(v);
					std::vector<PokeData>_newitem;
					PokeData _data;
					_data.type=type;
					_data.data=data;
					_newitem.push_back(_data);
					PushItem(_newitem,1,type);
					isDel=true;
					if (size==2)
						return;
				}
				else
					v++;
				switch (size)
				{
				case 4://≤ªª·”– 44 55 66
					{
						//Àƒ∏ˆ≈∆∑÷44 55 »Áπ˚ «“∆≥˝4 ’‚—˘ «√ªŒ Ã‚µƒ£¨»Áπ˚ «5 ¡À£¨ƒ·¬ÍÕ¥ø‡ 
						//????????????
						//+1 µƒ»´≤ø“™…æ≥˝,º”“ªªÚºı“ª≤ªª·Õ¨ ±¥Ê‘⁄
						if((*v).data==data+1)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
						if((*v).data==data-1)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
					}
					break;
				case 6://π¿º∆≤ªª·¥¶¿Ì
					{

						if((*v).data==data+1)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
						if((*v).data==data-1)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
						if((*v).data==data+2)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
						if((*v).data==data-2)
						{
							v=del_list.erase(v);
							std::vector<PokeData>_newitem;
							PokeData _data;
							_data.type=type;
							_data.data=data;
							_newitem.push_back(_data);
							PushItem(_newitem,1,type);
						}
						else
							v++;
					}
					break;
				default:
					break;
				}
					
				break;
			}
			break;
		}

	}
}
unsigned int NewRobot::sequence(PokeData data)
{
	int value=0;
	value+=data.data*100;
	return value;
}
inline bool NewRobot::pokeKingPoke(PokeData& data)
{
	if(data.data==1) {return true;}
	else if(data.data==9) {return true;}
	else if(data.data>=14) {return true;}
	return false;
}
inline int NewRobot::pokeType(PokeData& _data)
{
	if(_data.data==1) {return 4;}
	else if(_data.data==9) {return 4;}
	else if(_data.data>=14) {return 4;}

	//
	return _data.type;
}
bool NewRobot::splitDouble(int len,int type)
{
	log("funtction>>splitDouble len = %d type = %d",len,type);
	//
	clearxxlist();
	//typeµƒdouble≈∆
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).type==type&&(*it).size==2)
		{
			//_xxlist.clear();
			_xxlist=(*it)._list;
			break;
		}

	}
	DeleteItem _item;
	//std::vector<DeleteItem>_eraselist;
	//≤∑÷∂‘◊”
	int _retlen=(int)_retlist.size();
	for(int i=0;i<_xxlist.size();i++)
	{
		_retlist.push_back(_xxlist[i]);
		_item.size=2;
		_item.type=pokeType(_xxlist[i]);

		_item.data.push_back(_xxlist[i].data);

		if(_retlist.size()==len)
		{
			_dellist.push_back(_item);
			deletePoke(_dellist);
			dealPoke(_retlist);
			return true;
		}
		if((_retlist.size()-_retlen)==_xxlist.size())
		{
			_dellist.push_back(_item);//º”»Î…æ≥˝¡–±Ì
		}
	}
	log("funtction>>splitDouble <<_ret size >%lu<",_retlist.size());
	return false;
}
inline void NewRobot::clearxxlist()
{
	if(_xxlist.size()>0)
		_xxlist.clear();
}
bool NewRobot::filterPkLarge(int size,int type,int len,std::vector<PokeData> _list)
{
	//¥Û–°±»Ωœ,∞¥µ¿¿Ì≈≈–Ú¡À£¨µ⁄“ª∏ˆ”¶∏√ «◊Ó–°µƒ
	for(int i=0;i<_list.size();i++)
	{

	}
	return false;
}
//µ±Õ¨¿‡–Õµƒ≈∆÷ª”–kªÚ’ﬂ5  ±£¨”–ÕÊº“≥ˆ¡À’‚√≈µƒ∂‘◊”£¨æÕª·÷ÿ∏¥º”‘ÿ£¨”¶Œ™—°‘Ò÷Æ∫Û≈∆√ª≥…¡–±Ì¿Ô√Ê…æ≥˝
bool NewRobot::filterPkCount(int fsize,int ftype,int flen,int* tag)
{
	log("funtction>>filterCount size = %d type = %d len = %d",fsize,ftype,flen);
	//	1
	//0		2
	//	3
	//∂‘º“¥Û≈∆≤≈≥ˆ∑÷£¨£®√ªøº¬«Ω”œ¬¿¥µƒΩ·π˚£¨◊Ó÷’≤ª“ª∂® «◊Ó¥Ûµƒ£©£¨øº¬«º”∏ˆÀÊª˙≈–∂®
	log("big = %d id = %d",bigPokeId,id);
	if(bigPokeId==0||bigPokeId==2)
	{
		if(id==0||id==2)
		{
			return false;
		}
	}
	else if(bigPokeId==3||bigPokeId==1)
	{
		if(id==0||id==2)
		{
			return false;
		}
	}
	log("filterPkCount::start()");
	clearxxlist();//º”∏ˆ ˝æ›ø™πÿ£¨µΩƒ«≤ª≤ΩæÕ«Âø’
	//∑÷¿‡¥¶¿Ì”≈ªØÀ„∑®
	if(fsize==-1&&ftype==-1 )//≤ª∏¯∂®¿‡–Õ
	{ //¥¶¿Ìµ•≈∆µƒœ˚∑÷,√ªπÊ∂®¿‡–Õ∫Õ¥Û–°
		bool isHave = false;
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if ((*it).type!=firsttype)//Ω‚æˆ÷ÿ∏¥º”‘ÿµƒŒ Ã‚£¨function<checkOtherSinglePoke>µ˜”√
			{
				for(int i=0;i<(*it)._list.size();i++)
				{
					//’‚¿Ô÷ª¥¶¿Ì
					if(((*it)._list[i].data==4||(*it)._list[i].data==12)/*&&(*it).size==1*/)//≤ªø…“‘≤∑÷÷˜≈∆µƒ∂‘◊”£¨∂‘◊”÷ªø…“‘”…∂‘◊”¿¥≤∑÷
					{
						isHave=true;
						/*if(_retlist.size()==flen&&flen!=0)*///∑¿¥Ì
						
						//œ»≈–∂œ‘⁄≥ı ºªØ
						int m_size=(*it).size;
						int m_type=(*it).type;
						DeleteItem _item;
						_item.size=m_size;
						_item.type=m_type;
						_item.data.push_back((*it)._list[i].data);
						_retlist.push_back((*it)._list[i]);//º”»Î≥ˆ≈∆¡–±Ì
						_dellist.push_back(_item);//º”»Î…æ≥˝¡–±Ì
						//break;
						if(_retlist.size()==size)
						{
							deletePoke(_dellist);
							dealPoke(_retlist);
							return true;
						}
						
						return false;
					}
				}
			}
			
			if(isHave)
				break;
		}
		
	}
	//∏¯∂®¿‡–Õ
	else if(fsize==1)
	{
		for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
		{
			if(fsize==(*it).size&&(*it).type==ftype)//¥˙¬Î”–¥Ì
			{
				for(int i=0;i<(*it)._list.size();i++)
				{
					if((*it)._list[i].data==4||(*it)._list[i].data==12)
					{
						if((*it)._list.size()<flen)//Ω”œ¬¿¥µƒ¥¶¿Ì“ª∂®ª·∞¸∫¨5 ªÚ k ‘⁄¿Ô√Ê
						{
							*tag=2;
							return false;
							
						}
						else
						{
							*tag=1;
						}
						int m_size=fsize;//(*it).size;
						int m_type=ftype;//(*it).type;
						DeleteItem _item;
						_item.size=m_size;
						_item.type=m_type;
						_item.data.push_back((*it)._list[i].data);
						_retlist.push_back((*it)._list[i]);//º”»Î≥ˆ≈∆¡–±Ì
						_dellist.push_back(_item);//º”»Î…æ≥˝¡–±Ì
					
						if(_retlist.size()==flen&&flen!=0)//∑¿¥Ì
						{
							deletePoke(_dellist);
							dealPoke(_retlist);
							return true;
						}
						return false;
					}
				}
			}
			
		}
	}
	return false;
}
bool NewRobot::splitSingle(int len,int type)
{
	log("funtction>>splitSingle len = %d type = %d",len,type);
	clearxxlist();//º”∏ˆ ˝æ›ø™πÿ£¨µΩƒ«≤ª≤ΩæÕ«Âø’
	int tag=0;
	if (filterPkCount(1,type,len,&tag))//∫Ø ˝”–Œ Ã‚£¨µ±len > 1 ±£¨«“”–5 ªÚ k ±£¨ª·≥ˆœ÷÷ÿ∏¥º”‘ÿµƒ«Èøˆ
	{
		return true;
	}
	//typeµƒµ•≈∆
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).type==type&&(*it).size==1)
		{
			//_xxlist.clear();
			_xxlist=(*it)._list;
			break;
		}
	}
	//≥ˆµ•≈∆
	DeleteItem _item;
	//std::vector<DeleteItem>_eraselist;
	int _retlen=(int)_retlist.size();
	for(int i=0;i<_xxlist.size();i++)
	{
		if(_xxlist[i].data==4||_xxlist[i].data==12)
		{
			if(tag==1)//1 <
			{
				continue;
			}
			//continue;
		}
		_retlist.push_back(_xxlist[i]);
		
		_item.size=1;
		_item.type=pokeType(_xxlist[i]);
		_item.data.push_back(_xxlist[i].data);

		if(_retlist.size()==len)
		{
			_dellist.push_back(_item);
			deletePoke(_dellist);
			dealPoke(_retlist);
			return true;
		}
		if((_retlist.size()-_retlen)==_xxlist.size())
		{
			_dellist.push_back(_item);
		}
	}
	log("funtction>>splitSingle <<_ret size >%lu<",_retlist.size());
	return false;
}
void NewRobot::deletePoke(std::vector<int> _poke,int _size,int _type)
{
	//“¿¥Œ…æ≥˝£¨¿¡µ√∂‡¬«
	
	int n=0;
	int m_iType=_type;
	int m_sSize=_size;
	log("function>>deletePoke() type = %d size = %d",_type,_size);
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();)
	{
		if((*it).type==m_iType&&(*it).size==m_sSize)
		{
			/*std::vector<PokeData> _mList=(*it)._list;*/
			for(std::vector<PokeData>::iterator _item=(*it)._list.begin();_item!=(*it)._list.end();)
			{
				if(n<_poke.size())
				{
					if((*_item).data==_poke[n])
					{
						n++;
						_item=(*it)._list.erase(_item);//ø…“‘÷ÿ∏¥ºÏÀ˜£¨…æ≥˝
						
					}
					else
						_item++;
				}
				else
				{
					break;
				}
			}	
		}
		if((*it)._list.size()==0)
		{
			it=_listitem.erase(it);
			break;
		}
		else
			it++;
	}
}
bool NewRobot::splitDoubleDoule(int len,int type)
{
	//
	clearxxlist();
	//typeµƒ2 double≈∆
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).type==type&&(*it).size==4)
		{
			//_xxlist.clear();
			_xxlist=(*it)._list;
			break;
		}
	}
	//std::vector<DeleteItem>_eralist;
	DeleteItem _item;
	//≤∑÷4 ≈∆
	int _retlen=(int)_retlist.size();
	for(int i=0;i<_xxlist.size();i++)
	{
		_retlist.push_back(_xxlist[i]);

		_item.size=4;
		_item.type=pokeType(_xxlist[i]);
		_item.data.push_back(_xxlist[i].data);

		if(_retlist.size()==len)
		{
			//return _retlist;
			//return ;
			_dellist.push_back(_item);
			deletePoke(_dellist);
			dealPoke(_retlist);
			return true;
		}
		if((_retlist.size()-_retlen)==_xxlist.size())
		{
			_dellist.push_back(_item);
		}
	}
	log("funtction>>splitDoubleDoule <<_ret size >%lu<",_retlist.size());
	return false;
}
bool NewRobot::splitSix(int type,int len)
{
	//
	clearxxlist();
	//typeµƒ3 double≈∆
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if((*it).type==type&&(*it).size==6)
		{
			//_xxlist.clear();
			_xxlist=(*it)._list;
			break;
		}
	}
	//std::vector<DeleteItem>_eralist;
	DeleteItem _item;
	//≤∑÷6 ≈∆
	int _retlen=(int)_retlist.size();
	for(int i=0;i<_xxlist.size();i++)
	{
		_retlist.push_back(_xxlist[i]);

		_item.size=6;
		_item.type=pokeType(_xxlist[i]);
		_item.data.push_back(_xxlist[i].data);

		if(_retlist.size()==len)
		{
			//return _retlist;
			//return ;
			_dellist.push_back(_item);
			deletePoke(_dellist);
			dealPoke(_retlist);
			return true;
		}
		if((_retlist.size()-_retlen)==_xxlist.size())
		{
			_dellist.push_back(_item);
		}
	}
	log("funtction>>splitSix <<_ret size >%lu<",_retlist.size());
	return false;
}
void NewRobot::registerTypeCount(int count,int type)
{

}
void NewRobot::registerDataCount(int data,int count,int type,int size)
{

}
bool NewRobot::analysis()
{
	return false;
}
int NewRobot::randomInt(int max)
{
	int rand_key=rand()%max+0;
	if (randlist.size()==0)
	{
		randlist.push_back(rand_key);
	}
	else
	{
		while(checkHave(rand_key))
		{
			 rand_key=rand()%max+0;
		}
		randlist.push_back(rand_key);
	}
	return rand_key;
}
bool NewRobot::checkHave(int n)
{
	for(int i=0;i<randlist.size();i++)
	{
		if(randlist[i]==n)
			return true;
	}
	return false;
}

void NewRobot::getListData(std::vector<PokeData>&datalist)
{
	for(int i=0;i<4;i++)
		typeCntList[i]=0;
	pokeList=datalist;
}
//黑 红 梅 方 1 4 3 2
//方 黑 红 梅 0 1 2 3
static int  CmKingBig(int type,int data)
{
    int cm=0;
    switch(type)
    {
        case 0:
        {
            cm=type*100;
            
        }
            break;
        case 1:
        {
            cm=type*400;
        }
            break;
        case 2:
        {
            cm=type*300;
            
        }
            break;
        case 3:
        {
            cm=type*200;
        }
            break;
            
    }
    return cm;
    
}
int NewRobot::dealDataByIdx(int idx)
{
    //std::vector<donePoke> bankedDataList;

    if(UserInfo::getInstance()->getKingCount()==2)
    {
        return -1;//基主还不考虑，要不要判断基主的处理
    }
	PokeData data=pokeList[idx];
	//
	//∑Ω ∫⁄ ∫Ï √∑ 0 1 2 3 
	//2 º” 10 µƒƒ£ ΩΩ–÷˜£¨≤ª±ÿøº¬«¥Û–°
    
    donePoke done;
	if(data.data==9)
	{
		
		done.cnt=1;
		done.data=data.type;
		for(int i=0;i<bankedDataList.size();i++)
		{
			if(bankedDataList[i].data==data.type)
			{
				done.cnt=2;//“—æ≠¥Ê‘⁄¡À£¨æÕøº¬«∂‘◊”
				break;
			}
		}
        log("done data = %d",done.data);
		bankedDataList.push_back(done);
        log("list data = %d",bankedDataList[0].data);
    }
		

	switch(pokeType(data))
	{
		case 0:
			{
				typeCntList[0]+=1;
			}
			break;
		case 1:
			{
				typeCntList[1]+=1;
			}
			break;
		case 2:
			{
				typeCntList[2]+=1;
			}
			break;
		case 3:
			{
				typeCntList[3]+=1;
			}
			break;
		default:
			break;
	}
    int kingtype=UserInfo::getInstance()->getType();
    bool bSingle=false;
    if(kingtype!=-1&&done.cnt==2)
    {
        for(int i=0;i<bankedDataList.size();i++)
        {
            if(bankedDataList[i].data==kingtype&&bankedDataList[i].cnt==1)
            {
                
                bSingle=true;//当前主牌是单排
                
            }
        }
        if(bSingle)
        {
            UserInfo::getInstance()->setKingCount(2);
            return done.data;
            float delta=(float)typeCntList[done.data]/(pokeList.size()-idx);
            //log("delta data = %f robot size = %lu type = %lu typesize = %d",delta,pokeList.size()-idx,i,typeCntList[bankedDataList[i].data]);
            if(typeCntList[done.data]>5||delta>0.2)
                return done.data;
        }
        
        
    }
    //
    if(UserInfo::getInstance()->getType()!=-1)
        return -1;
	for(size_t i=0;i<bankedDataList.size();i++)
	{
        UserInfo::getInstance()->setKingCount(1);
        return done.data;
        log("data = %lu size = %lu",i,bankedDataList.size());
        log("data = %d",bankedDataList[0].data);
        float delta=(float)typeCntList[bankedDataList[i].data]/(pokeList.size()-idx);
		log("delta data = %f robot size = %lu type = %lu typesize = %d",delta,pokeList.size()-idx,i,typeCntList[bankedDataList[i].data]);
		if(typeCntList[bankedDataList[i].data]>5||delta>0.2)
			return bankedDataList[i].data;
	}
	return -1;

	//
}
//ø€µ◊≈∆πÊ‘Ú
//¥¶¿Ìµ•≈≈£¨ø€∑÷0 °´°´ 40∑÷÷Æº‰
//’‚√≈√ª÷˜µƒª∞£¨µ•≈≈–°”⁄8∏ˆ‘≠‘Ú…œø…“‘»´ø€£¨πÊ‘ÚΩœ∂‡£¨º”»ÎÀÊª˙–‘
//»˝√≈∂º√ª∂‘◊”µƒª∞øº¬«£¨ÀÊª˙–‘£¨”–∂‘◊”µƒ√≈£¨≤ªº”»ÎÀÊª˙—°‘Ò¿Ô√Ê
//À„ÕÍ∫Û∏±≈∆–°”⁄8∏ˆª∞£¨øº¬«ø€º∏∏ˆ÷˜µƒµ•≈≈£¨ª˘±æ√ª’‚√¥∫√µƒ≈∆¡À£¨¬˙◊„99.99%µƒ“™«Û
//A’‚—˘µƒ≈∆“™¡Ù◊≈£¨≤ªø…“‘≥ˆ

std::vector<PokeData> NewRobot::dealBankerPoke()
{
	//‘›∂®◊ÓºÚµ•µƒ∑Ω∞∏
	int eightCnt=0;
	std::vector<PokeData> m_datalist;
	for(std::vector<PokeListItem>::iterator it=_listitem.begin();it!=_listitem.end();it++)
	{
		if(((*it).type!=4&&(*it).type!=bank)&&(*it).size==1)
		{
			if((*it)._list.size()<8)
			{
				DeleteItem _item;
				_item.size=1;
				_item.type=(*it).type;
				for(int i=0;i<(*it)._list.size();i++)
				{
					eightCnt++;
					if(eightCnt<8)
					{
						_item.data.push_back((*it)._list[i].data);
						m_datalist.push_back((*it)._list[i]);
						if(i==(*it)._list.size()-1)
							_dellist.push_back(_item);
					}
					else if(eightCnt==8)
					{
						_item.data.push_back((*it)._list[i].data);
						m_datalist.push_back((*it)._list[i]);
						_dellist.push_back(_item);
					}
					else
						break;

				
				}
			}
		}
	}
	deletePoke(_dellist);
	return m_datalist;//∑µªÿ∏¯UserInfo±£¥Ê
}

