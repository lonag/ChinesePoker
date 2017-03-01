#ifndef _logger_h_
#define _logger_h_

#include "cocos2d.h"
USING_NS_CC;
#define GameLog(str, ...) \
	Logger::getInstance()->logFlush(); \
	Logger::getInstance()->format(str, ##__VA_ARGS__)
class Logger
{
public:
	static Logger* getInstance();
	void printLOG(std::string str);
	//inline void printLOG(int i);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	void format(const char* format, ...) CC_FORMAT_PRINTF(1, 2);
#else
	void format(const char* format, ...);
#endif
public:
	std::string GetLogFileName();
	void startService();
	void logFlush();
	FILE* _file;
	void releaseService();
};

template<typename T>
T str2value(const std::string& s) 
{
	std::istringstream is(s);
	T t;
	is >> t;
	return t;
}

template<typename T>
T str2value(const char* s) 
{
	std::istringstream is(s);
	T t;
	is >> t;
	return t;
}

template <class TYPE>
inline std::string val2str(const TYPE& value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

inline void str2value(float& value, const char * pstr)
{
	//win32
	std::stringstream ss;
	ss << pstr;
	ss >> value;

}

inline void str2value(double& value, const char * pstr)
{
	char* endptr;
	value = strtod(pstr, &endptr);
	if (*endptr)
		throw std::runtime_error("not a number");
}

inline void str2value(int& value, const char * pstr)
{
	char* endptr;
    value = 0;//strtol(pstr, &endptr, 10);
	if (*endptr)
		throw std::runtime_error("not a number");
}

inline void str2value(char& value, const char * pstr)
{
	int i;
	str2value(i, pstr);
	value = char(i);
	if (value != i)
		throw std::runtime_error("out of range");
}

//inline void str2value(int& value, const char * pstr)
//{
//	int i;
//	str2value(i, pstr);
//	value = int(i);
//	if (value != i)
//		throw std::runtime_error("out of range");
//}

inline void str2value(unsigned int& value, const char * pstr)
{
	char* endptr;
    //value = 0;//strtoul(pstr, &endptr, 10);
	if (*endptr)
		throw std::runtime_error("not a number");
}

inline void str2value(unsigned char& value, const char * pstr)
{
	/*unsigned int ui;
	str2value(ui, pstr);
	value = unsigned char(ui);*/
	//if (value != ui)
		//throw std::runtime_error("out of range");
}

inline void str2value(unsigned short& value, const char * pstr)
{
	/*unsigned int ui;
	str2value(ui, pstr);
	value = unsigned short(ui);
	if (value != ui)
		throw std::runtime_error("out of range");*/
}



#endif