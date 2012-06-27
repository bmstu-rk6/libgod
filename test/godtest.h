#ifndef INC__GODTEST_H
#define INC__GODTEST_H

#include "libgod.h"
// for some tests
namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

#define INIT_TEST(neededArgs) initTest( __FILE__, (neededArgs), argc, argv );

void initTest(const char* name, int neededArgs, int argc, char* argv[]);

// asserts

namespace unittest
{
  class unittest_error : public std::runtime_error
	{
  public:
    explicit unittest_error (const std::string& message) : std::runtime_error(message){}
    explicit unittest_error (const boost::format& message) : std::runtime_error(message.str()){}
  };
	
	template <class T>
	void assertTrue (const T& left, unsigned line)
	{
		bool result = left;
		if (!result)
			throw unittest_error( boost::format( "assertEqual at %d : %s - %s" )
					% line % (result?"true":"false") % left );
	}


	template <class T, class U>
	void assertEqual (const T& left, const U& right, unsigned line)
	{
		bool result = left == right;
		if (!result)
			throw unittest_error( boost::format( "assertEqual at %d : %s - %s and %s" )
					% line % (result?"true":"false") % left % right );
	}


	template <class T, class U>
	void assertNonEqual (const T& left, const U& right, unsigned line)
	{
		bool result = left != right;
		if (!result)
			throw unittest_error( boost::format( "assertNonEqual at %d : %s - %s and %s" )
					% line % (result?"true":"false") % left % right );
	}

	inline void assertError (const std::string& s, unsigned line)
	{
		throw unittest_error( boost::format( "assertError at %d : said %s" )
				% line % s );
	}
};

#define ASSERT_TRUE(Expr1) unittest::assertTrue((Expr1), __LINE__)
#define ASSERT_EQUAL(Expr1, Expr2) unittest::assertEqual((Expr1), (Expr2), __LINE__)
#define ASSERT_NONEQUAL(Expr1, Expr2) unittest::assertNonEqual((Expr1), (Expr2), __LINE__)
#define ASSERT_ERROR(Expr1) unittest::assertError((Expr1), __LINE__)

#endif

