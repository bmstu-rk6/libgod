#include "godtest.h"
#include "comparable.h"

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
			libgod::Comparable c;
			for (size_t i = 0; i < 10; ++i)
			{
				libgod::Point p1 = randPoint(dp,dc);
				libgod::Point p2 = randPoint(dp,dc);
				ASSERT_TRUE(p1 == p2 || c(p1,p2) != c(p2,p1));
			}
			libgod::Set s1(dp,dc);
			libgod::Set s2(dp,dc);
			s1.add(randPoint(dp,dc));
			s1.add(randPoint(dp,dc));
			s2.add(randPoint(dp,dc));
			s2.add(randPoint(dp,dc));
			s2.add(randPoint(dp,dc));
			ASSERT_TRUE(c(s1,s2));
			ASSERT_TRUE(!c(s1,s1));
			ASSERT_TRUE(!c(s2,s1));
			
			// Check set order when point slightly dffers
			libgod::Set s3 = s1;
			s3[0].setParameterAt(0, s1[0].parameterAt(0)+1);
			ASSERT_TRUE(c(s1,s3));
			ASSERT_TRUE(!c(s3,s1));
			s3[0].setParameterAt(0, s1[0].parameterAt(0)-1);
			ASSERT_TRUE(!c(s1,s3));
			ASSERT_TRUE(c(s3,s1));

			libgod::Set s4(dp+1,dc);
			ASSERT_TRUE(c(s1,s4));
			ASSERT_TRUE(!c(s4,s1));
			
			// unions checks
			libgod::Union u1(dp,dc);
			libgod::Union u2(dp,dc);
			u1.add(s1);
			u1.add(s1);
			u2.add(s1);
			u2.add(s1);
			u2.add(s1);
			ASSERT_TRUE(c(u1,u2));
			ASSERT_TRUE(!c(u2,u1));

			u2.clear();
			u2.add(s2);
			u2.add(s2);
			ASSERT_TRUE(c(u1,u2));
			ASSERT_TRUE(!c(u2,u1));
		}

	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
