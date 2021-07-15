#ifndef GAS_ObjectsCreator_H
#define GAS_ObjectsCreator_H

#include "Common.h"
#include "Allocator.h"

namespace GAS
{
	class ObjectsCreator : public Allocator
	{

	public:

		ObjectsCreator();
		MAKE_UNCOPYABLE( ObjectsCreator );
		virtual ~ObjectsCreator();

		

		template< typename ObjType, typename... Types >
		ObjType* createObject( const Types&... contructArgs )
		{
			auto mem = allocate( sizeof(ObjType) );

			if( !mem )
			{
				LOG_ERROR( "Can't allocate memory" );
				deallocate( mem );
				return nullptr;
			}

			ObjType* ret = new(mem) ObjType(contructArgs...);

			return ret;
		}

		template< typename ObjType, typename Initializer, typename... InitArgsTypes >
		ObjType* createAndInitObj( Initializer initializer, const InitArgsTypes&... initArgs )
		{
			auto ret = createObject<ObjType>();

			if ( !ret )
			{
				return nullptr;
			}

			if( !(ret->*initializer)( initArgs... ) )
			{
				destroyObj( ret );
				return nullptr;
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
