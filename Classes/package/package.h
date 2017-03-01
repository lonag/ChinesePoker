#ifndef pak_package_h_
#define pak_package_h_
#include "cocos2d.h"
class package
{
public:
	package();
	~package();
	void ScanDirInternal(/*std::vector<std::string>& result*/) const;
};

#endif//