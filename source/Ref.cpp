#include "Ref.h"

namespace GAS
{

	Ref::Ref()
		: reference_count_{ 0 }
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
}