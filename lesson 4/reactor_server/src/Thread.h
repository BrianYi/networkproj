#pragma once
#include "common.h"
#include <pthread.h>

class Thread
{ 
	uint64_t fThreadId;
public:
	Thread( );
	virtual ~Thread( ) { }
	int start( );
	void sleep(uint32_t ms );
	virtual void* entry( ) = 0;
	uint64_t get_handle( );
private:
	static void* _entry( void* arg );
};

