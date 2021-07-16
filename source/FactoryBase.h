#ifndef GAS_FactoryBase_H
#define GAS_FactoryBase_H

#include "Common.h"

#include "ObjectsCreator.h"
#include "AutoReleasePool.h"
#include "Scheduler.h"

namespace GAS
{

	class FactoryBase
	{

	public:

		FactoryBase();
		MAKE_UNCOPYABLE( FactoryBase );
		virtual ~FactoryBase();

		ObjectsCreator* createObjectsCreator();

		AutoReleasePool* createAutoReleasePool();

		Scheduler* createScheduler();

	};


}



#endif //GAS_FactoryBase_H 