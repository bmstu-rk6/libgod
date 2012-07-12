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
	INIT_TEST(0);
	try
	{
		const size_t dp = 2, dc = 3; 

		{
			// test bare
			libgod::Union u2;
			ASSERT_TRUE(u2.isBare());
			ASSERT_TRUE(u2.dimCriteria()<=1);
			
			libgod::Union u0(dp,dc);
			ASSERT_TRUE(!u0.isBare());
			u2 = u0;
			ASSERT_TRUE(!u2.isBare());
			ASSERT_EQUAL(u2.dimCriteria(), u0.dimCriteria());
			ASSERT_EQUAL(u2.dimParameter(), u0.dimParameter());
		}

		{
			libgod::Set aset2(dp,dc);
			aset2.add(randPoint(dp,dc));
			aset2.add(randPoint(dp,dc));
			aset2.add(randPoint(dp,dc));

			// equals tests for the set
			libgod::Set aset2copy = aset2;
			ASSERT_TRUE(aset2copy == aset2);
			ASSERT_EQUAL(aset2copy.dimParameter(), aset2.dimParameter());
			ASSERT_EQUAL(aset2copy.dimCriteria(), aset2.dimCriteria());
			ASSERT_TRUE(!(aset2copy != aset2));

			// construct a union
			
			libgod::Set aset1(dp,dc);
			aset1.add(randPoint(dp,dc));
			
			libgod::Set aset3(dp,dc);
			aset3.add(randPoint(dp,dc));
			aset3.add(randPoint(dp,dc));
			aset3.add(randPoint(dp,dc));

			libgod::Union u(dp,dc);
			u.add(aset1);
			u.add(aset2);
			u.add(aset3);

			// test set swaps
/*			ASSERT_EQUAL(u[0], aset1);
			ASSERT_EQUAL(u[1], aset2);
			ASSERT_EQUAL(u[2], aset3);
			u.swapItems(0,1);
			ASSERT_EQUAL(u[1], aset1);
			ASSERT_EQUAL(u[0], aset2);
			ASSERT_EQUAL(u[2], aset3);*/
		}


		{
			// equals tests for the union
			//
			libgod::Union u1(dp,dc);
			u1.add().add(randPoint(dp,dc));
			u1.add().add(randPoint(dp,dc));
			u1.add().add(randPoint(dp,dc));

			libgod::Union u2 = u1;
			ASSERT_TRUE(u2 == u1);
			ASSERT_TRUE(!(u2 != u1));
			ASSERT_TRUE(u2.deepEquals(u1));
			ASSERT_TRUE(u1.deepEquals(u2));

			// changing content keeps union equal
			u2[0] = u2[1];
			ASSERT_TRUE(u2 == u1);
			ASSERT_TRUE(!(u2 != u1));
			ASSERT_TRUE(!u2.deepEquals(u1));
			ASSERT_TRUE(!u1.deepEquals(u2));
		}

	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
