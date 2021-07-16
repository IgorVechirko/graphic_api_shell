#ifndef GAS_WorkingScope_H
#define GAS_WorkingScope_H

#include "Common.h"

#include "WorkingScopeDelegate.h"
#include "FactoryBase.h"
#include "ObjectsCreator.h"
#include "AutoReleasePool.h"
#include "Scheduler.h"

namespace GAS
{	

	class WorkingScope
	{

	public:

		WorkingScope();
		WorkingScope( WorkingScopeDelegate* scope_delegate );
		MAKE_UNCOPYABLE(WorkingScope);
		virtual ~WorkingScope();

		int run();

		FactoryBase* getFactory();

		ObjectsCreator* getCreator();

		AutoReleasePool* getReleasePool();

		Scheduler* getScheduler();

	private:

		FactoryBase* createFactory();

	private:

		std::unique_ptr<WorkingScopeDelegate> delegate_;

		std::unique_ptr<FactoryBase> factory_;

		std::unique_ptr<ObjectsCreator> creator_;

		std::unique_ptr<AutoReleasePool> auto_release_pool_;

		std::unique_ptr<Scheduler> scheduler_;
	};

}

#endif //GAS_WorkingScope_H