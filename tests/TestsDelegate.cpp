#include "TestsDelegate.h"

#include "WorkingScope.h"

//TestScenes
#include "AutoTestsScene.h"

namespace Tests
{

	TestsDelegate::TestsDelegate( int argc, char** argv )
		: current_scene_( nullptr )
		, app_argc_(argc)
		, app_argv_(argv)
	{
	}

	TestsDelegate::~TestsDelegate()
	{
		if( current_scene_ )
			current_scene_->release();
	}

	void TestsDelegate::onBeforeRun()
	{
		setupScenesCreateFunc();
		
		runNextTestScene();
	}

	int TestsDelegate::getAppArgc() const
	{
		return app_argc_;
	}

	char** TestsDelegate::getAppArgv() const
	{
		return app_argv_;
	}

	void TestsDelegate::setupScenesCreateFunc()
	{
		tests_scenes_create_funcs_[ "auto_tests" ] = std::bind( &TestsDelegate::createScene<AutoTestsScene>, this, std::placeholders::_1 );
	}

	void TestsDelegate::runNextTestScene()
	{
		if ( tests_scenes_create_funcs_.empty() )
		{
			GAS::LOG_ERROR( "There is no tests scenes" );
			return;
		}

		//if first run
		if ( !current_scene_ )
		{
			auto sceneRef = tests_scenes_create_funcs_.begin()->second( tests_scenes_create_funcs_.begin()->first );

			getScope()->setScene( &sceneRef );

			current_scene_ = &sceneRef;
			current_scene_->retain();
			return;
		}
		
		//if current scene already exist
		for( auto scene_func_it = tests_scenes_create_funcs_.begin(); scene_func_it != tests_scenes_create_funcs_ .end(); ++scene_func_it )
		{
			if ( scene_func_it->first == current_scene_->getName() )
			{
				if ( std::next(scene_func_it) != tests_scenes_create_funcs_.end() )
				{
					++scene_func_it;
				}
				else
				{
					scene_func_it = tests_scenes_create_funcs_.begin();
				}

				//here we call scene create function which is the second member of scene_func_it
				auto sceneRef = scene_func_it->second( scene_func_it->first );

				getScope()->setScene( &sceneRef );

				current_scene_->release();
				current_scene_ = &sceneRef;
				current_scene_->retain();
				return;
			}
			else
			{
				GAS::LOG_ERROR( "Can't find current scene in scenes create functions list" );
			}
		}
	}
}