#include "godtest.h"
#include <boost/assign/list_of.hpp>

TEST(Metadata, add)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	EXPECT_EQ(un1.metadata().size(), 2);
	EXPECT_TRUE(un1.metadata().is("foo"));
	EXPECT_TRUE(un1.metadata().is("bar"));
	EXPECT_FALSE(un1.metadata().is("baz"));

	EXPECT_THROW(un1.metadata().add(libgod::MetadataEntry("foo","zzz")), libgod::GodError);
	EXPECT_EQ(un1.metadata().size(), 2);

}

TEST(Metadata, copy)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	EXPECT_EQ(un1.metadata().size(), 2);

	libgod::Union un2 = un1;
	
	EXPECT_EQ(un2.metadata().size(), 2);
	
	libgod::Union un3;
	EXPECT_TRUE(un3.metadata().empty());
	EXPECT_EQ(un3.metadata().size(), 0);
	un3 = un1;

	EXPECT_EQ(un3.metadata().size(), 2);
}

TEST(Metadata, remove)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	libgod::Union un2 = un1;
	libgod::Union un3;
	un3 = un1;

	un1.metadata().remove("foo");
	EXPECT_FALSE(un1.metadata().is("foo"));
	EXPECT_EQ(un1.metadata().size(), 1);
	EXPECT_EQ(un2.metadata().size(), 2);
	EXPECT_EQ(un3.metadata().size(), 2);
}

TEST(Metadata, remove_non_existant)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	un1.metadata().remove("foo");
	EXPECT_FALSE(un1.metadata().is("foo"));
	EXPECT_THROW(un1.metadata().remove("baz"), libgod::GodError);
	un1.metadata().remove("bar");
	EXPECT_FALSE(un1.metadata().is("bar"));
	EXPECT_TRUE(un1.metadata().empty());
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

class MetadataTest : public ::testing::Test
{
protected:
	void compareKeys (const libgod::Metadata& m, std::list<std::string> keys_expected)
	{
		std::list<std::string> keys_actual;
		for (libgod::Metadata::const_iterator it = m.begin(); it != m.end(); ++it)
			keys_actual.push_back(it->name());
		keys_actual.sort();
		keys_expected.sort();
		EXPECT_EQ(keys_actual, keys_expected);
	}

};

TEST_F(MetadataTest, iterators)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	compareKeys(un1.metadata(), boost::assign::list_of("foo")("bar"));
	
	un1.metadata().add(libgod::MetadataEntry("baz", "foo123"));
	compareKeys(un1.metadata(), boost::assign::list_of("foo")("bar")("baz"));
}

TEST_F(MetadataTest, ostream)
{
	std::ostringstream oss1, oss2;
	libgod::Union un1;
	oss1 << un1.metadata();

	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	oss2 << un1.metadata();
	ASSERT_FALSE(oss1.str().empty());
	ASSERT_FALSE(oss2.str().empty());
	ASSERT_GE(oss2.str().size(), oss1.str().size());
}

