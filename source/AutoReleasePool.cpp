#include "AutoReleasePool.h"

namespace GAS
{

	AutoReleasePool::AutoReleasePool()
	{
	}

	AutoReleasePool::~AutoReleasePool()
	{
		for( int ref_indx = 0; ref_indx < refs_pool_.size(); ++ref_indx )
		{
			auto ref = refs_pool_[ref_indx];

			auto referencesCount = ref->getRefsCount();
			
			if ( referencesCount > 1 )
			{
				LOG_WARNING( "Ref %p still have %d references.", ref, referencesCount );
			}

			while(ref->getRefsCount())
				ref->release();

			auto deallocateFunc = ref->getDeallocFunc();

			ref->~Ref();

			if ( deallocateFunc )
				deallocateFunc(ref);
			else
				delete ref;
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