#include "godtest.h"

namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/erase.hpp>

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

void checkXer(libgod::GodASN1& ga, const std::string expected)
{
	std::stringstream ss;
	ga.dump(ss, ga.getRoot().get());
	std::string actual = ss.str();
	boost::algorithm::replace_all(actual, "\n", "");
	boost::algorithm::erase_all(actual, " ");
	EXPECT_EQ(actual, expected);
}

TEST_P(FileASN1Test, testXer)
{
	libgod::GodASN1 ga;
	ga.getRoot()->header.version = 123;
	OCTET_STRING_fromString(&ga.getRoot()->header.comment, "LongComment");
	ga.getRoot()->metric.parameterDim = 10;
	ga.getRoot()->metric.criteriaDim = 200;
	ga.getRoot()->metric.setsCount = 3000;
	checkXer(ga, "<God><header><version>123</version><comment>LongComment</comment></header><metric><parameterDim>10</parameterDim><criteriaDim>200</criteriaDim><setsCount>3000</setsCount></metric><union></union></God>");
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
