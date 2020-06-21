#pragma once
#include "common.h"
#include <string>

class Address : public sockaddr_in
{
public:
	Address( );
	Address( const uint16_t& inPort );
	Address( const std::string& inIP, const uint16_t& inPort );
	Address( struct sockaddr_in inSockAddr );
	~Address( );
	std::string getIP( ) const;
	void setIP( const std::string& inIP );
	uint16_t getPort( ) const;
	void setPort( const uint16_t& inPort );
private:
	void fAddress( const std::string& inIP, const uint16_t& inPort );
};

