#ifndef GAS_WorkingScopeProvider_H
#define GAS_WorkingScopeProvider_H

#include "Common.h"
//#include "WorkingScope.h"

namespace GAS
{

	class WorkingScope;
	class WorkingScopeProvider
	{

	protected:


	public:

		WorkingScopeProvider();
		WorkingScopeProvider( WorkingScope* scope );
		WorkingScopeProvider( const WorkingScopeProvider& provider );
		WorkingScopeProvider& operator= ( const WorkingScopeProvider& provider );
		virtual ~WorkingScopeProvider();

		WorkingScope* getScope();

	protected:

		WorkingScope* scope_;

	};

}

#endif //GAS_WorkingScopeProvider_H