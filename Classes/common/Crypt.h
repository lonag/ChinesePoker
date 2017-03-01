#ifndef _crypt_h_
#define _crypt_h_
#include "cocos2d.h"
USING_NS_CC;
#ifndef UCHAR
#define UCHAR unsigned char
#endif

class Crypt
{
public:
	// ���ṩ����Կ��ĳ���ڴ�������м��ܣ�����ڴ�Ҫ����8�ֽڵ���������
	static bool Encrypt(void* pIn, void* pOut, const int nLen, UCHAR* key);
	// ���ṩ����Կ��ĳ���ڴ�������н��ܣ�����ڴ�Ҫ����8�ֽڵ���������
	static bool Decrypt(void* pIn, void* pOut, const int nLen, UCHAR* key);
	// ��ĳ��������ļ��ڴ���н��ܣ���Կ�������Կ�����е�һ������
	static bool Encrypt(void* pIn, void* pOut, const int nLen, const int nIndex, const int nMethod = 0);
	static bool Decrypt(void* pIn, void* pOut, const int nLen, const int nIndex, const int nMethod = 0);
	// 3des�ӽ���ͨ�ú�����bEncypt�����Ƿ���ܣ�
	static bool crypt(UCHAR* pIn, UCHAR* pOut, const int nLen, UCHAR* key, bool bEncypt=0);
};
#endif