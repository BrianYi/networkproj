#pragma once
#include "TcpSocket.h"
class TcpSession :
	public TcpSocket
{ 
public:
	TcpSession( TcpSocket tcpSocket );
	virtual int32_t handle_event( uint32_t flags );
};

