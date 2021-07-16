#include "WorkingScope.h"

#include "D3DWindowsFactory.h"

namespace GAS
{

	FactoryBase* WorkingScope::createFactory()
	{
		auto factory = new D3DWindowsFactory();
		factory->setScope( this );
		
		return factory;
	}

}