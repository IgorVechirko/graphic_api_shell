#include "Ref.h"

namespace GAS
{

	Ref::Ref()
		: reference_count_{ 0 }
		, dealloc_func_{ nullptr }
	{
	}

	Ref::~Ref()
	{
	}


	void Ref::release()
	{
		if( reference_count_ == 0 )
		{
			LOG_ERROR( "Too many release() calls." );
			return;
		}

		--reference_count_;
	}
	
	void Ref::retain()
	{
		++reference_count_;
	}

	unsigned int Ref::getRefsCount()
	{
		return reference_count_;
	}

	void Ref::setDeallocFunc( deallocFunc dealloc_func )
	{
		dealloc_func_ = dealloc_func;
	}

	deallocFunc Ref::getDeallocFunc()
	{
		return dealloc_func_;
	}
}