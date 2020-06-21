#include "Address.h"

Address::Address( )
{
	fAddress( "0.0.0.0", 0 );
}


Address::Address( const uint16_t& inPort )
{
	fAddress( "0.0.0.0", inPort );
}

Address::Address( const std::string& inIP, const uint16_t& inPort )
{
	fAddress( inIP, inPort );
}

Address::Address( struct sockaddr_in inSockAddr )
{
	fAddress( ::inet_ntoa( inSockAddr.sin_addr ), inSockAddr.sin_port );
}

Address::~Address( )
{ }

std::string Address::getIP( ) const
{
	return ::inet_ntoa( this->sin_addr );
}

void Address::setIP( const std::string& inIP )
{
	uint32_t address = ::inet_addr( inIP.c_str( ) );
	if ( address == INADDR_NONE )
	{
		printf( "Invalid ip address!\n" );
	}
	else
	{
		this->sin_addr.s_addr = address;
	}
}

uint16_t Address::getPort( ) const
{
	return ntohs( this->sin_port );
}

void Address::setPort( const uint16_t& inPort )
{
	this->sin_port = htons( inPort );
}

void Address::fAddress( const std::string& inIP, const uint16_t& inPort )
{
	this->sin_family = AF_INET;
	this->setIP( inIP );
	this->setPort( inPort );
}
