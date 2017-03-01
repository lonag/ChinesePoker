#ifndef _ccskynet_message_h_
#define _ccskynet_message_h_
#include "../ccskynet/skynet_databuffer.h"

//packet =type code id data-------size
struct packet
{
	short size;
	short type;//1
	short code;
	int   id;
	packet()
	{
		type=1;id=1;size=0;//
	}
};
class ccskynet_message :packet
{
public:
	void setType(short type);
	void setCode(short code);
	void setId(int id);
	//size
	unsigned short getSize();
	unsigned short getCode();
	unsigned int   getId();
	unsigned short getType();
    
public:
	ccskynet_message(int size=64);
	~ccskynet_message(){}
	ByteBuffer* buffer;
	ByteBuffer* GetBuffer();
	char* getData();
};
#endif
