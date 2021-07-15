#ifndef GAS_WindowsFactory_H
#define GAS_WindowsFactory_H

#include "Common.h" 

#include "FactoryBase.h"

namespace GAS
{

	class WindowsFactory : public FactoryBase
	{

	public:

		WindowsFactory();
		MAKE_UNCOPYABLE(WindowsFactory);
		virtual ~WindowsFactory();

	};

}

#endif //GAS_WindowsFactor