#pragma once
#include "common.h"
#include "Socket.h"

class EventHandler: public Socket
{ 
public:
	EventHandler( int32_t inSocketType, int32_t inProtocol, IOType inIOType );
	virtual ~EventHandler( );
	virtual void request_event( uint32_t events );
 	uint32_t get_events( );
 	//void set_event( struct epoll_event event );
	virtual int32_t handle_event(uint32_t flags ) { return 0; };
	virtual void kill_event( );
protected:
	uint32_t fEvents;
};

inline uint32_t EventHandler::get_events( )
{
	return fEvents;
}
