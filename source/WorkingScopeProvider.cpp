#include "WorkingScopeProvider.h"

namespace GAS
{

	WorkingScopeProvider::WorkingScopeProvider()
		: scope_{ nullptr }
	{
	}

	WorkingScopeProvider::WorkingScopeProvider( WorkingScope* scope )
	{
		_ASSERT( scope );

		scope_ = scope;
	}

	WorkingScopeProvider::WorkingScopeProvider( const WorkingScopeProvider& provider )
	{
		scope_ = provider.scope_;
	}

	WorkingScopeProvider& WorkingScopeProvider::operator=( const WorkingScopeProvider& provider )
	{
		scope_ = provider.scope_;

		return *this;
	}

	WorkingScopeProvider::~WorkingScopeProvider()
	{
	}

	WorkingScope* WorkingScopeProvider::getScope()
	{
		return scope_;
	}

}