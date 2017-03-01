#ifndef _COUNT_NODE_H_
#define _COUNT_NODE_H_
#include "cocos2d.h"
USING_NS_CC;
class CountNode: public Node
{
public:
	virtual bool init();
	static CountNode* create();
	void setString(int count);
private:
	LabelTTF* m_count;
};
#endif