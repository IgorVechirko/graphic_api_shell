#ifndef Test_AutoTestsScene_H
#define Test_AutoTestsScene_H

#include "Common.h"
#include "TestSceneBase.h"

namespace Tests
{

	class AutoTestsScene
		: public TestSceneBase
	{

	public:

		AutoTestsScene();
		virtual ~AutoTestsScene();

		virtual void onInit() override;

	private:

		void testGlmIntegration();
		void testAllocator();
		void testAutoReleasePool();
		void testAutoRef();
		void testDataBuff();
		void testFileUtils();
		void testThread();
		void testThreadPool();

	};

}

#endif //Test_AutoTestsScene_H