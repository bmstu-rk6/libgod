#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/shared_ptr.hpp>
namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

#define INIT_TEST(neededArgs) initTest( __FILE__, (neededArgs), argc, argv );

void initTest(const char* name, int neededArgs, int argc, char* argv[]);

#endif

