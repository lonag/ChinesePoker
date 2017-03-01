#include "../ccskynet/ccskynet_manager.h"
#include "../ccskynet/ccskynet_dispatch.h"
#include <thread>
using namespace std;
static ccskynet_manager* instance;
ccskynet_manager::ccskynet_manager()
{

}
ccskynet_manager::~ccskynet_manager()
{
	t.join();
}
ccskynet_manager* ccskynet_manager::getInstance()
{
	if (instance==NULL)
	{
		instance=new ccskynet_manager();
		return instance;
	}
	return instance;
}
bool ccskynet_manager::connect()
{
	if( m_eStatus != eSocketConnected && m_eStatus != eSocketConnecting )
	{
		ccsSocket.setInetAddress("127.0.0.1",8888);
		if( ccsSocket.ccConnect() )
		{
			m_eStatus = eSocketConnecting;
			return true;
		}
	}
	return false;
}
void ccskynet_manager::start()
{
	if (connect())
	{
		//pthread_t pid;
		//pthread_create(&pid, NULL, run, this);
		t=std::thread(&ccskynet_manager::run,this);
		t.detach();
		m_eStatus =eSocketConnecting;
	}
	
}
void ccskynet_manager::send(ccskynet_message* mess)
{
 	if( mess==NULL /*|| !isConnected()*/ )
 		return;
	m_PsendBufferQueue.push_back(mess);
}
void* ccskynet_manager::run(void* u)
{
	ccskynet_manager* ccs=(ccskynet_manager*)u;
	for (;;)
	{
		//log("status %d",(int)ccs->m_eStatus);
		switch( ccs->m_eStatus )
		{
		case eSocketConnecting:
			{
				switch( ccs->ccsSocket.ccIsConnected() )
				{
				case eSocketConnected:
					{
						ccs->m_eStatus = eSocketConnected;
						ccs->onConnected();
					}
					break;
				case eSocketConnectFailed:
					{
						
						ccs->ccsSocket.ccClose();
						ccs->m_eStatus = eSocketConnectFailed;
						//onExceptionCaught(eSocketConnectFailed);
					}
					break;
				case eSocketConnecting:
					{
						log("time out");
						//超时判断
					}
					break;
				default:
					break;
				}
			}
			break;
		case eSocketConnected:
			{

				if( ccs->ccsSocket.ccIsReadable() )
				{
					if( ccs->canRead() )
					{
						
						return NULL;
					}
					else
					{
						//log("can read");
				
					}
						
				}
				if( ccs->ccsSocket.ccIsWritable() /*&&*/ /*!m_lSendBuffers.empty()*/ )
				{
					if( ccs->canWrite() ) 
					{
						
						return NULL;
					}
					else
					{
						//log("can write");
					}
						
				}
			}
			break;
		default:
			break;
		}	
		//log("thread sleep 1000");
		//Sleep(1000);
		 this_thread::sleep_for(chrono::milliseconds(1000));
	}
	return NULL;
}
void ccskynet_manager::disconnect()
{
	if( m_eStatus == eSocketConnected )
	{
		//shutdown();
		ccsSocket.ccDisconnect();
		m_eStatus = eSocketDisconnected;
		onDisconnected();
	}
}

void ccskynet_manager::close()
{
	if( m_eStatus == eSocketConnected )
	{
		//shutdown();
		ccsSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
	}
}
bool ccskynet_manager::canRead()
{
	int ret=ccsSocket.ccRead(m_pReadBuffer,SOCKET_READ_BUFFER_SIZE);
	//0000 0001 0002 0000 0001
	//0000 0001 0002 0000 0001
	log("read buffer  hex = %s",byteToHexStr((unsigned char*)m_pReadBuffer,ret).c_str());	
	if( ret == eSocketIoError || ret == eSocketIoClosed )
	{
		//shutdown();
		ccsSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else
	{
		ByteBuffer* buffer=new ByteBuffer((char*)m_pReadBuffer,0,ret);
		short size=buffer->getShort();
		//short type=buffer->getShort();
		short code=buffer->getShort();
		//int id=buffer->getInt();


		log("read data code = %d  size = %d",code,size);

	
// 		if(ccskynet_dispatch::getInstance()->dispatch_message("type",msg)
// 		{
// 
// 		}
// 		else
// 		{
// 			
// 		}
		//log("socket string len = %x ",m_pReadBuffer);
		//数据处理
	}
	return false;
}
bool ccskynet_manager::canWrite()
{
	if (m_PsendBufferQueue.empty())
	{
		return false;
	}
	ccskynet_message* mess=m_PsendBufferQueue.front();

	unsigned short size=mess->getSize();
	ByteBuffer* buff=new ByteBuffer(size+2);
	buff->putShort(size+2);
	buff->put(mess->getData(),0,size);

// 	char tmp[1024]="hello world";
// 	int n = strlen(tmp) -1;
	//send size
	int nRet = ccsSocket.ccWrite(buff->getBuffer(),2+size);
	if( nRet == eSocketIoError )
	{
		ccsSocket.ccClose();
		m_eStatus = eSocketIoClosed;
		onDisconnected();
		return true;
	}
	else if(nRet==2+size)
	{
		log("buffer  hex = %s",byteToHexStr((unsigned char*)buff->getBuffer(),size+2).c_str());	
	}
	m_PsendBufferQueue.pop_front();

	return false;
}