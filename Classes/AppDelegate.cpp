#include "AppDelegate.h"
#include "scene/LocalplayScene.h"//
#include "scene/HallScene.h"
#include "scene/GameScene.h"
#include "scene/MainScene.h"
#include "scene/Logo.h"
#include "common/UserInfo.h"
#include "scene/GameScore.h"
#include "log/logger.h"
#include <vector>
#include <string>
#include "excelsr/ExcelsStrOp.h"
#include "scene/Tablescene.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "ccskynet/ccskynet_manager.h"
USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	//::getInstance()->releaseService();
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::createWithRect("iDevice", Rect(0,0,800,480));
		director->setOpenGLView(glview);
	}
	director->setOpenGLView(glview);
	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);


	Size frameSize = glview->getFrameSize();
	// turn on display FPS
	director->setDisplayStats(true);
	
	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);
	//SGL_LoadResource(0);
	// create a scene. it's an autorelease object
	//Logger::getInstance()->startService();
	//auto scene = LocalplayScene::scene();
	/*auto scene = GameScore::scene();*/
	/*auto scene = MainScene::scene();*/
	auto scene = Logo::scene();
	// run
	director->runWithScene(scene);
	UserInfo::getInstance()->setIsMusic(true);
	UserInfo::getInstance()->setIsSound(true);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
