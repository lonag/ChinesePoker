#include "ExcelsStrOp.h"

#define RES_FILENAME				"res_lang%d.txt"
#define SGL_MAX_LNG_COUNT			40

//language table;
static struct LANGUAGE_T
{
	unsigned int* offset;		//data offset table;
	unsigned int * data;		//data;
}languages[SGL_MAX_LNG_COUNT];

//local datas;
static int cur_lang = 0; 

void InitString()
{
	memset(&languages,0, sizeof(languages));
}

bool SetCurrentLanguage(int lang)
{
	if(lang == cur_lang || lang >= SGL_MAX_LNG_COUNT) 
		return false;

	cur_lang = lang;
	return true;
}

unsigned int GetCurrentLanguage(void)
{
	return cur_lang;
}


static void I18n_BigEndian2(unsigned int* pArr, unsigned int size)
{
	unsigned int i;
	char* pb;
	char tmp;

	for(i = 0; i < size; i++)
	{
		pb = (char*)&pArr[i];
		tmp = pb[0];
		pb[0] = pb[1];
		pb[1] = tmp;
	}
}


bool LoadResourceFromFile(const char* filename, unsigned int lang)
{
	ssize_t len = 0;
	Data m_data=FileUtils::getInstance()->getDataFromFile(filename);
	unsigned char* pData =m_data.getBytes();
	len=m_data.getSize();
	if(pData)
	{
		languages[cur_lang].data = (unsigned int*)malloc(len);
		languages[cur_lang].offset = (unsigned int*)malloc(sizeof(int)*RES_STRING_COUNT);
		if (!languages[cur_lang].data)
		{	
			return false;
		}
		memcpy(languages[cur_lang].data,pData,len);
		for (int i=0; i< RES_STRING_COUNT; i++)
		{
			unsigned char* p =(unsigned char*)languages[cur_lang].data;
			languages[cur_lang].offset[i] = RES_STRING_COUNT*2+p[i*2]+p[i*2+1]*256;	//每个偏移为2个字节+本身偏移;
		}
		return true;
	}
	return false;
}

bool SGL_LoadResource(unsigned int lang)
{	
	char filename[64] ={0};
	sprintf(filename, RES_FILENAME, lang);
	if(LoadResourceFromFile(filename, lang))
		return true;
	return false;
}


const char* LoadString(int strId)
{
	if(strId >= RES_STRING_COUNT) 
	{
		return NULL;
	}
	if(!languages[cur_lang].offset)
	{
		if(!SGL_LoadResource(cur_lang))
			return NULL;
	}
	return (const char *)((const char *)languages[cur_lang].data + languages[cur_lang].offset[strId]);
}


void ReleaseString()
{
	for (int i =0;i< SGL_MAX_LNG_COUNT;i++)
	{
		if (languages[cur_lang].data)
		{
			free(languages[cur_lang].data);
			languages[cur_lang].data = NULL;
		}
		if (languages[cur_lang].offset)
		{
			free(languages[cur_lang].offset);
			languages[cur_lang].offset =NULL;
		}
	}
}

