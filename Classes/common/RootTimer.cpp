#include "../common/RootTimer.h"

RootTimer::RootTimer()
{
	startTime=0;
	offsetTime=1200;
	currentTime=0;
	timeout=0;
}

RootTimer::~RootTimer()
{
	startTime=0;
	offsetTime=1200;
	currentTime=0;
	timeout=0;
}

void RootTimer::timeOut(int timeout,Ref* b,time_out_func func)
{
	this->timeout=timeout;
	this->target=b;
	this->func=func;
	startTime=BaseManager::getInstance()->getCurrentTime();
	this->schedule(schedule_selector(RootTimer::timer));
}

void RootTimer::timer(float dt)
{
	currentTime=BaseManager::getInstance()->getCurrentTime();
	if (currentTime>=startTime+offsetTime)
	{
		timeout--;
		startTime=BaseManager::getInstance()->getCurrentTime();
		if (timeout<0)
		{
			this->unschedule(schedule_selector(RootTimer::timer));
			(target->*func)(this);
		}
	}
}
