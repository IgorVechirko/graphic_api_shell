#include <iostream>

#include "WorkingScope.h"
#include "WorkingScopeDelegate.h"
#include "Ref.h"
#include "FileUtils.h"

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
		auto fooObj = getScope()->getCreator()->createObject<Foo>();

		auto file = getScope()->getFileUtils()->loadFile( "" );

		file->setPath( "" );

		bool stop = true;

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
