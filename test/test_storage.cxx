#include "godtest.h"

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
	INIT_TEST(1);
	try
	{
		const size_t dp = 2, dc = 3; 
		libgod::Union aunion(dp,dc);

		libgod::Set& aset1 = aunion.add();
		aset1.add(randPoint(dp,dc));
		aset1.add(randPoint(dp,dc));
		
		ASSERT_EQUAL(aunion.size(), 1);
		ASSERT_EQUAL(aunion[0].size(), 2);
		
		libgod::Set& aset2 = aunion.add();
		aset2.add(randPoint(dp,dc));
		aset2.add(randPoint(dp,dc));
		aset2.add(randPoint(dp,dc));

		ASSERT_EQUAL(aunion.size(), 2);
		ASSERT_EQUAL(aunion[1].size(), 3);
		ASSERT_EQUAL(aunion[0].size(), 2);

		ASSERT_EQUAL(aunion.dimParameter(), dp);
		ASSERT_EQUAL(aunion[0].dimParameter(), dp);
		ASSERT_EQUAL(aunion[0][0].dimParameter(), dp);

		libgod::Storage storage(argv[1]);
		storage.write(aunion);
		storage.dump(std::cout, aunion);
		
		libgod::Union nunion(dp,dc);
		storage.read(nunion);
		storage.dump(std::cout, nunion);

		// test bare
		libgod::Union u2;
		ASSERT_TRUE(u2.isBare());
		ASSERT_TRUE(u2.dimCriteria()<=1);
		u2 = nunion;
		ASSERT_TRUE(!u2.isBare());
		ASSERT_EQUAL(u2.dimCriteria(), nunion.dimCriteria());
		ASSERT_EQUAL(u2.dimParameter(), nunion.dimParameter());
		
		ASSERT_EQUAL(aunion.size(), dp);
		ASSERT_EQUAL(aunion.size(), nunion.size());
	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
