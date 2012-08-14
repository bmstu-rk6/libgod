#include "godtest.h"

class FileReadCtorTest : public FileComparer
{
protected:
	void actualProcess(std::string filename)
	{
		setFileName(filename);

		libgod::GodASN1 ga(m_inFilename);
		EXPECT_NO_THROW(ga.writeToFile(m_outFilename));
		EXPECT_TRUE(checkEquals());
	}
};


TEST_F(FileReadCtorTest, process1)
{
	actualProcess("../input1.asn1");
}

TEST_F(FileReadCtorTest, process2)
{
	actualProcess("../input2.asn1");
}

