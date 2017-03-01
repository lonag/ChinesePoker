#ifndef _HALL_SCENE_H_
#define _HALL_SCENE_H_
#include "cocos2d.h"
#include "../common/RootLayer.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "protocols/ProtocolAds.h"

#endif
class HallScene:public RootLayer
{
public:
	static Scene* scene();
	virtual bool init();
	virtual void initiation();
	CREATE_FUNC(HallScene);
private:
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	// a selector callback
	void menuBackCallback(Ref* pSender);
	void eventMenuCallback(Ref* pSender);
#endif
};
#endif