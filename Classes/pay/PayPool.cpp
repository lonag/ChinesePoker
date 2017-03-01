#include "../pay/PayPool.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
#endif
USING_NS_CC;


void PayPool::pay()
{
	//Director::getInstance()->resume();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp_empty_test/Cocos2dxActivity", "pay", "()V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			//JniHelper::getJavaVM()->DetachCurrentThread();
			//log("sucess!");
		}
#endif	
}
void PayPool::playCGVideo(std::string name)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp_empty_test/Cocos2dxActivity",
		"playVideo",
		"(Ljava/lang/String;)V"))
	{
		jstring uriStr = t.env->NewStringUTF(name.c_str());
		t.env->CallStaticObjectMethod(t.classID, t.methodID,uriStr);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(uriStr);
	}
#endif
}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

#include "protocols/PluginManager.h"
#include "cocos2d.h"
#include "configs/Configs.h"

using namespace cocos2d::plugin;
using namespace cocos2d;

MyPurchase* MyPurchase::s_pPurchase = NULL;

MyPurchase::MyPurchase()
	: s_pAlipay(NULL)
	, s_pRetListener(NULL)
	, s_pNd91(NULL)
{

}

MyPurchase::~MyPurchase()
{
	unloadIAPPlugin();
	if (s_pRetListener)
	{
		delete s_pRetListener;
		s_pRetListener = NULL;
	}
}

MyPurchase* MyPurchase::getInstance()
{
	if (s_pPurchase == NULL) {
		s_pPurchase = new MyPurchase();
	}
	return s_pPurchase;
}

void MyPurchase::purgePurchase()
{
	if (s_pPurchase)
	{
		delete s_pPurchase;
		s_pPurchase = NULL;
	}
	PluginManager::end();
}

void MyPurchase::loadIAPPlugin()
{
	if (s_pRetListener == NULL)
	{
		s_pRetListener = new MyPurchaseResult();
	}

	{
		// init alipay plugin
		s_pAlipay = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("MaoPay"));
		TIAPDeveloperInfo pAlipayInfo;
		pAlipayInfo["Nd91AppId"] = ND91_APPID;
		pAlipayInfo["Nd91AppKey"] = ND91_APPKEY;
		pAlipayInfo["Nd91Orientation"] = ND91_ORIENTATION;
		if (pAlipayInfo.empty())
		{
			char msg[256] = { 0 };
			sprintf(msg, "Developer info is empty. PLZ fill your alipay info in %s(nearby line %d)", __FILE__, __LINE__);
			MessageBox(msg, "MaoPay Warning");
		}
		s_pAlipay->setDebugMode(true);
		s_pAlipay->configDeveloperInfo(pAlipayInfo);
		s_pAlipay->setResultListener(s_pRetListener);
	}

//	{
// 		TIAPDeveloperInfo pNdInfo;
// 		pNdInfo["Nd91AppId"] = ND91_APPID;
// 		pNdInfo["Nd91AppKey"] = ND91_APPKEY;
// 		pNdInfo["Nd91Orientation"] = ND91_ORIENTATION;
// 		if (pNdInfo.empty()) {
// 			char msg[256] = { 0 };
// 			sprintf(msg, "Developer info is empty. PLZ fill your Nd91 info in %s(nearby line %d)", __FILE__, __LINE__);
// 			MessageBox(msg, "Nd91 Warning");
// 		}
// 		s_pNd91 = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()->loadPlugin("IAPNd91"));
// 		s_pNd91->setDebugMode(true);
// 		s_pNd91->configDeveloperInfo(pNdInfo);
// 		s_pNd91->setResultListener(s_pRetListener);
//	}
}

void MyPurchase::unloadIAPPlugin()
{
	if (s_pAlipay)
	{
		PluginManager::getInstance()->unloadPlugin("MaoPay");
		s_pAlipay = NULL;
	}

// 	if (s_pNd91)
// 	{
// 		PluginManager::getInstance()->unloadPlugin("IAPNd91");
// 		s_pNd91 = NULL;
// 	}
}

void MyPurchase::payByMode(TProductInfo info, MyPayMode mode)
{
	ProtocolIAP* pIAP = NULL;
	switch(mode)
	{
	case eAlipay:
		pIAP = s_pAlipay;
		break;
	case eND91:
		//pIAP = s_pNd91;
		break;
	default:
		break;
	}

	if (pIAP) {
		pIAP->payForProduct(info);
	}
}

void MyPurchaseResult::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
	char goodInfo[1024] = { 0 };
	sprintf(goodInfo, "商品名称:%s\n商品价格:%s\n商品描述:%s",
		info.find("productName")->second.c_str(),
		info.find("productPrice")->second.c_str(),
		info.find("productDesc")->second.c_str());
	MessageBox(goodInfo , msg);
}


#endif