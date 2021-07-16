#include "Scheduler.h"

namespace GAS
{

	Scheduler::Scheduler()
	{
		last_tick_time_ = std::chrono::steady_clock::now();
	}

	Scheduler::~Scheduler()
	{
	}

	void Scheduler::addUpdateFunc( UpdateFunc func, void* target )
	{
		if ( func && target )
		{
			for( auto routineIt = update_routines_.begin(); routineIt != update_routines_.end(); ++routineIt )
			{
				if ( (*routineIt).target_ == target )
				{
					return;
				}
			}

			update_routines_.push_back( sUpdateRoutine{ target, func } );
		}
	}
		
	void Scheduler::delUpdateFunc( void* target )
	{
		if ( target )
		{
			for( auto routineIt = update_routines_.begin(); routineIt != update_routines_.end(); ++routineIt )
			{
				if ( (*routineIt).target_ == target )
				{
					update_routines_.erase( routineIt );
					break;
				}
			}
		}
	}

}