#include "../ccskynet/ccskynet_socket.h"
#include "cocos2d.h"
USING_NS_CC;
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
#pragma comment(lib, "Ws2_32.lib")
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static bool bStartup = false;
#endif

ccskynet_socket::ccskynet_socket()
	: m_uSocket(INVALID_SOCKET)
{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	if( !bStartup ) 
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);
		bStartup = true;
	}
#endif
}

ccskynet_socket::~ccskynet_socket()
{
	ccClose();
}

bool ccskynet_socket::ccInit()
{
	if( m_uSocket != INVALID_SOCKET )
	{
		ccClose();
	}

	m_uSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( m_uSocket == INVALID_SOCKET )
	{
		CCLOGERROR("create socket failed");
		return false;
	}

#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	unsigned long ul = 1;
	int nRet = ioctlsocket(m_uSocket, FIONBIO, (unsigned long*)&ul);
	if( nRet == SOCKET_ERROR )
	{
		CCLOGERROR("set unblocking failed");
		ccClose();
		return false;
	}
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	int nFlags = fcntl(m_uSocket, F_GETFL, 0);
	int nRet = fcntl(m_uSocket, F_SETFL, nFlags | O_NONBLOCK);
	if( nRet == SOCKET_ERROR )
	{
		CCLOGERROR("set unblocking failed");
		ccClose();
		return false;
	}
#endif

	int nNoDelay = 1;
	if( setsockopt(m_uSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&nNoDelay, sizeof(nNoDelay)) == SOCKET_ERROR )
	{
		CCLOGERROR("set nodelay failed");
		ccClose();
		return false;
	}

	return true;
}

void ccskynet_socket::ccClose()
{
	if( m_uSocket != INVALID_SOCKET )
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		closesocket(m_uSocket);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		close(m_uSocket);        
#endif
		m_uSocket = INVALID_SOCKET;
	}
}

bool ccskynet_socket::ccConnect()
{
#if 0 // runtime error on ios
	CCAssert(strlen(m_oInetAddress.getIp()) && m_oInetAddress.getPort() != 0, "_connect");
#endif

	if( m_uSocket == INVALID_SOCKET )
	{
		if(!ccInit())
		{
			return false;
		}
	}
	struct sockaddr_in my_addr;

	my_addr.sin_addr.s_addr=inet_addr(ip.c_str());
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons((unsigned short)port);


	int nRet = ::connect(m_uSocket,(struct sockaddr *)&my_addr,sizeof(struct sockaddr_in));
	if( nRet == 0 )
	{
		return true;
	}
	else
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		int nError = WSAGetLastError();
		if( nError ==  WSAEWOULDBLOCK )
		{
			return true;
		}
		else
		{
			return false;
		}
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		if( nRet == SOCKET_ERROR && errno == EINPROGRESS )
		{
			return true;
		}
		else
		{
			return false;
		}
#endif
	}
}

void ccskynet_socket::ccDisconnect()
{
	if( m_uSocket != INVALID_SOCKET )
	{
#if 0
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		shutdown(m_uSocket, SD_BOTH);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		shutdown(m_uSocket, SHUT_RDWR);
#endif
#endif
		ccClose();
	}
}

void ccskynet_socket::setInetAddress(std::string ip,unsigned short port)
{
	this->ip=ip;
	this->port=port;
}

static int readall(int fd, char * buffer, size_t sz)
{
		for (;;) 
		{
            int err = 0;//recv(fd , buffer, sz, MSG_WAITALL);
			if (err < 0) {
				if (errno == EAGAIN || errno == EINTR)
					continue;
				break;
			}
			return err;
		}
		log("Socket error");
		//exit(1);
    return 0;
}

int ccskynet_socket::ccRead(char* _buff, int _len)
{
	if( m_uSocket == INVALID_SOCKET )
		return eSocketIoError;
// 	uint8_t header[2];
// 	if (readall(m_uSocket, (char*)header, 2) == 0)
// 	{
// 
// 	}
// 	else
// 	{
// 		log("error package style");
// 		return -1;
// 	}
// 	_len = header[0] << 8 | header[1];


    return 0;//::recv(m_uSocket, _buff, _len, 0);
}

int ccskynet_socket::ccWrite(char* _buff, int _len)
{
	if( m_uSocket == INVALID_SOCKET )
		return eSocketIoError;

#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
// 	std::string buffer=_buff;
// 	char tmp[1024];
// 	int i=0;
// 	for (i=0;i<buffer.length();i++)
// 	{
// 		tmp[i]=buffer[i];
// 	}
// 	tmp[i]='\0';
// 
// 	int n = strlen(tmp) -1;
// 	uint8_t head[2];
// 	head[0] = (n >> 8) & 0xff;
// 	head[1] = n & 0xff;
// 	int r;
// 	r = ::send(m_uSocket, (char*)head, 2, 0);
// 	if (r<0) 
// 	{
// 		log("send head error");
// 		return r;
// 		
// 	}
// 	r = ::send(m_uSocket, tmp , n, 0);
// 	if (r<0) 
// 	{
// 		log("send data error");
// 		return r;
// 		
// 	}
// 	return r;
	return ::send(m_uSocket, _buff, _len, 0);
#endif

#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    return 0;//::send(m_uSocket, _buff, _len, SO_NOSIGPIPE);
#endif
}

bool ccskynet_socket::ccIsReadable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_uSocket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	int ret=select((int)(m_uSocket + 1), &fd, NULL, NULL, &tv) ;
	if(  ret>0)
	{
		if( FD_ISSET(m_uSocket, &fd) )
		{
			return true;
		}
	}

	return false;
}

bool ccskynet_socket::ccIsWritable()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_uSocket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if( select((int)(m_uSocket + 1), NULL, &fd, NULL, &tv) > 0 )
	{
		if( FD_ISSET(m_uSocket, &fd) )
		{
			return true;
		}
	}

	return false;
}

int ccskynet_socket::ccIsConnected()
{
	fd_set	fd;
	struct timeval tv;

	FD_ZERO(&fd);
	FD_SET(m_uSocket, &fd);

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if( select((int)(m_uSocket + 1), NULL, &fd, NULL, &tv) > 0 )
	{
		if( FD_ISSET(m_uSocket, &fd) )
		{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

			return eSocketConnected;

#elif( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

			int nError;
			socklen_t len = sizeof(nError);
			if( getsockopt(m_uSocket, SOL_SOCKET, SO_ERROR, &nError, &len) < 0 )
			{
				return eSocketConnectFailed;
			}
			if( nError == ECONNREFUSED || nError == ETIMEDOUT )
			{
				return eSocketConnectFailed;
			}
			return eSocketConnected;

#endif
		}
	}
	return eSocketConnecting;
}
