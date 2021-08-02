#include <iostream>

#include "WorkingScope.h"
#include "TestsDelegate.h"

int main( int argc, char** argv )
{
	int ret = 0;
	{
		GAS::WorkingScope scope(new Tests::TestsDelegate());

		ret = scope.run();
	}

	std::cout << argv[0] << std::endl;

	char r;
	std::cin >> r;

	return ret;
}
