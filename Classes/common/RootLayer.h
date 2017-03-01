#ifndef _ROOT_LAYER_H_
#define _ROOT_LAYER_H_
#include "cocos2d.h"
//#include "cocos-ext.h"
#include "../common/CommonUtils.h"
#include "../excelsr/ExcelsStrOp.h"
//USING_NS_CC_EXT;
USING_NS_CC;
class RootLayer :public Layer
{
public:
	enum TipsStyle
	{
		kTipsSure,
		kTipsBad,
		kTipsNone
	};
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void exitGame(Ref* obj);
	virtual void initiation() =0;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
    
public:
	void showTips(std::string str,TipsStyle style,Ref* obj=NULL,const ccMenuCallback& callbackoK=NULL,const ccMenuCallback& callbackCancell=NULL);
};
#endif
