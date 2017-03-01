#ifndef _PAY_POOL_H_
#define _PAY_POOL_H_
#include <string>
using namespace std;
#include "cocos2d.h"
typedef void (*PayCallback)(int code, const char *pszOrderId,
							  float orderAmount, int payWayId, const char *pszPayWayName);
class PayPool 
{
public:
	static void pay();
	static void playCGVideo(std::string name);
};
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "protocols/ProtocolIAP.h"

class MyPurchaseResult : public cocos2d::plugin::PayResultListener
{
public:
	virtual void onPayResult(cocos2d::plugin::PayResultCode ret, const char* msg, cocos2d::plugin::TProductInfo info);
};

class MyPurchase
{
public:
	static MyPurchase* getInstance();
	static void purgePurchase();

	typedef enum {
		eNoneMode = 0,
		eAlipay,
		eND91,
	} MyPayMode;

	void unloadIAPPlugin();
	void loadIAPPlugin();
	void payByMode(cocos2d::plugin::TProductInfo info, MyPayMode mode);

private:
	MyPurchase();
	virtual ~MyPurchase();

	static MyPurchase* s_pPurchase;

	cocos2d::plugin::ProtocolIAP* s_pAlipay;
	cocos2d::plugin::ProtocolIAP* s_pNd91;
	MyPurchaseResult* s_pRetListener;
};
#endif
#endif