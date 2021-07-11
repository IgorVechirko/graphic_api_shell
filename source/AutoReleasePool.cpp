#include "AutoReleasePool.h"

namespace GAS
{

	AutoReleasePool::AutoReleasePool()
	{
	}

	AutoReleasePool::~AutoReleasePool()
	{
		while( refs_pool_.size() )
		{
			auto ref = (*refs_pool_.cbegin());
			refs_pool_.resize( refs_pool_.size() - 1 );

			auto referencesCount = ref->getRefsCount();
			
			if ( referencesCount > 1 )
			{
				LOG_WARNING( "Ref %d still have %d references.", ref, referencesCount );
			}

			while(ref->getRefsCount())
				ref->release();

			//free object through working scope allocator
		}
	}

	void AutoReleasePool::addRef( Ref* ref )
	{
		if ( std::find( refs_pool_.begin(), refs_pool_.end(), ref ) != refs_pool_.end() )
		{
			LOG_ERROR( "Ref already exist in the pool." );
			return;
		}

		ref->retain();
		refs_pool_.push_back( ref );
	}

	void AutoReleasePool::checkAutoRelease()
	{
		for( auto it = refs_pool_.begin(); it != refs_pool_.end(); )
		{
			if( (*it)->getRefsCount() == 1 )
			{
				auto ref = (*it);
				it = refs_pool_.erase(it);

				ref->release();
				//free object through working scope allocator
			}

			++it;
		}
	}
}