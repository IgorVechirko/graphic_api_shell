#ifndef GAS_ThreadsPool_H
#define GAS_ThreadsPool_H

#include "Common.h"

#include "WorkingScopeProvider.h"
#include "Thread.h"
#include "AutoRef.h"

namespace GAS
{

	class ThreadsPool
		: public WorkingScopeProvider
	{

	public:

		ThreadsPool();
		MAKE_UNCOPYABLE( ThreadsPool );
		virtual ~ThreadsPool();

		AutoRef<Thread> createThread();
		void removeThread( Thread* thread );
		void removeThread( unsigned int thread_id );

		AutoRef<Thread> getThreadByID( unsigned int thread_id ) const;

	private:

		std::vector<Thread*> threads_;

	};

}


#endif //GAS_ThreadsPool_H