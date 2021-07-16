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

		auto factory = delegate_->createFactoryHook();
		factory_.reset( factory ? factory : createFactory() );

		creator_.reset( factory_->createObjectsCreator() );

		auto_release_pool_.reset( factory_->createAutoReleasePool() );

		scheduler_.reset( factory_->createScheduler() );
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