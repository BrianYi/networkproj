#include "EventHandler.h"
#include "Dispatcher.h"

EventHandler::EventHandler( int32_t inSocketType, int32_t inProtocol, IOType inIOType ):
	Socket(inSocketType, inProtocol, inIOType )
{
	fEvents = 0;
}

EventHandler::~EventHandler( )
{
}

void EventHandler::request_event( uint32_t events )
{
	if ( fEvents & events )
		return;
	fEvents |= events;
	Dispatcher::register_handler( fSocket, this );
}

void EventHandler::kill_event( )
{
	Dispatcher::remove_handler( this->fSocket );
}

// 
// void EventHandler::set_event( struct epoll_event event )
// {
// 	fEvent = event;
// }

// Task * EventHandler::get_handler( )
// {
// 	return fTask;
// }
