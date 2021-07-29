#include "Thread.h"

namespace GAS
{
	unsigned int Thread::ID_generator_{ 0 };


	Thread::Thread()
		: need_stop_flag_{false}
		, state_{ State::kIdle }
		, thread_has_finished_signal_{ 1 }
		, ID_{ ID_generator_++ }
	{
	}

	Thread::~Thread()
	{
		stopSync();
	}

	bool Thread::executeRoutine( ThreadRoutine routine )
	{
		std::unique_lock state_lock(state_lock_);

		if ( state_ != State::kIdle )
		{
			auto state = state_;
			state_lock.unlock();

			LOG_WARNING( "Can't execute routine because thread already doing some work. Thread state %d",
				static_cast<int>(state) );
			
			return false;
		}

		need_stop_flag_ = false;
		state_ = State::kExecuting;

		//Countdown semaphore to 0
		thread_has_finished_signal_.acquire();

		auto executor = std::bind( &Thread::routineExecutor, this, std::placeholders::_1 );
		thread_.reset( new std::thread( executor, routine ) );

		thread_->detach();

		return true;
	}
	
	bool Thread::stopSync()
	{
		std::unique_lock state_lock(state_lock_);

		if ( state_ != State::kExecuting )
		{
			auto state = state_;
			state_lock.unlock();

			LOG_WARNING( "Can't stop thread because it not in executing state. Thread state %d",
				static_cast<int>(state) );

			return false;
		}

		need_stop_flag_ = true;
		state_ = State::kStopping;

		state_lock.unlock();

		//Wait when semaphore will be released
		thread_has_finished_signal_.acquire();

		//Release semaphore for roll it to start state
		thread_has_finished_signal_.release();

		return true;
	}
	
	bool Thread::stopAsync()
	{
		std::unique_lock state_lock(state_lock_);

		if ( state_ != State::kExecuting )
		{
			auto state = state_;
			state_lock.unlock();

			LOG_WARNING( "Can't stop thread because it not in executing state. Thread state %d",
				static_cast<int>(state) );

			return false;
		}

		need_stop_flag_ = true;
		state_ = State::kStopping;

		return true;
	}
	
	unsigned int Thread::getID() const
	{
		return ID_;
	}

	void Thread::routineExecutor( ThreadRoutine routine )
	{
		routine(need_stop_flag_);

		std::lock_guard state_lock(state_lock_);

		state_ = State::kIdle;
		
		//Release semaphore to notify that thread finish execution
		thread_has_finished_signal_.release();
	}

}