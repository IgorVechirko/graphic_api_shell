#ifndef GAS_Allocator_H
#define GAS_Allocator_H

#include <stdlib.h>

#include "Common.h"

namespace GAS
{
	class Allocator
	{

	public:

		Allocator();
		virtual ~Allocator();

		MAKE_UNCOPYABLE( Allocator );

		void* allocate( size_t size );
		void deallocate( void* ptr );

	private:

		size_t allocations_count_;

	};
}


#endif //GAS_Allocator_H