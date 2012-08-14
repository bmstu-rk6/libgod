#include "godtest.h"

class FileUnionIOTest : public FileComparer
{
protected:
	void actualProcess(std::string filename)
	{
		setFileName(filename);

		libgod::Union un;
		libgod::Storage st1(m_inFilename);
		libgod::Storage st2(m_outFilename);

		EXPECT_NO_THROW(st1.read(un));
		EXPECT_NO_THROW(st2.write(un));
		EXPECT_TRUE(checkEquals());
	}
};


TEST_F(FileUnionIOTest, union1)
{
	actualProcess("../input.union1");
}

TEST_F(FileUnionIOTest, union2)
{
	actualProcess("../input.union2");
}

TEST_F(FileUnionIOTest, union3)
{
	actualProcess("../input.union3");
}

TEST_F(FileUnionIOTest, DISABLED_unionrand)
{
	actualProcess("../input.unionrand");
}

