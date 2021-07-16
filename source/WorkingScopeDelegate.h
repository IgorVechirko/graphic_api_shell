#ifndef GAS_WorkingScopeDelegate_H
#define GAS_WorkingScopeDelegate_H

#include "Common.h"

#include "FactoryBase.h"

namespace GAS
{

	class WorkingScope;
	class WorkingScopeDelegate
	{

	public:

		WorkingScopeDelegate(){}
		virtual ~WorkingScopeDelegate(){};

		virtual FactoryBase* createFactoryHook( WorkingScope* scope ){ return nullptr; };

	};

}

#endif// GAS_WorkingScopeDelegate_H