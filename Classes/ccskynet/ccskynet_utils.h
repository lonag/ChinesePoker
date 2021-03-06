#ifndef _ccskynet_utils_h
#define _ccskynet_utils_h
#include "cocos2d.h"

#include <vector>
#include <string>
#include <cmath>

#include <algorithm>


class ByteBuffer;



using namespace std;

#define  Float_MAX_VALUE  3.4028235E+38F
#define  Float_MIN_VALUE  1.4E-45F;

// Helpers to safely delete Refs and arrays
#define SQ_SAFE_DELETE(x)       {if(x){ delete x; x = 0; }}
#define SQ_SAFE_DELETE_ARRAY(x) {if(x){ delete[] x; x = 0; }}
#define SQ_SAFE_DELETE_VEC(x) {for(int i = 0; i < x->size();i++){delete (x+i);}delete[] x;}

static const double ERROR_INS = 0.005;
extern unsigned char* readFile(const char *filename);
extern string byteToHexStr(unsigned char *byte_arr, int arr_len);
extern double distance(double x1, double y1, double x2, double y2);
extern unsigned long msNextPOT(unsigned long x);

#define SAFE_DELETE_ELEMENT( ptr ) if (ptr != NULL) {delete ptr; ptr = NULL;}
#define SAFE_DELETE_ARRAY( ptr )if (ptr != NULL){delete[] ptr;ptr = NULL;}

template<typename _RandomAccessIterator>
inline void safe_delete_vector(_RandomAccessIterator __first, _RandomAccessIterator __last)
{

	for (_RandomAccessIterator it = __first;it!= __last ; ++it) {
		if( (*it)!=NULL){
			delete *it;
			*it = NULL;
		}
	}
}	


//CString StringConvertToUnicodeBytesCodes(const wchar_t* lpszNeedConvert);

template <class Class, typename TT>
inline bool instanceof(TT const &Ref)
{
    return dynamic_cast<Class const *>(&Ref);
	//return false;
}

const char* fullpathFromRelatePath(const char* relatePath);

bool writeSaveData(const char* relatepath,char* buf,int len);

ByteBuffer* readSaveData(const char* relatepath);

ByteBuffer* getFileData(const char* pszfullFilepath, bool isfullPath);

std::string createRandString(int len,bool filter);



#endif
