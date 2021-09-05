#include "Thread.h"

namespace GAS
{
	unsigned int Thread::ID_generator_{ 0 };


	Thread::Thread()
		: need_stop_flag_{false}
		, state_{ State::kIdle }
		, ID_{ ID_generator_++ }
	{
	}

	Thread::~Thread()
	{
		std::unique_lock state_lock(state_lock_);

		switch( state_ )
		{
			case State::kExecuting:
			{
				state_ = State::kStopping;
				need_stop_flag_ = true;
			}
			case State::kStopping:
			{
				thread_finish_signal_.wait(state_lock);
			}
			default:
				break;
		}
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

		auto executor = std::bind( &Thread::routineExecutor, this, std::placeholders::_1 );
		thread_.reset( new std::thread( executor, routine ) );

		thread_->detach();

		return true;
	}
	
	bool Thread::stopSync()
	{
		std::unique_lock state_lock(state_lock_);

		if ( state_ != State::kExecuting &&
			 state_ != State::kStopping )
		{
			auto state = state_;
			state_lock.unlock();

			LOG_WARNING( "Can't stop thread because it not in executing state. Thread state %d",
				static_cast<int>(state) );

			return false;
		}

		if( state_ != State::kStopping )
		{
			need_stop_flag_ = true;
			state_ = State::kStopping;
		}

		thread_finish_signal_.wait(state_lock);

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


		//explicitly create state_lock after routine finish 
		{
			std::unique_lock state_lock(state_lock_);

			state_ = State::kIdle;
		
			thread_finish_signal_.notify_all();
		}
	}

}