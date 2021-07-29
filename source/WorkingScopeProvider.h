#ifndef GAS_WorkingScopeProvider_H
#define GAS_WorkingScopeProvider_H

#include "Common.h"

namespace GAS
{

	class WorkingScope;
	class WorkingScopeProvider
	{

	protected:

		virtual void onScopeSeted( WorkingScope* scope ) {};


	public:

		WorkingScopeProvider();
		WorkingScopeProvider( WorkingScope* scope );
		WorkingScopeProvider( const WorkingScopeProvider& provider );
		WorkingScopeProvider& operator= ( const WorkingScopeProvider& provider );
		virtual ~WorkingScopeProvider();

		void setScope( WorkingScope* scope );
		void setScope( WorkingScopeProvider* provider );
		WorkingScope* getScope() const;

	protected:

		std::atomic<WorkingScope*> scope_;

	};

}

#endif //GAS_WorkingScopeProvider_H