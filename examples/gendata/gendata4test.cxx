#include <iostream>
#include "libgod.h"

/**********************************************
	This program creates files for testunion programs.
	Generated files are verified by krouk that they reflect expected
	ASN/1 structure.
**********************************************/

// I know this is ugly, but I need just create data for testing
int ind_xf = 0;
double x_and_f[275];

//Create random point with specified number of paramters and criteria
libgod::Point randPoint (size_t dp, size_t dc)
{
	libgod::Point p(dp,dc);
	for (size_t i = 0; i < dp; ++i) {
		x_and_f[ind_xf] = 1.0 * rand() / RAND_MAX;
		p.setParameterAt(i, x_and_f[ind_xf]);
		ind_xf++;
	}
	
	for (size_t i = 0; i < dc; ++i) {
		x_and_f[ind_xf] = 1.0 * rand() / RAND_MAX;
		p.setCriterionAt(i, x_and_f[ind_xf]);
		ind_xf++;
	}
	return p;
}

int main(int argc, char* argv[])
{
	try {
		//input.union1: Union with 1 empty set
		libgod::Union un1(10,7);
		libgod::Set& s = un1.add();
		
		libgod::Storage st1("input.union1");
		st1.write(un1);
		// Print dump to cout
		std::cout << un1;

		//un1.~Union();

		//input.union2: Union with 2 sets each has 2 points
		//TODO: will require some updates when code will be fixed
		libgod::Union un2(5,3);

		double parameters[] = {1.2, -0.9, 6.7, 1.209, 4.731};
		double criteria[] = {0.99, 0.76, 0.12};

		for (int i=0; i<2; i++) {
			libgod::Set& s = un2.add();
			for (int j=0; j<2; j++) {
				libgod::Point& p = s.add();
				p.setParameters(parameters);
				p.setCriteria(criteria);
			}
		}
		
		libgod::Storage st2("input.union2");
		st2.write(un2);
		std::cout << un2;

		//input.union3: Union with 10 sets, each set has (i+1) random points
		const size_t dp = 2, dc = 3; 
		libgod::Union un3(dp,dc);

		for (int i=0; i<10; i++) {
			libgod::Set& s = un3.add();
			for (int j=0; j<(i+1); j++)
				s.add(randPoint(dp,dc));
		}

		libgod::Storage st3("input.union3");
		st3.write(un3);
		std::cout << un3;
		
		//write gobal x and f into file
		std::ofstream testdata;
		testdata.open("input.union3.bin", std::ios::binary | std::ios::out);
		testdata.write((char*)x_and_f, sizeof(x_and_f));
		testdata.close();
		
		std::cout << "sizeof(x_and_f) = " << sizeof(x_and_f) << std::endl;
		
		for (int i=0; i<275; i++) {
			std::cout << x_and_f[i] << " ";
			if (i%5 == 0)
				std::cout << std::endl;
		}
		std::cout << std::endl;
		
		//std::cout<< "ind_xf = " << ind_xf << std::endl;

		//TODO: input.union4: 

		//TODO:	input.union5: input.union2 with metadata (8 entries)
		//Comment: when the code will be ready
	
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
