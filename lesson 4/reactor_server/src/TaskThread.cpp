#include "TaskThread.h"

std::vector<TaskThread*> TaskThreadPool::sTaskThreadArry;

void* TaskThread::entry( )
{
	for ( ;; )
	{
		if ( fTaskQueue.empty( ) )
		{
			sleep( 10 );
			continue;
		}

		std::unique_lock<std::mutex> lock( mx );
		Task *task = fTaskQueue.front( );;
		fTaskQueue.pop( );
		if ( task->get_flags() & Task::killEvent )
		{
			EventHandler* handler = task->get_handler( );
#ifdef _DEBUG
			printf( "threadID=%llu, delete handler=%x, fTaskQueue.size=%d\n",
					this->get_handle( ),
					handler,
					this->fTaskQueue.size( ));
#endif // _DEBUG
			delete handler;
		}
		lock.unlock( );

		task->run( );

		delete task;
	}
	return nullptr;
}

void TaskThread::push( Task* task )
{
	std::unique_lock<std::mutex> lock( mx );
	fTaskQueue.push( task );
}

size_t TaskThreadPool::add_thread( int32_t numThread )
{
	for ( int32_t i = 0; i < numThread; ++i )
	{
		TaskThread* ptrTaskThread = new TaskThread( );
		sTaskThreadArry.push_back( ptrTaskThread );
		ptrTaskThread->start( );
	}
	return sTaskThreadArry.size( );
}

TaskThread* TaskThreadPool::get_thread( uint32_t index )
{
	if ( index < 0 || index >= sTaskThreadArry.size( ) )
		return nullptr;
	return sTaskThreadArry[ index ];
}

size_t TaskThreadPool::get_num_threads( )
{
	return sTaskThreadArry.size( );
}
