#include "../ccskynet/ccskynet_message.h"
#include "cocos2d.h"
ccskynet_message::ccskynet_message(int size):buffer(NULL)
{
	buffer=new ByteBuffer(size);
}
void ccskynet_message::setType(short type)
{
	this->type=type;
}
void ccskynet_message::setCode(short code)
{
	this->code=code;
	buffer->putShort(type);
	buffer->putShort(code);
	buffer->putInt(id);
}
unsigned short ccskynet_message::getCode()
{
	return this->code;
}
unsigned short ccskynet_message::getSize()
{
	this->size=buffer->getPosition();
	return this->size;
}
ByteBuffer* ccskynet_message::GetBuffer()
{
	
	return buffer;
}
char* ccskynet_message::getData()
{
	
	return buffer->getBuffer();
}