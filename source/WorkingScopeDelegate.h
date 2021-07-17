#ifndef GAS_WorkingScopeDelegate_H
#define GAS_WorkingScopeDelegate_H

#include "Common.h"

#include "WorkingScopeProvider.h"
#include "FactoryBase.h"

namespace GAS
{

	class WorkingScope;
	class WorkingScopeDelegate
		: public WorkingScopeProvider
	{

	public:

		WorkingScopeDelegate(){}
		virtual ~WorkingScopeDelegate(){};

		virtual FactoryBase* createFactoryHook( WorkingScope* scope ){ return nullptr; };
		virtual void onBeforeRun(){};

	};

}

#endif// GAS_WorkingScopeDelegate_H