#include "FactoryBase.h"

namespace GAS
{

	FactoryBase::FactoryBase()
	{
	}

	FactoryBase::~FactoryBase()
	{
	}

	ObjectsCreator* FactoryBase::createObjectsCreator()
	{
		return new ObjectsCreator();
	}

	AutoReleasePool* FactoryBase::createAutoReleasePool()
	{
		return new AutoReleasePool();
	}

	Scheduler* FactoryBase::createScheduler()
	{
		return new Scheduler();
	}
}