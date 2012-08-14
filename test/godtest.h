#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include <limits>
#include <unistd.h>
#include <sys/types.h>

#include "libgod.h"
// for some tests
namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

#include "gtest/gtest.h"

class FileComparer : public ::testing::Test
{
protected:
	std::string m_inFilename;
	std::string m_outFilename;

	virtual void SetUp();

	void setFileName(std::string inFilename);
	bool checkEquals();
};

#endif

