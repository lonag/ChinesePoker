#include "../common/Clock.h"
#include "AppMacros.h"
#include "time.h"

bool Clock::init()
{
	bool bRet=false;
	do 
	{
		if (!Node::init())
		{
			return false;
		}
		initiation();
		currentTime=0;
		offsetIime=1200;
		startTime=getCurrentTime();
		srand((unsigned int)startTime);
		this->schedule(schedule_selector(Clock::clockTimer));
		bRet=true;
	} while (0);
	return bRet;
}

void Clock::initiation()
{
	__String* str=__String::createWithFormat("%d",timeout);
	auto data = LabelTTF::create(str->getCString(), "Arial", 30);
	data->setPosition(point);
	this->addChild(data, 5,23457);

	auto m_clock=Sprite::create("timer_bg.png");
	m_clock->setPosition(point);
	this->addChild(m_clock,3);
}

Clock* Clock::create(int timeout,Point point,Ref* b,time_out_func func)
{
	Clock* c=new Clock();
	c->timeout=timeout;
	c->target=b;
	c->func=func;
	c->point=point;
	c->endTime=0;
	if (c->init()&&c)
	{
		if(timeout>=15)
			c->endTime=0;//rand()%c->timeout+1;
		return c;
	}
	delete c;
	return NULL;
}

long Clock::getCurrentTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void Clock::clockTimer(float dt)
{
	currentTime=getCurrentTime();
	if (currentTime>=startTime+offsetIime)
	{
		startTime=getCurrentTime();
		timeout--;
		auto data=(LabelTTF*)this->getChildByTag(23457);
		__String* str=__String::createWithFormat("%d",timeout);
		data->setString(str->getCString());
		if (timeout<endTime)
		{
			(target->*func)(this);
			this->unschedule(schedule_selector(Clock::clockTimer));
		}
	}
}

bool CallTimer::init()
{
	bool bRet=false;
	do 
	{
		if (!Node::init())
		{
			return false;
		}
		currentTime=0;
		offsetIime=1200;
		startTime=(unsigned int)getCurrentTime();
		this->schedule(schedule_selector(CallTimer::clockTimer));
		bRet=true;
	} while (0);
	return bRet;
}

void CallTimer::create(Ref* b,int timeout,time_out_func func)
{
	CallTimer* c=new CallTimer();
	c->timeout=timeout;
	c->target=b;
	c->func=func;
	if (c->init()&&c)
	{
		Node* d=dynamic_cast<Node*>(b);
		d->addChild(c);
	}
}

long CallTimer::getCurrentTime()
{
	struct timeval tv;     
	gettimeofday(&tv,NULL);     
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void CallTimer::clockTimer(float dt)
{
	currentTime=(unsigned int)getCurrentTime();
	if (currentTime>=startTime+offsetIime)
	{
		startTime=(unsigned int)getCurrentTime();
		timeout--;
		if (timeout<0)
		{
			(target->*func)(this);
			this->unschedule(schedule_selector(CallTimer::clockTimer));
		}
	}
}
