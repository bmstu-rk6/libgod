#include "godtest.h"

int main(int argc, char* argv[])
{
	INIT_TEST(2)
	try
	{
		libgod::GodASN1 ga;
		ga.readFromFile( argv[1] );
		ga.writeToFile( argv[2] );
	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
