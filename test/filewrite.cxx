#include "godtest.h"

class FileWriteTest : public FileComparer
{
protected:
	void actualProcess(std::string filename)
	{
		setFileName(filename);

		libgod::GodASN1 ga;
		EXPECT_NO_THROW(ga.writeToFile(m_outFilename));
		EXPECT_TRUE(checkEquals());
	}
};


TEST_F(FileWriteTest, process1)
{
	actualProcess("../input1.asn1");
}

TEST_F(FileWriteTest, process2)
{
	actualProcess("../input2.asn1");
}

