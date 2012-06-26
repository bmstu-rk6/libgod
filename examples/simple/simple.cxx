#include <iostream>
#include "libgod.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
			throw std::runtime_error( "Not enough arguments" );

		//libgod::GodASN1 ga;
		//ga.writeToFile( argv[1] );
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
