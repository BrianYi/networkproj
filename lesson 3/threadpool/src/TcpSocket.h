/*
 * Copyright (C) 2020 BrianYi, All rights reserved
 */
#pragma once
#include "Socket.h"
#include "Address.h"
class TcpSocket: public Socket
{ 
public:
	TcpSocket( );
	TcpSocket( int32_t fd, bool binded, Address& address );
	TcpSocket( const TcpSocket& inTcpSocket ) = delete;
	~TcpSocket( );
	void listen( const uint16_t& inPort, const uint32_t& inQueueLength );
	int32_t connect( const Address& inAddress, IOType inIOType = Blocking );
	int32_t connect( const std::string& inIP, const uint16_t& inPort, IOType inIOType = Blocking );
	TcpSocket* accept( IOType inIOType = Blocking );
	int32_t send( const char* inContent, const uint32_t& inSiz, IOType inIOType = Blocking );
	int32_t recv( char* outContent, const uint32_t& inSize, IOType inIOType = Blocking );
	Address address( void );
	std::string ip( void );
	uint16_t port( void );
protected:
	Address fAddress;
};

