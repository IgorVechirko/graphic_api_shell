#ifndef GAS_Ref_H
#define GAS_Ref_H

#include "Common.h"


namespace GAS
{
	class Ref;
	typedef std::function<void(void*)> deallocFunc;

	class Ref
	{

	public:
		
		Ref();
		MAKE_UNCOPYABLE(Ref);
		virtual ~Ref();
		

		void release();
		void retain();

		unsigned int getRefsCount() const;

		void setDeallocFunc( deallocFunc dealloc_func );
		deallocFunc getDeallocFunc() const;

	private:

		std::atomic<unsigned int> reference_count_;

		deallocFunc dealloc_func_;

	};

}

#endif //GAS_Ref_H