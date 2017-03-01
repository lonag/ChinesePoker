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
	// 用提供的密钥对某段内存区域进行加密（这段内存要满足8字节的整数倍）
	static bool Encrypt(void* pIn, void* pOut, const int nLen, UCHAR* key);
	// 用提供的密钥对某段内存区域进行解密（这段内存要满足8字节的整数倍）
	static bool Decrypt(void* pIn, void* pOut, const int nLen, UCHAR* key);
	// 对某个区域的文件内存进行解密，密钥是针对密钥数组中的一个索引
	static bool Encrypt(void* pIn, void* pOut, const int nLen, const int nIndex, const int nMethod = 0);
	static bool Decrypt(void* pIn, void* pOut, const int nLen, const int nIndex, const int nMethod = 0);
	// 3des加解密通用函数（bEncypt代表是否加密）
	static bool crypt(UCHAR* pIn, UCHAR* pOut, const int nLen, UCHAR* key, bool bEncypt=0);
};
#endif