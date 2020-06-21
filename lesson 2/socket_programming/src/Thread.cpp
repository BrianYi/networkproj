#include "Thread.h"

Thread::Thread( )
{
	fThreadId = -1;
    fStop = false;
    fObj = nullptr;
}

int Thread::start( )
{
	int err = pthread_create( &fThreadId, nullptr, _entry, ( void * ) this );
	return err;
}

void Thread::stop()
{
    pthread_mutex_lock(&fMutex);
    fStop = true;
    pthread_cond_signal(&fCond);
    pthread_mutex_unlock(&fMutex);
}

uint64_t Thread::handle( )
{
	return fThreadId;
}

void* Thread::_entry( void* arg )
{
	Thread* ptrThread = ( Thread * ) arg;
	ptrThread->entry( );
	return nullptr;
}


