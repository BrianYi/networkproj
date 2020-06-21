#include "Thread.h"

Thread::Thread( )
{
	fThreadId = -1;
}

int Thread::start( )
{
	int err = pthread_create( &fThreadId, nullptr, _entry, ( void * ) this );
	return err;
}

void Thread::sleep( uint32_t ms )
{
	::usleep( 1000 * ms );
}

uint64_t Thread::get_handle( )
{
	return fThreadId;
}

void* Thread::_entry( void* arg )
{
	Thread* ptrThread = ( Thread * ) arg;
	ptrThread->entry( );
	return nullptr;
}
