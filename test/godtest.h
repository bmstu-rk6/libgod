#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include "libgod.h"
// for some tests
namespace asn1
{
#include "God.h"
};
#include "asserts.h"
#include "godasn1.h"

#define INIT_TEST(neededArgs) initTest( __FILE__, (neededArgs), argc, argv );

void initTest(const char* name, int neededArgs, int argc, char* argv[]);

#endif

