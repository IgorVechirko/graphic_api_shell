#ifndef GAS_GASStartClass_H
#define GAS_GASStartClass_H

#include "Common.h"


namespace GAS
{

	class GASStartClass
	{

	public:

		GASStartClass();
		virtual ~GASStartClass();

		MAKE_UNCOPYABLE(GASStartClass);
		//not copyable class
		/*GASStartClass( const GASStartClass& inst ) = delete;
		GASStartClass( GASStartClass&& inst ) = delete;
		GASStartClass& operator= (const GASStartClass& inst ) = delete;*/

		void run();

	};

}

#endif //GAS_GASStartClass_H
