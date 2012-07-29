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
	catch (libgod::GodError& ge) {
		std::cerr<< "Test error: " << ge.what() << std::endl;
		return 1;
	}

	return 0;
}
