#ifndef GAS_FactoryBase_H
#define GAS_FactoryBase_H

#include "Common.h"

#include "WorkingScopeProvider.h"
#include "ScopeObjectsCreator.h"
#include "AutoReleasePool.h"
#include "Scheduler.h"
#include "FileUtils.h"
#include "ThreadsPool.h"

namespace GAS
{

	class FactoryBase : public WorkingScopeProvider
	{

	public:

		FactoryBase();
		MAKE_UNCOPYABLE( FactoryBase );
		virtual ~FactoryBase();

		ScopeObjectsCreator* createObjectsCreator();

		AutoReleasePool* createAutoReleasePool();

		Scheduler* createScheduler();

		FileUtils* createFileUtils();

		ThreadsPool* createThreadsPool();

	};


}



#endif //GAS_FactoryBase_H 