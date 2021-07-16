#include "WorkingScope.h"


namespace GAS
{

	WorkingScope::WorkingScope()
		: WorkingScope(nullptr)
	{
	}

	WorkingScope::WorkingScope( WorkingScopeDelegate* scope_delegate )
	{
		// in any way create delegate to prevent in future pointer checking
		delegate_.reset( scope_delegate ? scope_delegate : new WorkingScopeDelegate() );

		auto factory = delegate_->createFactoryHook(this);
		factory_.reset( factory ? factory : createFactory() );

		creator_.reset( factory_->createObjectsCreator() );
		creator_->setScope(this);

		auto_release_pool_.reset( factory_->createAutoReleasePool() );
		auto_release_pool_->setScope(this);

		scheduler_.reset( factory_->createScheduler() );
		scheduler_->setScope(this);
	}

	WorkingScope::~WorkingScope()
	{
	}

	int WorkingScope::run()
	{
		return 0;
	}
	
	FactoryBase* WorkingScope::getFactory()
	{
		return  factory_.get();
	}

	ObjectsCreator* WorkingScope::getCreator()
	{
		return creator_.get();
	}

	AutoReleasePool* WorkingScope::getReleasePool()
	{
		return auto_release_pool_.get();
	}

	Scheduler* WorkingScope::getScheduler()
	{
		return scheduler_.get();
	}
}