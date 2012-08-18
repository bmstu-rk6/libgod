#include "godtest.h"

TEST(Metadata, addremove)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	EXPECT_EQ(un1.metadata().size(), 2);
	EXPECT_TRUE(un1.metadata().is("foo"));
	EXPECT_TRUE(un1.metadata().is("bar"));
	EXPECT_FALSE(un1.metadata().is("baz"));


	libgod::Union un2 = un1;
	
	EXPECT_EQ(un2.metadata().size(), 2);
	

	libgod::Union un3;
	un3 = un1;

	EXPECT_EQ(un3.metadata().size(), 2);

	un1.metadata().remove("foo");
	EXPECT_EQ(un1.metadata().size(), 1);
	EXPECT_EQ(un2.metadata().size(), 2);
	EXPECT_EQ(un3.metadata().size(), 2);
}

TEST(Metadata, entryorder)
{
	libgod::MetadataEntry me1("foo", "foo123");
	libgod::MetadataEntry me2("bar", "bar123");
	libgod::MetadataEntry me3("foo", "zap123");

	// !=
	EXPECT_NE(me1,me2);
	EXPECT_NE(me1,me3);
	EXPECT_NE(me2,me3);
	
	// less
	EXPECT_LT(me2,me1);
	EXPECT_LT(me2,me3);

	// me1 and me3 are equal in terms of order but not equal
	EXPECT_FALSE(me1<me3);
	EXPECT_FALSE(me3<me1);
	EXPECT_NE(me1,me3);

	// not less = ge
	EXPECT_FALSE(me1<me2);
	EXPECT_FALSE(me3<me2);

	EXPECT_FALSE(me3<me1);
}

TEST(Metadata, iterators)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	std::vector<libgod::MetadataEntry> keys;
}

