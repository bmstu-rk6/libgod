#include "godtest.h"

int main(int argc, char* argv[])
{
	INIT_TEST(1)
	try
	{
		libgod::GodASN1 ga;
		ga.writeToFile( argv[1] );
	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
