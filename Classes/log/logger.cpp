#include "../log/logger.h"

static Logger* instance =nullptr;
void Logger::format(const char* format, ...)
 {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	#define FORMAT_SIZE (1024*100)
        
    std::string ret;
        
    va_list ap;
    va_start(ap, format);
        
    char* buf = (char*)malloc(FORMAT_SIZE);
    if (buf != nullptr)
    {
        vsnprintf(buf, FORMAT_SIZE, format, ap);
        ret = buf;
        free(buf);
    }
    va_end(ap);
	ret+="\n";
    char* buffer=(char*)ret.c_str();
	fwrite(buffer,ret.size(),1,_file);
#endif
    //return ret;
 }

Logger* Logger::getInstance()
{
	if(instance==nullptr)
	{
		instance=new Logger();
		//instance->startService();
		return instance;
	}
	return instance;
}
void Logger::releaseService()
{
	fclose(_file);
	delete instance;
	
}
void Logger::startService()
{
	std::string str=FileUtils::getInstance()->getWritablePath();
	//log((const char*)str.c_str());
	std::string strfilename=GetLogFileName();
	strfilename=str+"log"+"/"+strfilename;
	//log(strfilename.c_str());
	_file =fopen(strfilename.c_str(),"w+");
}
 
void Logger::printLOG(std::string str)
{
	str=str+"\n";
	char* buffer=(char*)str.c_str();
	fwrite(buffer,str.size(),1,_file);
}
std::string Logger::GetLogFileName() 
 { 
     //struct tm *tm;
     time_t timep; 
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
     time(&timep); 
	  tm = localtime(&timep); 
     int year = tm->tm_year + 1900; 
     int month = tm->tm_mon + 1; 
     int day = tm->tm_mday; 
     int hour=tm->tm_hour; 
     int min=tm->tm_min; 
     int second=tm->tm_sec; 
	 char buffer[256]="/0";
	 sprintf(buffer,"gamelog%d-%d-%d-%d-%d-%d.txt",year,month,day,hour,min,second);
	 std::string str(buffer);
	 return str;
 #else  
     struct timeval now; 
     gettimeofday(&now, NULL);  
     timep = now.tv_sec; 
 #endif  
    return "";
 }
void Logger::logFlush()
{
	fflush(_file);
}