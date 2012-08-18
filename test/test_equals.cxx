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
	
const size_t dp = 2, dc = 3; 

TEST(Equals, Bare)
{
	// test bare
	libgod::Union u2;
	EXPECT_TRUE(u2.isBare());
	EXPECT_TRUE(u2.dimCriteria()<=1);

	libgod::Union u0(dp,dc);
	EXPECT_TRUE(!u0.isBare());
	u2 = u0;
	EXPECT_TRUE(!u2.isBare());
	EXPECT_EQ(u2.dimCriteria(), u0.dimCriteria());
	EXPECT_EQ(u2.dimParameter(), u0.dimParameter());
}

TEST(Equals, BareSetCascade)
{
	// construct a bare set
	libgod::Set s;
	EXPECT_TRUE(s.isBare());
	EXPECT_NE(s.dimParameter(), dp);
	EXPECT_NE(s.dimCriteria(), dc);

	// adding point to a bare set make it looks okay
	libgod::Point p(dp,dc);
	s.add(p);

	EXPECT_TRUE(!s.isBare());
	EXPECT_EQ(s.dimParameter(), dp);
	EXPECT_EQ(s.dimCriteria(), dc);
}

TEST(Equals, BareSetUnion)
{
	// construct a bare set
	libgod::Union u;
	EXPECT_TRUE(u.isBare());
	EXPECT_NE(u.dimParameter(), dp);
	EXPECT_NE(u.dimCriteria(), dc);

	// adding point to a bare set make it looks okay
	libgod::Set s(dp,dc);
	u.add(s);

	EXPECT_TRUE(!u.isBare());
	EXPECT_EQ(u.dimParameter(), dp);
	EXPECT_EQ(u.dimCriteria(), dc);
}

TEST(Equals, UnionShallow)
{
	libgod::Set aset2(dp,dc);
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));

	// equals tests for the set
	libgod::Set aset2copy = aset2;
	EXPECT_TRUE(aset2copy == aset2);
	EXPECT_EQ(aset2copy.dimParameter(), aset2.dimParameter());
	EXPECT_EQ(aset2copy.dimCriteria(), aset2.dimCriteria());
	EXPECT_TRUE(!(aset2copy != aset2));

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
	EXPECT_EQ(u[0], aset1);
	EXPECT_EQ(u[1], aset2);
	EXPECT_EQ(u[2], aset3);
	u.swapItems(0,1);
	EXPECT_EQ(u[1], aset1);
	EXPECT_EQ(u[0], aset2);
	EXPECT_EQ(u[2], aset3);
}

TEST(Equals, UnionDeep)
{
	// equals tests for the union
	//
	libgod::Union u1(dp,dc);
	u1.add().add(randPoint(dp,dc));
	u1.add().add(randPoint(dp,dc));
	u1.add().add(randPoint(dp,dc));

	libgod::Union u2 = u1;
	EXPECT_TRUE(u2 == u1);
	EXPECT_TRUE(!(u2 != u1));
	EXPECT_TRUE(u2.deepEquals(u1));
	EXPECT_TRUE(u1.deepEquals(u2));

	// changing set content keeps union equal
	// deepEquals should fail of course
	u2[0] = u2[1];
	EXPECT_TRUE(u2 == u1);
	EXPECT_TRUE(!(u2 != u1));
	EXPECT_TRUE(!u2.deepEquals(u1));
	EXPECT_TRUE(!u1.deepEquals(u2));

	// deepEquals checks for sets equality
	u1[2].add(randPoint(dp,dc));
	EXPECT_TRUE(u2 == u1);
	EXPECT_TRUE(!(u2 != u1));
	EXPECT_TRUE(!u2.deepEquals(u1));
	EXPECT_TRUE(!u1.deepEquals(u2));

	// deepEquals succeeds if some sets are swapped 
	// i.e. not ordered
	u2 = u1;
	u2.swapItems(0,1);
	EXPECT_TRUE(u2 == u1);
	EXPECT_TRUE(!(u2 != u1));
	EXPECT_TRUE(u2.deepEquals(u1));
	EXPECT_TRUE(u1.deepEquals(u2));
}

