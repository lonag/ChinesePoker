#ifndef _ROOT_TIMER_H_
#define _ROOT_TIMER_H_
#include "cocos2d.h"
#include "../common/BaseManager.h"
#include "../common/Clock.h"
USING_NS_CC;

class RootTimer :public Node
{
public:
	RootTimer();
	~RootTimer();
	void timeOut(int timeout,Ref* b,time_out_func func);
	void timer(float dt);
	unsigned long startTime;
	int offsetTime;
	unsigned long currentTime;
	int timeout;
	Ref* target;
	time_out_func func;
};
#endif