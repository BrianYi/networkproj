/*
 * Copyright (C) 2020 BrianYi, All rights reserved
 */
#pragma once
#include "PlatformHeader.h"

class Address : public sockaddr_in
{
public:
	Address( );
	Address( const uint16_t& inPort );
	Address( const std::string& inIP, const uint16_t& inPort );
	Address( struct sockaddr_in inSockAddr );
	~Address( );
	std::string ip( ) const;
	void set_ip( const std::string& inIP );
	uint16_t port( ) const;
	void set_port( const uint16_t& inPort );
private:
	void _address( const std::string& inIP, const uint16_t& inPort );
};

