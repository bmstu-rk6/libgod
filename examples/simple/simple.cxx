#include <iostream>
#include "libgod.h"

int main(int argc, char* argv[])
{
	try
	{
		std::cout << "Create a point with two parameters and three criteria" << std::endl;
		const size_t dp = 2, dc = 3; 
		libgod::Point p(dp,dc);
		for (size_t i = 0; i < dp; ++i)
			p.setParameterAt(i, 1.0 * rand() / RAND_MAX);
		for (size_t i = 0; i < dc; ++i)
			p.setCriterionAt(i, 1.0 * rand() / RAND_MAX);

		std::cout << "Create an empty union with specified dimensions" << std::endl;
		libgod::Union aunion(dp,dc);

		std::cout << "Add a new set to the union with two points" << std::endl;
		libgod::Set& aset1 = aunion.add();
		aset1.add(p);
		aset1.add(p);

		std::cout << "Add a new set to the union with three points" << std::endl;
		libgod::Set& aset2 = aunion.add();
		aset2.add(p);
		aset2.add(p);
		aset2.add(p);
	
		std::cout << "Write a union to ASN.1 file" << std::endl;
		libgod::Storage storage("example.asn1");
		storage.write(aunion);

		std::cout << "Read a union from ASN.1 file" << std::endl;
		libgod::Union bunion;
		storage.read(bunion);

		std::cout << "Union contains " << bunion.size() 
			<< " sets, first set is of " << bunion.begin()->size() << " points" << std::endl
			<< "Second point of first set is:\n" << bunion[0][1] << std::endl;

		std::cout << "Remove ASN.1 file" << std::endl;
		remove("example.asn1");
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
