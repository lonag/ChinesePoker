#ifndef _game_score_h_
#define _game_score_h_
#include "../common/RootLayer.h"
#include "cocos2d.h"
USING_NS_CC;//你奶奶个熊
class GameScore:public RootLayer
{
public:
	static Scene* scene();
	virtual bool init();
	virtual void initiation();
	void onClickFunc(Ref* ref);
	CREATE_FUNC(GameScore);
public:
	void showData(int);
	void showNickData(std::vector<std::string> _list);
};
#endif