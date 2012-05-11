#include "godtest.h"

void initTest(const char* name, int neededArgs, int argc, char* argv[])
{
	std::cout << "Running test " << name << std::endl;
	for (int i = 1; i <= argc; ++i)
		std::cout << " #" << i << " " << argv[i] << std::endl;
	
	if (argc != neededArgs+1)
		throw std::runtime_error( "Not enough arguments" );
}
