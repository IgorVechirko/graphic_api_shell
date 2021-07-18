#ifndef GAS_ScopeObjectsCreator_H
#define GAS_ScopeObjectsCreator_H

#include <type_traits>

#include "Common.h"
#include "Ref.h"
#include "Allocator.h"
#include "WorkingScopeProvider.h"
#include "AutoRef.h"

namespace GAS
{
	class ScopeObjectsCreator 
		: public Allocator
		, public WorkingScopeProvider
	{

	public:

		ScopeObjectsCreator();
		MAKE_UNCOPYABLE( ScopeObjectsCreator );
		virtual ~ScopeObjectsCreator();

		

		template< typename ObjType, typename... Types >
		AutoRef<ObjType> createObject( const Types&... constructArgs )
		{
			AutoRef<ObjType> ret(nullptr);

			auto mem = allocate( sizeof(ObjType) );

			if( !mem )
			{
				LOG_ERROR( "Can't allocate memory" );
				deallocate( mem );
				return nullptr;
			}

			ret.reset( new(mem) ObjType(constructArgs...) );

			//if object inherite from Ref add it too release pool
			if ( std::is_base_of<Ref, ObjType>() )
			{
				auto deallocFunc = std::bind( &Allocator::deallocate, this, std::placeholders::_1 );
				((Ref*)&ret)->setDeallocFunc( deallocFunc );
				getScope()->getReleasePool()->addRef( ((Ref*)&ret) );
			}

			//if object inherite from WorkingScopeProvider distribute working scope to him
			if ( std::is_base_of<WorkingScopeProvider, ObjType>() )
				((WorkingScopeProvider*)&ret)->setScope(this);

			return ret;
		}

		template< typename ObjType, typename Initializer, typename... InitArgsTypes >
		AutoRef<ObjType> createAndInitObj( Initializer initializer, const InitArgsTypes&... initArgs )
		{
			auto ret = createObject<ObjType>();

			if ( !&ret )
			{
				return nullptr;
			}

			if( !(&ret->*initializer)( initArgs... ) )
			{
				if ( !std::is_base_of<Ref, ObjType>() )
				{
					destroyObj( &ret );
				}

				ret.reset(nullptr);
			}
			
			return ret;
		}

		template< typename ObjType >
		void destroyObj( ObjType* ptr )
		{
			ptr->~ObjType();
			deallocate(ptr);
		}
	};

}


#endif // GAS_ObjectsCreator_H
