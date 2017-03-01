#ifndef __EXCELS_STR_OP_H__
#define __EXCELS_STR_OP_H__

#include "cocos2d.h"
using namespace cocos2d;

#include <map>
#include <string>
#include "res_str.h"

void InitString();

bool SetCurrentLanguage(int lang);
unsigned int GetCurrentLanguage(void);
static void I18n_BigEndian2(unsigned int* pArr, unsigned int size);
bool LoadResourceFromFile(const char* filename, unsigned int lang);
bool SGL_LoadResource(unsigned int lang);
const char* LoadString(int strId);
void ReleaseString();

#endif