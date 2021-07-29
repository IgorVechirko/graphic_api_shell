#ifndef GAS_WorkingScope_H
#define GAS_WorkingScope_H

#include "Common.h"

#include "AutoRef.h"

#include "WorkingScopeDelegate.h"
#include "FactoryBase.h"
#include "ScopeObjectsCreator.h"
#include "AutoReleasePool.h"
#include "Scheduler.h"
#include "FileUtils.h"
#include "SceneBase.h"
#include "ThreadsPool.h"

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

		FactoryBase* getFactory() const;

		ScopeObjectsCreator* getCreator() const;

		AutoReleasePool* getReleasePool() const;

		Scheduler* getScheduler() const;

		FileUtils* getFileUtils() const;

		ThreadsPool* getThreadsPool() const;

		void setScene( SceneBase* scene );
		AutoRef<SceneBase> getScene() const;

	private:

		FactoryBase* createFactory();

	private:

		std::unique_ptr<WorkingScopeDelegate> delegate_;

		std::unique_ptr<FactoryBase> factory_;

		std::unique_ptr<ScopeObjectsCreator> creator_;

		std::unique_ptr<AutoReleasePool> auto_release_pool_;

		std::unique_ptr<Scheduler> scheduler_;

		std::unique_ptr<FileUtils> file_utils_;

		std::unique_ptr<ThreadsPool> threads_pool_;

		SceneBase* scene_;
	};

}

#endif //GAS_WorkingScope_H