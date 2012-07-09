#ifndef INC__ASSERTS_H
#define INC__ASSERTS_H

// asserts

namespace libgod
{
  class assert_exception : public std::runtime_error
	{
  public:
    explicit assert_exception (const std::string& message) : std::runtime_error(message){}
    explicit assert_exception (const boost::format& message) : std::runtime_error(message.str()){}
  };
	
	template <class T>
	void assertTrue (const T& left, unsigned line)
	{
		bool result = left;
		if (!result)
			throw assert_exception( boost::format( "assertEqual at %d : %s - %s" )
					% line % (result?"true":"false") % left );
	}


	template <class T, class U>
	void assertEqual (const T& left, const U& right, unsigned line)
	{
		bool result = left == right;
		if (!result)
			throw assert_exception( boost::format( "assertEqual at %d : %s - %s and %s" )
					% line % (result?"true":"false") % left % right );
	}


	template <class T, class U>
	void assertNonEqual (const T& left, const U& right, unsigned line)
	{
		bool result = left != right;
		if (!result)
			throw assert_exception( boost::format( "assertNonEqual at %d : %s - %s and %s" )
					% line % (result?"true":"false") % left % right );
	}

	inline void assertError (const std::string& s, unsigned line)
	{
		throw assert_exception( boost::format( "assertError at %d : said %s" )
				% line % s );
	}
};

#define ASSERT_TRUE(Expr1) libgod::assertTrue((Expr1), __LINE__)
#define ASSERT_EQUAL(Expr1, Expr2) libgod::assertEqual((Expr1), (Expr2), __LINE__)
#define ASSERT_NONEQUAL(Expr1, Expr2) libgod::assertNonEqual((Expr1), (Expr2), __LINE__)
#define ASSERT_ERROR(Expr1) libgod::assertError((Expr1), __LINE__)

#endif

