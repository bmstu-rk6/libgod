#include "godtest.h"

int main (int argc, char *argv[]) {
	INIT_TEST(2);
	try {
		libgod::Union un;
		libgod::Storage st1( argv[1] );
		libgod::Storage st2( argv[2] );	

		st1.read(un);
		st2.write(un);
		
	}
	catch (std::exception& e) {
		std::cerr<< "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
