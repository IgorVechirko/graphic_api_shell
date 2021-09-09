#include <iostream>

#include "WorkingScope.h"
#include "TestsDelegate.h"

int main( int argc, char** argv )
{
	int ret = 0;
	{
		GAS::WorkingScope scope(new Tests::TestsDelegate(argc, argv));

		ret = scope.run();
	}
	
	char r;
	std::cin >> r;

	return ret;
}
