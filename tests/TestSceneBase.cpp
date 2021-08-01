#include "TestSceneBase.h"


namespace Tests
{

	TestSceneBase::TestSceneBase()
	{
	}

	TestSceneBase::~TestSceneBase()
	{
	}

	bool TestSceneBase::initWithName( const std::string& test_name )
	{
		test_name_ = test_name;

		return init();
	}

	const std::string& TestSceneBase::getName() const
	{
		return test_name_;
	}

}