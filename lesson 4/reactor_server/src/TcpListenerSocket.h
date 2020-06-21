#pragma once
#include "TcpSocket.h"
#include "TcpSession.h"
#include <vector>

class TcpListenerSocket :
	public TcpSocket
{
public:
	TcpListenerSocket();
	virtual ~TcpListenerSocket( );
	virtual int32_t handle_event( uint32_t flags );
protected:
	std::vector<TcpSession*> sTcpSessionArry;
	//void request_event( int events );
};

