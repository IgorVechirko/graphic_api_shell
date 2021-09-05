#include "AutoTestsScene.h"

#include "Allocator.h"
#include "Ref.h"
#include "AutoReleasePool.h"
#include "WorkingScope.h"
#include "ScopeObjectsCreator.h"
#include "DataBuff.h"
#include "Thread.h"
#include "ThreadsPool.h"

namespace Tests
{

	AutoTestsScene::AutoTestsScene()
	{
	}

	AutoTestsScene::~AutoTestsScene()
	{
	}

	void AutoTestsScene::onInit()
	{
		testAllocator();
		GAS::LOG_ERROR( "" );
		testAutoReleasePool();
		GAS::LOG_ERROR( "" );
		testAutoRef();
		GAS::LOG_ERROR( "" );
		testDataBuff();
		GAS::LOG_ERROR( "" );
		testThread();
		GAS::LOG_ERROR( "" );
	}

	void AutoTestsScene::testAllocator()
	{
		GAS::FUNC_TRACE;

		{
			GAS::LogTrace block_trace( "Detect leak test" );
			
			GAS::Allocator allocator;

			int* integer = static_cast<int*>(allocator.allocate(sizeof(int)));
			*integer = 4578;

			GAS::LOG_WARNING( "Allocator must detect memmory leak" );
		}

		{
			GAS::LogTrace block_trace( "Detect no leak test" );

			GAS::Allocator allocator;

			char* data = static_cast<char*>(allocator.allocate(256));
			char string[] = { "Very long string" };
			memcpy( data, string, sizeof(string) );

			allocator.deallocate( data );

			GAS::LOG_WARNING( "Allocator must finish without leaks" );
		}

		{
			GAS::LogTrace block_trace( "Detect extra deallocation" );

			GAS::Allocator allocator;

			char* data = static_cast<char*>(allocator.allocate(256));
			char string[] = { "Very long string" };
			memcpy( data, string, sizeof(string) );

			allocator.deallocate( data );

			int* integer = new int;
			*integer = 4578;

			GAS::LOG_WARNING( "Allocator must detect more deallocation then allocation was" );
			allocator.deallocate( integer );
		}
	}

	void AutoTestsScene::testAutoReleasePool()
	{
		GAS::FUNC_TRACE;

		{
			GAS::LogTrace block_trace( "Detect remaining refs" );

			std::unique_ptr<GAS::AutoReleasePool> release_pool( getScope()->getFactory()->createAutoReleasePool() );

			GAS::Ref* ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );

			ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );

			GAS::LOG_WARNING( "ReleasePool must finish with detect remaining refs" );
		}

		{
			GAS::LogTrace block_trace( "Detect no remaining refs" );

			std::unique_ptr<GAS::AutoReleasePool> release_pool( getScope()->getFactory()->createAutoReleasePool() );

			GAS::Ref* ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );
			ref->release();

			ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );
			ref->release();

			GAS::LOG_WARNING( "ReleasePool must finish without detect remaining refs" );
		}

		{
			GAS::LogTrace block_trace( "Check refs custom deleter work" );

			GAS::Allocator allocator;
			std::unique_ptr<GAS::AutoReleasePool> release_pool( getScope()->getFactory()->createAutoReleasePool() );

			GAS::Ref* ref = new (allocator.allocate(sizeof(Ref))) Ref();
			ref->setDeallocFunc( std::bind(&GAS::Allocator::deallocate, &allocator, std::placeholders::_1 ) );
			ref->retain();
			release_pool->addRef( ref );
			ref->release();

			ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );
			ref->release();

			GAS::LOG_WARNING( "Allocator must finish without leaks" );
		}

		{
			//need test for check how work checkAutoRelease method 
		}
	}

	void AutoTestsScene::testAutoRef()
	{
		GAS::FUNC_TRACE;

		auto objRef = getScope()->getCreator()->createObject<Ref>();
		
		if ( objRef->getRefsCount() != 2 )
		{
			GAS::LOG_ERROR( "Ref object have wrong refs_count" );
			return;
		}

		auto secondRef(objRef);

		if ( objRef->getRefsCount() != 3 )
		{
			GAS::LOG_ERROR( "Ref object have wrong refs_count" );
			return;
		}

		secondRef.reset(nullptr);

		if ( objRef->getRefsCount() != 2 )
		{
			GAS::LOG_ERROR( "Ref object have wrong refs_count after call reset" );
			return;
		}

		auto func = [&]() -> GAS::AutoRef<Ref> {
			auto newRef(objRef);
			return newRef;
		};

		secondRef = func();

		if ( objRef->getRefsCount() != 3 )
		{
			GAS::LOG_ERROR( "Ref object have wrong refs_count after call move constructor" );
			return;
		}
	}

	void AutoTestsScene::testDataBuff()
	{
		GAS::FUNC_TRACE;
		
		GAS::DataBuff buff;

		size_t data_size = 256;
		buff.allocData(data_size);

		if( buff.getDataSize() != data_size )
		{
			GAS::LOG_ERROR( "Buffer has wrong data size" );
			return;
		}

		if ( ( buff.getData() + data_size/2 != buff.getData( data_size/2 ) ) ||
			 ( buff.getData() + 0 != buff.getData() ) ||
			 ( buff.getData() + (data_size-1) != buff.getData(data_size-1) )
			)
		{
			GAS::LOG_ERROR( "getData working wrong" );
			return;
		}

		buff.allocData( data_size*2 );
		buff.deallocData();
		buff.allocData( data_size*3 );
		buff.allocData( data_size*4 );
	}
	
	void AutoTestsScene::testThread()
	{
		GAS::FUNC_TRACE;

		{
			GAS::LogTrace block_trace( "Check executing state" );

			auto thread = getScope()->getCreator()->createObject<GAS::Thread>();

			std::promise<void> waitRoutineStarExecute;
			std::promise<void> waitRoutineFinishExecute;

			auto threadRoutine = [&](GAS::ThreadNeedStopFlag& stopFlag){
				waitRoutineStarExecute.set_value();

				waitRoutineFinishExecute.get_future().get();
			};

			thread->executeRoutine( threadRoutine );

			waitRoutineStarExecute.get_future().get();

			GAS::LOG_WARNING( "Thread must gen warning it can't be executin again" );

			thread->executeRoutine( threadRoutine );

			waitRoutineFinishExecute.set_value();
		}

		{
			GAS::LogTrace block_trace( "Check stopping flag work" );

			auto thread = getScope()->getCreator()->createObject<GAS::Thread>();

			std::promise<void> waitRoutineStarExecute;

			auto threadRoutine = [&](GAS::ThreadNeedStopFlag& stopFlag){
				waitRoutineStarExecute.set_value();

				int i = 1;
				while( !stopFlag )
				{
					GAS::LOG_ERROR( "%d time. Continue execute routine", i );
					std::this_thread::sleep_for( std::chrono::milliseconds(10) );
					++i;
				}
			};

			GAS::LOG_ERROR( "Routine must print to output few times" );

			thread->executeRoutine( threadRoutine );

			std::this_thread::sleep_for( std::chrono::milliseconds(100) );

			waitRoutineStarExecute.get_future().get();

			thread->stopSync();
		}
	}
}