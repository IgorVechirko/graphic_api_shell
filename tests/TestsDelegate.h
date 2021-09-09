#ifndef Tests_TestsDelegate_H
#define Tests_TestsDelegate_H

#include "Common.h"
#include "WorkingScopeDelegate.h"
#include "TestSceneBase.h"
#include "AutoRef.h"

namespace Tests
{

	class TestsDelegate
		: public GAS::WorkingScopeDelegate
	{

	public:

		TestsDelegate( int argc, char** argv );
		virtual ~TestsDelegate();

		virtual void onBeforeRun() override;

		int getAppArgc() const;
		char** getAppArgv() const;

	private:

		void setupScenesCreateFunc();

		void runNextTestScene();

		// To simplify types convertion through bind function
		template<typename SceneType>
		GAS::AutoRef<TestSceneBase> createScene( const std::string& name )
		{
			auto sceneRef = getScope()->getCreator()->createAndInitObj<SceneType>( &SceneType::initWithName, name );

			return &sceneRef;
		}

	private:

		int app_argc_;
		char** app_argv_;

		typedef std::function<GAS::AutoRef<TestSceneBase>(const std::string&)> TestSceneCreateFunc;

		std::map<std::string,TestSceneCreateFunc> tests_scenes_create_funcs_;

		TestSceneBase* current_scene_;
	};

}


#endif //Tests_TestsDelegate_H