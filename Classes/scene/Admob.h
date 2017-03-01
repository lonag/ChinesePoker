#ifndef __AD_MOB_H__
#define __AD_MOB_H__

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "protocols/ProtocolAds.h"

class MyAdsListener : public cocos2d::plugin::AdsListener
{
public:
	virtual void onAdsResult(cocos2d::plugin::AdsResultCode code, const char* msg);
	virtual void onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points);
};

class Admob
{
public:
	bool initAd(); 
	static Admob* getInstance();
	void release();
	void show();
	void hide();
private:
	cocos2d::plugin::ProtocolAds* _admob;
	MyAdsListener* _listener;
	cocos2d::plugin::ProtocolAds* _ads;
	cocos2d::plugin::ProtocolAds::AdsPos _pos;

	cocos2d::plugin::TAdsInfo adInfo;
};

#endif 
#endif
