#include "../scene/Admob.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "protocols/PluginManager.h"
#include "configs/Configs.h"
USING_NS_CC;
using namespace cocos2d::plugin;
static Admob* instance=nullptr;
Admob* Admob::getInstance()
{
	if (instance==nullptr)
	{
		instance = new Admob();
	}
	return instance;
}
bool Admob::initAd()
{
	 _listener = new MyAdsListener();
	_admob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
	TAdsDeveloperInfo devInfo;
	 devInfo["AdmobID"] = ADMOB_ID_ANDROID;
	 _admob->configDeveloperInfo(devInfo);
	 _admob->setAdsListener(_listener);
	 _admob->setDebugMode(true);
	 // init options
	 _ads = _admob;
	 _pos = ProtocolAds::kPosTop;

	 // init the AdsInfo
	 adInfo["AdmobType"] = "1";
	 adInfo["AdmobSizeEnum"] = "1";

}
void Admob::show()
{
	if (_ads)
	{
		_ads->showAds(adInfo, _pos);
	}
}
void Admob::hide()
{
	_ads->hideAds(adInfo);
}
void Admob::release()
{
	if (_admob != NULL)
	{
		_admob->hideAds(adInfo);
		PluginManager::getInstance()->unloadPlugin("AdsAdmob");
		_admob = NULL;
	}
	if (NULL != _listener)
	{
		delete _listener;
		_listener = NULL;
	}
}
void MyAdsListener::onAdsResult(AdsResultCode code, const char* msg)
{
	log("OnAdsResult, code : %d, msg : %s", code, msg);
}

void MyAdsListener::onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points)
{
	log("Player get points : %d", points);

	// @warning should add code to give game-money to player here

	// spend the points of player
	if (pAdsPlugin != NULL) {
		pAdsPlugin->spendPoints(points);
	}
}
#endif