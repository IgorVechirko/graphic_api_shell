#include "WorkingScope.h"

#include "WindowsFactory.h"

namespace GAS
{

	FactoryBase* WorkingScope::createFactory()
	{
		return new WindowsFactory();
	}
}