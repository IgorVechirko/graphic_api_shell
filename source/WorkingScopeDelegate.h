#ifndef GAS_WorkingScopeDelegate_H
#define GAS_WorkingScopeDelegate_H

#include "Common.h"

#include "FactoryBase.h"

namespace GAS
{

	class WorkingScopeDelegate
	{

	public:

		WorkingScopeDelegate(){}
		virtual ~WorkingScopeDelegate(){};

		virtual FactoryBase* createFactoryHook(){ return nullptr; };

	};

}

#endif// GAS_WorkingScopeDelegate_H