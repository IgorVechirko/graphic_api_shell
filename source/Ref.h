#ifndef GAS_Ref_H
#define GAS_Ref_H

#include "Common.h"

namespace GAS
{
	class Ref
	{

	public:
		
		Ref();
		MAKE_UNCOPYABLE(Ref);
		virtual ~Ref();
		

		void release();
		void retain();

		unsigned int getRefsCount();

	private:

		unsigned int reference_count_;

	};

}

#endif //GAS_Ref_H