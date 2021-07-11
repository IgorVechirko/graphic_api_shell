#include "Allocator.h"

namespace GAS
{
	Allocator::Allocator()
		: allocations_count_{ 0 }
	{
	}

	Allocator::~Allocator()
	{
		if( allocations_count_ != 0 )
		{
			LOG_ERROR( "Memmory leaks." );
		}
	}

	void* Allocator::allocate( size_t size )
	{
		auto ptr = malloc(size);
		++allocations_count_;
		return ptr;
	}

	void Allocator::deallocate( void* ptr )
	{
		if( allocations_count_ == 0 )
		{
			LOG_ERROR( "Deallocations calls more times then allocations." );
			return;
		}
		--allocations_count_;
		free(ptr);
	}
}