/*
 * Copyright (C) 2020 BrianYi, All rights reserved
 */
#include "Address.h"

Address::Address( )
{
	_address( "0.0.0.0", 0 );
}


Address::Address( const uint16_t& inPort )
{
	_address( "0.0.0.0", inPort );
}

Address::Address( const std::string& inIP, const uint16_t& inPort )
{
	_address( inIP, inPort );
}

Address::Address( struct sockaddr_in inSockAddr )
{
	_address( ::inet_ntoa( inSockAddr.sin_addr ), inSockAddr.sin_port );
}

Address::~Address( )
{ }

std::string Address::ip( ) const
{
	return ::inet_ntoa( this->sin_addr );
}

void Address::set_ip( const std::string& inIP )
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

uint16_t Address::port( ) const
{
	return ntohs( this->sin_port );
}

void Address::set_port( const uint16_t& inPort )
{
	this->sin_port = htons( inPort );
}

void Address::_address( const std::string& inIP, const uint16_t& inPort )
{
	this->sin_family = AF_INET;
	this->set_ip( inIP );
	this->set_port( inPort );
}
