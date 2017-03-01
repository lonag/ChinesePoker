#include "../scene/GameScore.h"
#include "../scene/LocalplayScene.h"
#include "../extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
Scene* GameScore::scene()
{
	GameScore* layer=GameScore::create();
	auto m_scene=Scene::create();
	m_scene->addChild(layer,20);
	return m_scene;
}
bool GameScore::init()
{
	bool bRet=false;
	do 
	{
		if (!RootLayer::init())
		{
			return false;
		}
		bRet=true;
	} while (0);
	return bRet;
}
void GameScore::initiation()
{
	auto size=Director::getInstance()->getWinSize();
	

	Sprite* bg1=Sprite::create("res/images/resultDialog/result_bg.png");
	bg1->setPosition(size.width/2,size.height/2);
	//this->addChild(bg1);

	auto resultbg=Scale9Sprite::create("res/images/dialog/dialog_btn.png");
	resultbg->setPosition(size.width/2,size.height/2);
	resultbg->setContentSize(Size(780,128*4));
	this->addChild(resultbg,2);


	Sprite* bg2=Sprite::create("res/images/resultDialog/result_line.png");
	bg2->setPosition(size.width/2,size.height/2);
	this->addChild(bg2,3);

	auto resultbg2=Sprite::create("res/images/resultDialog/result_me_bg.png");
	resultbg2->setPosition(size.width/2-128,size.height/2+150);
	this->addChild(resultbg2,3);

	auto resultbg3=Sprite::create("res/images/resultDialog/result_win.png");
	resultbg3->setPosition(size.width/2+250,size.height/2+100);
	this->addChild(resultbg3,3,1001);

	auto resultbg4=Sprite::create("res/images/resultDialog/result_lose.png");
	resultbg4->setPosition(size.width/2+250,size.height/2-140);
	this->addChild(resultbg4,3);


	auto resultbg5=Sprite::create("res/images/resultDialog/result_nick.png");
	resultbg5->setPosition(size.width/2-315,size.height/2+230);
	this->addChild(resultbg5,4);


	auto resultbg6=Sprite::create("res/images/room/room_points_small_img.png");
	resultbg6->setPosition(size.width/2-150,size.height/2+230);
	this->addChild(resultbg6,4);


	auto resultbg7=Sprite::create("res/images/resultDialog/rank_flag.png");
	resultbg7->setPosition(size.width/2,size.height/2+230);
	this->addChild(resultbg7,4);




	Sprite* bg=Sprite::create("res/images/resultDialog/result_top.png");
	bg->setPosition(size.width/2,size.height/2+230);
	this->addChild(bg,3);




	MenuItemFont* fontMenu=MenuItemFont::create("AGAIN GAME",CC_CALLBACK_1(GameScore::onClickFunc,this));
	fontMenu->setPosition(size.width/2,size.height/2-270);
	//this->addChild(fontMenu,2);
	auto menu = Menu::create(fontMenu, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5);
	showData(4);

	std::vector<std::string>_list;
	_list.push_back("player");
	_list.push_back("robot3");
	_list.push_back("robot2");
	_list.push_back("robot4");
	showNickData(_list);

}
void GameScore::showNickData(std::vector<std::string> _list)
{
	std::vector<Point> _point;
	_point.push_back(Point(330,500));
	_point.push_back(Point(330,400));
	_point.push_back(Point(330,300));
	_point.push_back(Point(330,200));
	for(int i=0;i<_list.size();i++)
	{
		auto labelTTF=LabelTTF::create(_list[i],"Arial",40);
		labelTTF->setPosition(_point[i]);
		this->addChild(labelTTF,15);

		if(i<2)
		{
			auto labelTTF1=LabelTTF::create("+1","Arial",40);
			labelTTF1->setPosition(Point(_point[i].x+160,_point[i].y));
			this->addChild(labelTTF1,15);

			
		}
		else
		{
			auto labelTTF1=LabelTTF::create("-1","Arial",40);
			labelTTF1->setPosition(Point(_point[i].x+160,_point[i].y));
			this->addChild(labelTTF1,15);
		}
		
		auto labelTTF2=LabelTTF::create("0","Arial",40);
		labelTTF2->setPosition(Point(_point[i].x+310,_point[i].y));
		this->addChild(labelTTF2,15);

	}
}
void GameScore::onClickFunc(Ref* ref)
{
	this->removeFromParentAndCleanup(true);
	//Director::getInstance()->replaceScene(LocalplayScene::scene());
}
void GameScore::showData(int score)
{
	auto _point=this->getChildByTag(1001)->getPosition();
	char sstr[125]="/0";
	sprintf(sstr,"res/images/resultDialog/win_%d.png",score);
	Sprite* bg1=Sprite::create(sstr);

	bg1->setPosition(Point(_point.x,_point.y));
	this->addChild(bg1,10);
}