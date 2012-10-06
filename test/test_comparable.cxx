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
	
const size_t dp = 2, dc = 3; 

TEST(Comparable, Strict)
{
	libgod::Comparable c;
	for (size_t i = 0; i < 10; ++i)
	{
		libgod::Point p1 = randPoint(dp,dc);
		libgod::Point p2 = randPoint(dp,dc);
		EXPECT_TRUE(p1 == p2 || c(p1,p2) != c(p2,p1));
	}
	libgod::Set s1(dp,dc);
	libgod::Set s2(dp,dc);
	s1.add(randPoint(dp,dc));
	s1.add(randPoint(dp,dc));
	s2.add(randPoint(dp,dc));
	s2.add(randPoint(dp,dc));
	s2.add(randPoint(dp,dc));
	EXPECT_TRUE(c(s1,s2));
	EXPECT_TRUE(!c(s1,s1));
	EXPECT_TRUE(!c(s2,s1));
}

TEST(Comparable, NonStrict)
{
	libgod::Comparable c;

	libgod::Set s1(dp,dc);
	s1.add(randPoint(dp,dc));
	s1.add(randPoint(dp,dc));

	// Check set order when point slightly dffers
	libgod::Set s3 = s1;
	s3[0].setParameterAt(0, s1[0].parameterAt(0)+1);
	EXPECT_TRUE(c(s1,s3));
	EXPECT_TRUE(!c(s3,s1));
	s3[0].setParameterAt(0, s1[0].parameterAt(0)-1);
	EXPECT_TRUE(!c(s1,s3));
	EXPECT_TRUE(c(s3,s1));

	libgod::Set s4(dp+1,dc);
	EXPECT_TRUE(c(s1,s4));
	EXPECT_TRUE(!c(s4,s1));
}

TEST(Comparable, Union)
{
	libgod::Comparable c;

	libgod::Set s1(dp,dc);
	s1.add(randPoint(dp,dc));
	s1.add(randPoint(dp,dc));

	libgod::Set s2(dp,dc);
	s2.add(randPoint(dp,dc));
	s2.add(randPoint(dp,dc));
	s2.add(randPoint(dp,dc));

  // ensure order
	s2[0].setParameterAt(0, s1[0].parameterAt(0)+1);
	EXPECT_TRUE(c(s1[0],s2[0]));

	// unions checks
	libgod::Union u1(dp,dc);
	u1.add(s1);
	u1.add(s1);

	libgod::Union u2(dp,dc);
	u2.add(s1);
	u2.add(s1);
	u2.add(s1);
	EXPECT_TRUE(c(u1,u2) != c(u2,u1));
	EXPECT_TRUE(c(u1,u2));
	EXPECT_TRUE(!c(u2,u1));

	u2.clear();
	u2.add(s2);
	u2.add(s2);
	EXPECT_TRUE(c(u1,u2) != c(u2,u1));
	EXPECT_TRUE(c(u1,u2));
	EXPECT_TRUE(!c(u2,u1));
}
