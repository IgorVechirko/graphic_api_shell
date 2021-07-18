#include <iostream>

#include "WorkingScope.h"
#include "WorkingScopeDelegate.h"
#include "Ref.h"
#include "FileUtils.h"
#include "SceneBase.h"

class Foo : public GAS::Ref
{
public:

	Foo(){};
	virtual ~Foo(){
	
		bool stop =true;
	};

};

class TestDelegate
	: public GAS::WorkingScopeDelegate
{

public:

	TestDelegate(){};
	virtual ~TestDelegate(){};

	virtual void onBeforeRun() override
	{
		auto sceneRef = getScope()->getCreator()->createAndInitObj<GAS::SceneBase>(&GAS::SceneBase::init);

		getScope()->setScene( &sceneRef );
	}

};

int main( int argc, char** argv )
{
	int ret = 0;
	{
		GAS::WorkingScope scope(new TestDelegate());

		ret = scope.run();
	}

	char r;
	std::cin >> r;

	return ret;
}
