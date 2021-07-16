#include "WorkingScope.h"

#include "D3DWindowsFactory.h"

namespace GAS
{

	FactoryBase* WorkingScope::createFactory()
	{
		return new D3DWindowsFactory();
	}
}