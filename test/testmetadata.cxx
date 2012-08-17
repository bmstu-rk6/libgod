#include "godtest.h"

TEST(Metadata, simple)
{
	libgod::Union un1;
	un1.metadata().add(libgod::MetadataEntry("foo", "foo123"));
	un1.metadata().add(libgod::MetadataEntry("bar", "bar123"));

	ASSERT_EQ(un1.metadata().size(), 2);


	libgod::Union un2 = un1;
	
	ASSERT_EQ(un2.metadata().size(), 2);
	

	libgod::Union un3;
	un3 = un1;

	ASSERT_EQ(un3.metadata().size(), 2);

	un1.metadata().remove("foo");
	ASSERT_EQ(un1.metadata().size(), 1);
	ASSERT_EQ(un2.metadata().size(), 2);
	ASSERT_EQ(un3.metadata().size(), 2);
}

