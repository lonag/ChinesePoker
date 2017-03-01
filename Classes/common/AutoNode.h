#ifndef _AUTO_NODE_H_
#define _AUTO_NODE_H_
#include "../common/RootLayer.h"
class AutoNode:public Node
{
public:
	virtual bool init();
	static AutoNode* create();
	void ShowPoke(std::vector<PokeData>& data,int id,bool remove=false);
	Node* nodePoke;
	void timer(float dt);
};
#endif