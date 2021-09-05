#ifndef GAS_Thread_H
#define GAS_Thread_H

#include "Common.h"

#include "Ref.h"

namespace GAS
{
	typedef std::atomic_bool ThreadNeedStopFlag;
	typedef std::function<void( ThreadNeedStopFlag& )> ThreadRoutine;

	class Thread final
		: public Ref
	{

	public:

		Thread();
		MAKE_UNCOPYABLE(Thread);
		virtual ~Thread();

		bool executeRoutine( ThreadRoutine routine );
		bool stopSync();
		bool stopAsync();

		unsigned int getID() const;

	private:

		void routineExecutor( ThreadRoutine routine );

	private:

		enum class State
		{
			kIdle = 0,
			kExecuting,
			kStopping
		};

		State state_;
		std::mutex state_lock_;
		std::condition_variable thread_finish_signal_;

		unsigned int ID_;

		//actually thread which is do the work
		std::unique_ptr<std::thread> thread_;
		
		// Using inside the routine to determine when execution must will be terminated.
		ThreadNeedStopFlag need_stop_flag_;

	private:

		static unsigned int ID_generator_;

	};

}


#endif //GAS_Thread_H