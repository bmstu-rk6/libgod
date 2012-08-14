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
	ASSERT_TRUE(u2.isBare());
	ASSERT_TRUE(u2.dimCriteria()<=1);

	libgod::Union u0(dp,dc);
	ASSERT_TRUE(!u0.isBare());
	u2 = u0;
	ASSERT_TRUE(!u2.isBare());
	ASSERT_EQ(u2.dimCriteria(), u0.dimCriteria());
	ASSERT_EQ(u2.dimParameter(), u0.dimParameter());
}

TEST(Equals, BareSetCascade)
{
	// construct a bare set
	libgod::Set s;
	ASSERT_TRUE(s.isBare());
	ASSERT_NE(s.dimParameter(), dp);
	ASSERT_NE(s.dimCriteria(), dc);

	// adding point to a bare set make it looks okay
	libgod::Point p(dp,dc);
	s.add(p);

	ASSERT_TRUE(!s.isBare());
	ASSERT_EQ(s.dimParameter(), dp);
	ASSERT_EQ(s.dimCriteria(), dc);
}

TEST(Equals, BareSetUnion)
{
	// construct a bare set
	libgod::Union u;
	ASSERT_TRUE(u.isBare());
	ASSERT_NE(u.dimParameter(), dp);
	ASSERT_NE(u.dimCriteria(), dc);

	// adding point to a bare set make it looks okay
	libgod::Set s(dp,dc);
	u.add(s);

	ASSERT_TRUE(!u.isBare());
	ASSERT_EQ(u.dimParameter(), dp);
	ASSERT_EQ(u.dimCriteria(), dc);
}

TEST(Equals, UnionShallow)
{
	libgod::Set aset2(dp,dc);
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));

	// equals tests for the set
	libgod::Set aset2copy = aset2;
	ASSERT_TRUE(aset2copy == aset2);
	ASSERT_EQ(aset2copy.dimParameter(), aset2.dimParameter());
	ASSERT_EQ(aset2copy.dimCriteria(), aset2.dimCriteria());
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
	ASSERT_EQ(u[0], aset1);
	ASSERT_EQ(u[1], aset2);
	ASSERT_EQ(u[2], aset3);
	u.swapItems(0,1);
	ASSERT_EQ(u[1], aset1);
	ASSERT_EQ(u[0], aset2);
	ASSERT_EQ(u[2], aset3);
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
	ASSERT_TRUE(u2 == u1);
	ASSERT_TRUE(!(u2 != u1));
	ASSERT_TRUE(u2.deepEquals(u1));
	ASSERT_TRUE(u1.deepEquals(u2));

	// changing set content keeps union equal
	// deepEquals should fail of course
	u2[0] = u2[1];
	ASSERT_TRUE(u2 == u1);
	ASSERT_TRUE(!(u2 != u1));
	ASSERT_TRUE(!u2.deepEquals(u1));
	ASSERT_TRUE(!u1.deepEquals(u2));

	// deepEquals checks for sets equality
	u1[2].add(randPoint(dp,dc));
	ASSERT_TRUE(u2 == u1);
	ASSERT_TRUE(!(u2 != u1));
	ASSERT_TRUE(!u2.deepEquals(u1));
	ASSERT_TRUE(!u1.deepEquals(u2));

	// deepEquals succeeds if some sets are swapped 
	// i.e. not ordered
	u2 = u1;
	u2.swapItems(0,1);
	ASSERT_TRUE(u2 == u1);
	ASSERT_TRUE(!(u2 != u1));
	ASSERT_TRUE(u2.deepEquals(u1));
	ASSERT_TRUE(u1.deepEquals(u2));
}

