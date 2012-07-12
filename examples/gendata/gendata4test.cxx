#include <iostream>
#include "libgod.h"

/**********************************************
	This program creates files for testunion programs.
	Generated files are verified by krouk that they reflect expected
	ASN/1 structure.
**********************************************/

//Create random point with specified number of paramters and criteria
libgod::Point randPoint (size_t dp, size_t dc)
{
	libgod::Point p(dp,dc);
	for (size_t i = 0; i < dp; ++i)
		p.setParameterAt(i, 1.0 * rand() / RAND_MAX);
	for (size_t i = 0; i < dc; ++i)
		p.setCriterionAt(i, 1.0 * rand() / RAND_MAX);
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

		for (int i=0; i<un2.size(); i++) {
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
