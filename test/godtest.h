#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/shared_ptr.hpp>
#include <libgod.h>

#define INIT_TEST(neededArgs) initTest( __FILE__, (neededArgs), argc, argv );

void initTest(const char* name, int neededArgs, int argc, char* argv[]);

#endif

