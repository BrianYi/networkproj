#pragma once
#include "common.h"

class EventHandler;

class Task
{ 
public:
	enum
	{
		killEvent = 0xfffffffe
	};
	Task( EventHandler *handler, uint32_t flags );
	void run( );
	uint32_t get_flags( );
	void set_flags( uint32_t flags );
	EventHandler *get_handler( );
protected:
	EventHandler *fHandler;
	uint32_t fFlags;
};


inline uint32_t Task::get_flags( )
{
	return fFlags;
}

inline void Task::set_flags( uint32_t flags )
{
	fFlags = flags;
}

inline EventHandler * Task::get_handler( )
{
	return fHandler;
}
