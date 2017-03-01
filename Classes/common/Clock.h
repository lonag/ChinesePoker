#ifndef _CLOCK_H_
#define _CLOCK_H_
#include "cocos2d.h"
USING_NS_CC;
typedef void (Ref::*time_out_func)(Ref*);
#define time_func_selector(_selector) time_out_func(&_selector)

class Clock :public Node
{
public:
	virtual bool init();
	//clock
	static Clock* create(int timeout,Point point,Ref* b,time_out_func func);
	long getCurrentTime();
	void clockTimer(float dt);
	time_out_func func;
	Ref* target;
	Point point;
	int timeout;
	unsigned long startTime;
	unsigned long currentTime;
	int offsetIime;
	int endTime;
	void initiation();
};

class CallTimer :public Node
{
public:
	virtual bool init();
	//clock
	static void create(Ref* b,int timeout,time_out_func func);
	long getCurrentTime();
	void clockTimer(float dt);
	time_out_func func;
	Ref* target;
	int timeout;
	int startTime;
	int currentTime;
	int offsetIime;
};
#define CallLater(node,timeout,func) CallTimer::create(node,timeout,func)

#endif