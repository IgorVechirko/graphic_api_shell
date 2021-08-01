#ifndef TESTS_TestSceneBase_H
#define TESTS_TestSceneBase_H

#include "Common.h"
#include "SceneBase.h"

namespace Tests
{

	class TestSceneBase
		: public GAS::SceneBase
	{

	public:

		TestSceneBase();
		virtual ~TestSceneBase();

		bool initWithName( const std::string& test_name );

		const std::string& getName() const;

	private:

		std::string test_name_;

	};

}

#endif //TESTS_TestSceneBase_H