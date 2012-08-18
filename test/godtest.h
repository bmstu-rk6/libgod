#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include <limits>
#include <unistd.h>
#include <sys/types.h>

#include "libgod.h"

#include "gtest/gtest.h"

// Helper class to compare gold file with a generated output file
class FileComparer 
{
protected:
	std::string m_inFilename;
	std::string m_outFilename;

	void setFileName (std::string fileName);

	bool checkEquals();
};

// Class for inherit test from
class FileComparerParametrized : public FileComparer, public ::testing::TestWithParam<std::string>
{
	virtual void SetUp()
	{
		setFileName(GetParam());
	}
};

#endif

