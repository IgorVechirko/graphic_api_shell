#include "AutoTestsScene.h"

#include <filesystem>

#include "glm/glm.hpp"

#include "Allocator.h"
#include "Ref.h"
#include "AutoReleasePool.h"
#include "WorkingScope.h"
#include "ScopeObjectsCreator.h"
#include "DataBuff.h"
#include "Thread.h"
#include "ThreadsPool.h"
#include "TestsDelegate.h"
#include "FileUtils.h"
#include "File.h"

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
		testGlmIntegration();
		GAS::LOG_DEBUG( "" );
		testAllocator();
		GAS::LOG_DEBUG( "" );
		testAutoReleasePool();
		GAS::LOG_DEBUG( "" );
		testAutoRef();
		GAS::LOG_DEBUG( "" );
		testDataBuff();
		GAS::LOG_DEBUG( "" );
		testFileUtils();
		GAS::LOG_DEBUG( "" );
		testThread();
		GAS::LOG_DEBUG( "" );
	}

	void AutoTestsScene::testGlmIntegration()
	{
		GAS::FUNC_TRACE_DEBUG;

		glm::uvec2 vec2{ 2, 2 };

		vec2 *= 2;

		if ( vec2.x != 4 || vec2.y != 4 )
		{
			GAS::LOG_ERROR( "Glm works wrong" );
		}
	}

	void AutoTestsScene::testAllocator()
	{
		GAS::FUNC_TRACE_DEBUG;

		{
			GAS::LogTrace block_trace( "Detect leak test" );
			
			GAS::Allocator allocator;

			int* integer = static_cast<int*>(allocator.allocate(sizeof(int)));
			*integer = 4578;

			GAS::LOG_DEBUG( "Allocator must detect memmory leak" );
		}

		{
			GAS::LogTrace block_trace( "Detect no leak test" );

			GAS::Allocator allocator;

			char* data = static_cast<char*>(allocator.allocate(256));
			char string[] = { "Very long string" };
			memcpy( data, string, sizeof(string) );

			allocator.deallocate( data );

			GAS::LOG_DEBUG( "Allocator must finish without leaks" );
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

			GAS::LOG_DEBUG( "Allocator must detect more deallocation then allocation was" );
			allocator.deallocate( integer );
		}
	}

	void AutoTestsScene::testAutoReleasePool()
	{
		GAS::FUNC_TRACE_DEBUG;

		{
			GAS::LogTrace block_trace( "Detect remaining refs" );

			std::unique_ptr<GAS::AutoReleasePool> release_pool( getScope()->getFactory()->createAutoReleasePool() );

			GAS::Ref* ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );

			ref = new Ref();
			ref->retain();
			release_pool->addRef( ref );

			GAS::LOG_DEBUG( "ReleasePool must finish with detect remaining refs" );
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

			GAS::LOG_DEBUG( "ReleasePool must finish without detect remaining refs" );
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

			GAS::LOG_DEBUG( "Allocator must finish without leaks" );
		}

		{
			//need test for check how work checkAutoRelease method 
		}
	}

	void AutoTestsScene::testAutoRef()
	{
		GAS::FUNC_TRACE_DEBUG;

		{
			GAS::LogTrace block_trace( "Constructor check");

			GAS::Ref ref;
			GAS::AutoRef<Ref> autoRef( &ref );

			if ( ref.getRefsCount() != 1 )
			{
				GAS::LOG_ERROR( "AutoRef constructor works wrong" );
				return;
			}
		}

		{
			GAS::LogTrace block_trace( "Copy constructor check");

			GAS::Ref ref;
			GAS::AutoRef<Ref> autoRef( &ref );
			GAS::AutoRef<Ref> autoRefCopy( autoRef );

			if ( ref.getRefsCount() != 2 )
			{
				GAS::LOG_ERROR( "AutoRef copy constructor works wrong" );
				return;
			}
		}

		{
			GAS::LogTrace block_trace( "Move constructor check");

			GAS::Ref ref;
			auto createFunc = [&]() -> GAS::AutoRef<Ref> {
				GAS::AutoRef<Ref> autoRef(&ref);
				return autoRef;
			};

			GAS::AutoRef<Ref> autoRefCopy( std::move( createFunc() ) );

			if ( ref.getRefsCount() != 1 )
			{
				GAS::LOG_ERROR( "AutoRef move constructor works wrong" );
				return;
			}
		}

		{
			GAS::LogTrace block_trace( "Assignment operator check");

			GAS::Ref ref;
			GAS::AutoRef<Ref> autoRef(&ref);
			GAS::AutoRef<Ref> autoRefCopy(nullptr);
			autoRefCopy = autoRef;

			if ( ref.getRefsCount() != 2 )
			{
				GAS::LOG_ERROR( "AutoRef assignment operator works wrong" );
				return;
			}
		}

		{
			GAS::LogTrace block_trace( "\"operator&\" check");

			GAS::Ref ref;
			GAS::AutoRef<Ref> autoRef( &ref );

			if ( &autoRef != &ref )
			{
				GAS::LOG_ERROR( "AutoRef \"operator&\" works wrong" );
				return;
			}
		}

		{
			GAS::LogTrace block_trace( "\"reset\" method check");

			GAS::Ref ref;
			GAS::AutoRef<Ref> autoRef( &ref );
			autoRef.reset(nullptr);

			if ( ref.getRefsCount() != 0 || &autoRef != nullptr )
			{
				GAS::LOG_ERROR( "AutoRef \"reset\" method works wrong" );
				return;
			}
		}
	}

	void AutoTestsScene::testDataBuff()
	{
		GAS::FUNC_TRACE_DEBUG;
		
		GAS::DataBuff buff;

		size_t buff_size = 256;
		buff.allocBuff(buff_size);

		if( buff.getBuffSize() != buff_size )
		{
			GAS::LOG_ERROR( "Wrong buffer size" );
			return;
		}

		if( buff.getDataSize() != 0 )
		{
			GAS::LOG_ERROR( "Buffer has wrong data size" );
			return;
		}

		if ( ( buff.getBuff() + buff_size/2 != buff.getBuff( buff_size/2 ) ) ||
			 ( buff.getBuff() + 0 != buff.getBuff() ) ||
			 ( buff.getBuff() + (buff_size-1) != buff.getBuff(buff_size-1) )
			)
		{
			GAS::LOG_ERROR( "getData working wrong" );
			return;
		}

		buff.allocBuff( buff_size*2 );
		buff.deallocBuff();
		buff.allocBuff( buff_size*3 );
		buff.allocBuff( buff_size*4 );
	}
	
	void AutoTestsScene::testFileUtils()
	{
		GAS::FUNC_TRACE_DEBUG;

		auto tests_delegate = dynamic_cast<TestsDelegate*>(getScope()->getDelegate());
		if ( !tests_delegate )
		{
			GAS::LOG_ERROR( "Can't cast delegate" );
			return;
		}

		auto argc = tests_delegate->getAppArgc();
		auto argv = tests_delegate->getAppArgv();

		if ( argc <= 0 || !argv )
		{
			GAS::LOG_ERROR( "No application arguments" );
			return;
		}

		std::string application_full_name( argv[0] );
		GAS::LOG_DEBUG( "Application full name %s", application_full_name.c_str() );

		std::string invalid_file_full_name = application_full_name;
		invalid_file_full_name.resize( invalid_file_full_name.size()-1 );

		std::filesystem::path application_path(application_full_name);
		std::filesystem::path invalid_file_path(invalid_file_full_name);

		auto file_utils = getScope()->getFileUtils();

		{
			auto invalid_file = file_utils->getFile(invalid_file_path);
			if( &invalid_file )
			{
				GAS::LOG_ERROR( "If file doesn't exist fileUtils must return nullptr file" );
				return;
			}
		}

		{
			auto invalid_file = file_utils->cacheFile(invalid_file_path);
			if( &invalid_file )
			{
				GAS::LOG_ERROR( "If file doesn't exist fileUtils must return nullptr file" );
				return;
			}

			invalid_file = file_utils->getCachedFile( invalid_file_path );
			if( &invalid_file )
			{
				GAS::LOG_ERROR( "If file doesn't exist fileUtils must return nullptr file" );
				return;
			}
		}

		{
			auto app_file = file_utils->getFile( application_path );
			if ( !&app_file )
			{
				GAS::LOG_ERROR( "Can't file existing file" );
				return;
			}
		}

		{
			auto app_file = file_utils->cacheFile( application_path );
			if ( !&app_file )
			{
				GAS::LOG_ERROR( "Can't cache existing file" );
				return;
			}

			app_file = file_utils->getCachedFile( application_path );
			if (!&app_file)
			{
				GAS::LOG_ERROR( "Existing file wasn't chache." );
				return;
			}

			file_utils->uncacheFile( application_path );
		}

		{
			auto app_file = file_utils->getFile( application_path );

			if ( !app_file->open() )
			{
				GAS::LOG_ERROR( "Can't open existing file" );
				return;
			}

			if( !app_file->isOpen() )
			{
				GAS::LOG_ERROR( "Opened file must return true" );
				return;
			}

			GAS::LOG_DEBUG( "File must gen warning" );
			if( app_file->open() )
			{
				GAS::LOG_ERROR( "Already opened file can't return true from open" );
				return;
			}

			app_file->close();
			
			if( app_file->isOpen() )
			{
				GAS::LOG_ERROR( "Close file can't return true" );
				return;
			}

			GAS::LOG_DEBUG( "File must gen warning" );
			app_file->close();
		}
	}

	void AutoTestsScene::testThread()
	{
		GAS::FUNC_TRACE_DEBUG;

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

			GAS::LOG_DEBUG( "Thread must gen warning it can't be executing again" );

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

			GAS::LOG_DEBUG( "Routine must print to output few times" );

			thread->executeRoutine( threadRoutine );

			std::this_thread::sleep_for( std::chrono::milliseconds(100) );

			waitRoutineStarExecute.get_future().get();

			thread->stopSync();
		}
	}
}