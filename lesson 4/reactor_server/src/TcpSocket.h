#pragma once
#include "EventHandler.h"
class TcpSocket: public EventHandler
{ 
public:
	TcpSocket( );
	TcpSocket( const TcpSocket& inTcpSocket );
	~TcpSocket( );
	void listen( const uint16_t& inPort, const uint32_t& inQueueLength );
	int32_t connect( const Address& inAddress, IOType inIOType = Blocking );
	int32_t connect( const std::string& inIP, const uint16_t& inPort, IOType inIOType = Blocking );
	TcpSocket accept( IOType inIOType = Blocking );
	int32_t send( const char* inContent, const size_t& inSiz, IOType inIOType = Blocking );
	int32_t recv( char* outContent, const size_t& inSize, IOType inIOType = Blocking );
	Address address( void );
	std::string ip( void );
	uint16_t port( void );
protected:
	Address fAddress;
};

