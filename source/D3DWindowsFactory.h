#ifndef GAS_D3DWindowsFactory_H
#define GAS_D3DWindowsFactory_H

#include "Common.h" 

#include "FactoryBase.h"

namespace GAS
{

	class D3DWindowsFactory : public FactoryBase
	{

	public:

		D3DWindowsFactory();
		MAKE_UNCOPYABLE(D3DWindowsFactory);
		virtual ~D3DWindowsFactory();

	};

}

#endif //GAS_WindowsFactor