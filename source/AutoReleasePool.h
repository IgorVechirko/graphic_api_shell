#ifndef GAS_AutoReleasePool_H
#define GAS_AutoReleasePool_H

#include "Common.h"
#include "Ref.h"

namespace GAS
{

	class AutoReleasePool
	{

	public:

		AutoReleasePool();
		virtual ~AutoReleasePool();
		MAKE_UNCOPYABLE(AutoReleasePool);

		void addRef( Ref* ref );

		void checkAutoRelease();

	private:

		std::vector<Ref*> refs_pool_;

	};

}


#endif //GAS_AutoReleasePool_H