#include "WorkingScopeProvider.h"

namespace GAS
{

	WorkingScopeProvider::WorkingScopeProvider()
		: scope_{ nullptr }
	{
	}

	WorkingScopeProvider::WorkingScopeProvider( WorkingScope* scope )
	{
		assert( scope );

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

	void WorkingScopeProvider::setScope( WorkingScope* scope )
	{
		scope_ = scope;
	}

	void WorkingScopeProvider::setScope( WorkingScopeProvider* provider )
	{
		scope_ = provider->getScope();
	}

	WorkingScope* WorkingScopeProvider::getScope()
	{
		return scope_;
	}

}