#include "Dispatcher.h"
//#include "Task.h"
#include "TaskThread.h"

int Dispatcher::sFdEpoll = epoll_create( 64 );// size is ignored
int Dispatcher::sMaxevents = 64;
size_t Dispatcher::sThreadPicker = 0;
std::unordered_map<int, EventHandler*> Dispatcher::sHandlerTable;
std::mutex Dispatcher::mx;

Dispatcher::Dispatcher( )
{
}

void* Dispatcher::entry( )
{
	handle_events( );
	return nullptr;
}

void Dispatcher::handle_events( ) // demultiplexer
{
	struct epoll_event events[sMaxevents];
	for ( ;; )
	{
		int nfds = epoll_wait( sFdEpoll, events, sMaxevents, -1 );
		if ( nfds == -1 )
		{
			printf( "epoll_wait error %d\n", errno );
			continue;
		}
		for ( int i = 0; i < nfds; ++i )
		{
			std::unique_lock<std::mutex> lock( mx );
			auto it = sHandlerTable.find( events[ i ].data.fd );
			EventHandler *handler = it->second;
			if ( handler->get_events( ) & events[i].events )
			{
				Task *task = new Task( handler, events[ i ].events );
				push_to_thread( task );
			}
		}
	}
}

void Dispatcher::register_handler( int fd, EventHandler* handler )
{
	struct epoll_event ev;
	ev.data.fd = handler->fSocket;
	ev.events = handler->get_events( );
	
	std::unique_lock<std::mutex> lock( mx );
	
	if ( epoll_ctl( sFdEpoll, EPOLL_CTL_ADD, fd, &ev ) < 0 )
	{
		printf( "epoll set insertion error: fd=%d, errno=%d\n", 
				fd,
				errno);
		return;
	}
	
	if ( !sHandlerTable.count(fd) )
	{
		sHandlerTable.insert( std::make_pair( fd, handler ) );
#ifdef _DEBUG
	printf( "insert fd=%d, event=%x, totoal fd=%d\n",
			fd,
			handler,
			sHandlerTable.size( ) );
#endif
	}
}

void Dispatcher::remove_handler( int fd )
{
	std::unique_lock<std::mutex> lock( mx );
	if ( epoll_ctl( sFdEpoll, EPOLL_CTL_DEL, fd, nullptr ) < 0 )
	{
		printf( "epoll set remove error: fd=%d, errno=%d\n", 
				fd,
				errno);
		return;
	}

	auto it = sHandlerTable.find( fd );
	if ( it == sHandlerTable.end() )
	{
#ifdef _DEBUG
		printf( "remove_handler error, don't have fd=%d\n", fd );
#endif // _DEBUG
		return;
	}

#ifdef _DEBUG
	printf( "delete fd=%d, event=%x, totoal fd=%d\n",
			it->first,
			it->second,
			sHandlerTable.size( ) );
#endif
	//ÔÚTaskThreadÖÐÉ¾³ý
	EventHandler *handler = it->second;
	Task *task = new Task( handler, Task::killEvent);
	push_to_thread( task );

	sHandlerTable.erase( it );
	close( fd );
}


inline void Dispatcher::push_to_thread( Task *task )
{
	sThreadPicker++;
	sThreadPicker %= TaskThreadPool::get_num_threads( );
	TaskThread *taskThread = TaskThreadPool::get_thread( sThreadPicker );
	taskThread->push( task );
}