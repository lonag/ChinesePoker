#ifndef _TOAST_H_
#define _TOAST_H_
#include "cocos2d.h"
USING_NS_CC;
class Toast : public Layer
{
public:
	virtual bool init();
	static void showToast(Node* node,std::string tips,Point point);

	void delete_out(float dt);
};
#endif