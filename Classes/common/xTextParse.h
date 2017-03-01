#ifndef _x_text_parse_h_
#define _x_text_parse_h_
#include "cocos2d.h"
USING_NS_CC;
class xTextParse
{
public:
	xTextParse();
	~xTextParse();
	static xTextParse* getParse();
	int load(const char* filename);
	std::string getDataById(std::string key);
private:
	int parseValue(char *str, char *key, char *val);
	char *isSectionName(char *str);
	std::map<std::string,std::string>_textdata;
};
#define lformat(key) xTextParse::getParse()->getDataById(key)
#endif//