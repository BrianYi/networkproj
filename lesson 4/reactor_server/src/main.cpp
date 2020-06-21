#include <cstdio>
#include "TcpListenerSocket.h"
#include "Dispatcher.h"
#include "TaskThread.h"


int main()
{
	
	Dispatcher* dispatcher = new Dispatcher;
	dispatcher->start( );

	long num_of_processors = sysconf( _SC_NPROCESSORS_ONLN );
	TaskThreadPool::add_thread( num_of_processors );
	
	TcpListenerSocket *tcpListenerSocket = new TcpListenerSocket;
	tcpListenerSocket->listen( SERVER_PORT_TCP, 64 );
	tcpListenerSocket->request_event( EPOLLIN | EPOLLET );

	for ( ;; )
	{
		sleep( 1000 );
	}

	delete tcpListenerSocket;
	delete dispatcher;
    return 0;
}