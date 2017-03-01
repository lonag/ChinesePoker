#include "xTextParse.h"
static xTextParse* _xTextParse=NULL;
xTextParse::xTextParse()
{

}
xTextParse::~xTextParse()
{

}
xTextParse* xTextParse::getParse()
{
	if(_xTextParse==NULL)
	{
		return _xTextParse=new xTextParse();
	}
	return _xTextParse;
}
std::string xTextParse::getDataById(std::string key)
{
	if(_textdata.find(key)!=_textdata.end())
	{
		return _textdata.find(key)->second;
	}
	return "";
}
int xTextParse::load(const char* filename)
{
	FILE           *fp;
    char            key[128], value[4096], data[4096];
    int             ret, line = 0;

	std::string str=FileUtils::getInstance()->fullPathForFilename(filename);
	if ((fp = fopen(str.c_str(), "rb")) == NULL) {
        log("can not open text: %s", filename);
        return 1;
    }
	while (fgets(data, 4096, fp)) {
		line ++;
		
		ret = parseValue(data, key, value);
		_textdata[key]=value;
    }
	fclose(fp);
    return 0;
}
 /* 是段名 */
char* xTextParse::isSectionName(char *str) {
    if (str == NULL || strlen(str) <= 2 || (*str) != '[') 
        return NULL;
            
    char *p = str + strlen(str);
    while ((*(p-1)) == ' ' || (*(p-1)) == '\t' || (*(p-1)) == '\r' || (*(p-1)) == '\n') p--;
    if (*(p-1) != ']') return NULL;
    *(p-1) = '\0';

    p = str + 1;
    while(*p) {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || (*p == '_')) {
        } else {
            return NULL;
        }
        p ++;
    }
    return (str+1);
}
 /**
     * 解析字符串
     */
int xTextParse::parseValue(char *str, char *key, char *val)
{
    char  *p, *p1, *name, *value;
    
    if (str == NULL)
        return -1;
    p = str;
    // 去前置空格
    //while ((*p) == ' ' || (*p) == '\t' || (*p) == '\r' || (*p) == '\n') p++;
    p1 = p + strlen(p);
    // 去后置空格
    while(p1 > p) {
        p1 --;
        if (*p1 == ' ' || *p1 == '\t' || *p1 == '\r' || *p1 == '\n') continue;
        p1 ++;
        break;
    }
    (*p1) = '\0';
    // 是注释行或空行
    //if (*p == '#' || *p == '\0') return -1;
    p1 = strchr(str, '\t');
    if (p1 == NULL) return -2;
    name = p;
    value = p1 + 1;
    while ((*(p1 - 1)) == ' ') p1--;
    (*p1) = '\0';
    
    //while ((*value) == ' ') value++;
    //p = strchr(value, '#');
    //if (p == NULL) p = value + strlen(value);
    //while ((*(p - 1)) <= ' ') p--;
    //(*p) = '\0';
    if (name[0] == '\0')
        return -2;
    
    strcpy(key, name);
    strcpy(val, value);
    log("str = %s value = %s ",key,val);
    return 0;
}