#pragma once
#include "PlatformHeader.h"
#include <pthread.h>

class Thread
{ 
public:
	Thread( );
	virtual ~Thread( ) 
    { 
        pthread_cond_destroy(&fCond);
        pthread_mutex_destroy(&fMutex);
    }
	int start( );
    void stop();
    void setObject(void* obj);
	virtual void* entry( ) = 0;
	uint64_t handle( );
protected:
	uint64_t fThreadId;
    bool fStop;
    void *fObj;
    pthread_cond_t fCond;
    pthread_mutex_t fMutex;
private:
	static void* _entry( void* arg );
};


