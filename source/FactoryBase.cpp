#include "FactoryBase.h"

namespace GAS
{

	FactoryBase::FactoryBase()
	{
	}

	FactoryBase::~FactoryBase()
	{
	}

	ScopeObjectsCreator* FactoryBase::createObjectsCreator()
	{
		return new ScopeObjectsCreator();
	}

	AutoReleasePool* FactoryBase::createAutoReleasePool()
	{
		return new AutoReleasePool();
	}

	Scheduler* FactoryBase::createScheduler()
	{
		return new Scheduler();
	}

	FileUtils* FactoryBase::createFileUtils()
	{
		return new FileUtils();
	}
}