#include <iostream>

#include "GASStartClass.h"


int main( int argc, char** argv )
{
	GAS::GASStartClass context;
	context.run();

	std::cout << std::endl << "Press Enter to finish" << std::endl;
	std::cin.get();

	return 0;
}
