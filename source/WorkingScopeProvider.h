#ifndef GAS_WorkingScopeProvider_H
#define GAS_WorkingScopeProvider_H

#include "Common.h"

namespace GAS
{

	class WorkingScope;
	class WorkingScopeProvider
	{

	protected:

		virtual void onSocpeSeted( WorkingScope* scope ) {};


	public:

		WorkingScopeProvider();
		WorkingScopeProvider( WorkingScope* scope );
		WorkingScopeProvider( const WorkingScopeProvider& provider );
		WorkingScopeProvider& operator= ( const WorkingScopeProvider& provider );
		virtual ~WorkingScopeProvider();

		void setScope( WorkingScope* scope );
		void setScope( WorkingScopeProvider* provider );
		WorkingScope* getScope();

	protected:

		WorkingScope* scope_;

	};

}

#endif //GAS_WorkingScopeProvider_H