#include "godtest.h"

class FileUnionIOTest : public FileComparerParametrized
{
};


TEST_P(FileUnionIOTest, process)
{
	libgod::Union un;
	libgod::Storage st1(m_inFilename);
	libgod::Storage st2(m_outFilename);

	EXPECT_NO_THROW(st1.read(un));
	EXPECT_NO_THROW(st2.write(un));
	EXPECT_TRUE(checkEquals());
}

INSTANTIATE_TEST_CASE_P(FileUnionIOTest, FileUnionIOTest, 
		::testing::Values(
			std::string("../input.union1"), 
			std::string("../input.union2"),
			std::string("../input.union3")
		));

