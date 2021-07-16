#ifndef GAS_Scheduler_H
#define GAS_Scheduler_H

#include "Common.h"

#include "WorkingScopeProvider.h"

namespace GAS
{

	typedef std::function<void(float)> UpdateFunc;

	class Scheduler
		: public WorkingScopeProvider
	{

	public:

		Scheduler();
		MAKE_UNCOPYABLE(Scheduler)
		virtual ~Scheduler();

		void addUpdateFunc( UpdateFunc func, void* target );
		void delUpdateFunc( void* target );

	private:

		struct sUpdateRoutine
		{
			void* target_;
			UpdateFunc func_;

			sUpdateRoutine()
				: sUpdateRoutine(nullptr, nullptr)
			{
			}

			sUpdateRoutine( UpdateFunc func, void* target )
				: target_{ target }
				, func_{ func }
			{
			}
		};

		std::chrono::time_point<std::chrono::steady_clock> last_tick_time_;

		std::vector<sUpdateRoutine> update_routines_;
	};

}


#endif //GAS_Scheduler_H