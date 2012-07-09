#include "libgod.h"

/**********************************************
	This program prints content of godfile in XML format to stdout
**********************************************/

int main(int argc, char *argv[]) {
	try {
		libgod::Union un;
		libgod::Storage st( argv[1] );

		st.read(un);

		//Print dump to stdout
		st.dump(std::cout, un);

	}
	catch (std::exception& e) {
		std::cerr << "Print error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
