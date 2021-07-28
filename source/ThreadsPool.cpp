#include "ThreadsPool.h"

#include "WorkingScope.h"

namespace GAS
{

	ThreadsPool::ThreadsPool()
	{
	}

	ThreadsPool::~ThreadsPool()
	{
		for( auto thread : threads_ )
		{
			thread->release();
		}
	}

	AutoRef<Thread> ThreadsPool::createThread()
	{
		auto new_thread = getScope()->getCreator()->createObject<Thread>();

		new_thread->retain();
		threads_.push_back( &new_thread );

		return new_thread;
	}

	void ThreadsPool::removeThread( Thread* thread )
	{
		for( auto threadIt = threads_.begin(); threadIt != threads_.end(); ++threadIt )
		{
			if ( (*threadIt) == thread )
			{
				threadIt = threads_.erase(threadIt);
				thread->release();

				return;
			}
		}
	}

	void ThreadsPool::removeThread( unsigned int thread_id )
	{
		for( auto threadIt = threads_.begin(); threadIt != threads_.end(); ++threadIt )
		{
			if ( (*threadIt)->getID() == thread_id )
			{
				auto thread = (*threadIt);
				threadIt = threads_.erase(threadIt);
				thread->release();

				return;
			}
		}
	}

	AutoRef<Thread> ThreadsPool::getThreadByID( unsigned int thread_id )
	{
		for( auto thread : threads_ )
		{
			if ( thread->getID() == thread_id )
			{
				return thread;
			}
		}

		return nullptr;
	}
}