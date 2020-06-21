#pragma once
#include "Thread.h"
#include "EventHandler.h"
#include "Task.h"
#include <sys/epoll.h>
#include <unordered_map>
#include <mutex>
class Dispatcher :
	public Thread
{ 
public:
	Dispatcher( );
	virtual ~Dispatcher( ) { };
	void* entry( );
	void handle_events( );
	static void register_handler( int fd, EventHandler* handler);
	static void remove_handler( int fd );
private:
	static void push_to_thread( Task *task );
	static int sFdEpoll;
	static int sMaxevents;
	static size_t sThreadPicker;
	static std::mutex mx;
	static std::unordered_map<int, EventHandler*> sHandlerTable;
};

