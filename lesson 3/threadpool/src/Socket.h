/*
 * Copyright (C) 2020 BrianYi, All rights reserved
 */
#pragma once
#include "PlatformHeader.h"
class Socket
{ 
public:
	enum IOType
	{
		Blocking = 0,
		NonBlocking = 1
	};
	int fSocket;
    const uint32_t SEND_BUF_SIZE = 10 * 1024;
    const uint32_t RECV_BUF_SIZE = 10 * 1024;
public:
	Socket( int32_t inSocketType, int32_t inProtocol, IOType inIOType = Blocking );
	Socket( int32_t fd, bool binded, int32_t inSocketType, int32_t inProtocol, IOType inIOType = Blocking );
	virtual ~Socket( );
	void setIOType( IOType inIOType );
	void reuse_addr( );
	void no_delay( );
	void keep_alive( );
	void set_socket_sndbuf_size( uint32_t inNewSize );
	void set_socket_rcvbuf_size( uint32_t inNewSize );
protected:
	void open( );
	void close( );
	void bind_to_port( const uint16_t& inPort );
protected:
	int32_t fSocketType;
	int32_t fProtocol;
	bool fOpened;
	bool fBinded;
	IOType fIOType;
private:
	Socket( );
	Socket( const Socket& ) = delete;
	static uint32_t s_num_sockets;
};

