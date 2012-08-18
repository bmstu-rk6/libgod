#include "godtest.h"

namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

class FileASN1Test : public FileComparerParametrized
{
};


TEST_P(FileASN1Test, testRead)
{
	libgod::GodASN1 ga;
	EXPECT_NO_THROW(ga.readFromFile(m_inFilename));
	EXPECT_NO_THROW(ga.writeToFile(m_outFilename));
	EXPECT_TRUE(checkEquals());
}

TEST_P(FileASN1Test, testWrite) 
{
	libgod::GodASN1 ga;
	EXPECT_NO_THROW(ga.writeToFile(m_outFilename));
	EXPECT_TRUE(checkEquals());
}

TEST_P(FileASN1Test, testReadCtor) 
{
	libgod::GodASN1 ga(m_inFilename);
	EXPECT_NO_THROW(ga.writeToFile(m_outFilename));
	EXPECT_TRUE(checkEquals());
}

INSTANTIATE_TEST_CASE_P(FileASN1Test, FileASN1Test, 
		::testing::Values(
			std::string("../input1.asn1"), 
			std::string("../input2.asn1")
		));
