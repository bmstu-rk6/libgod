#ifndef INC__GODERROR_H
#define INC__GODERROR_H

namespace libgod
{

	/**
	 * Generic error exception class
	 */
	class GodError : public std::runtime_error
	{
	public:
		/** Construct an exception with the string */
		explicit GodError (const std::string& message)
			: std::runtime_error(message)
		{
		}
		
		/** Construct an exception with the boost::format instance */
		explicit GodError (const boost::format& fmt)
			: std::runtime_error(fmt.str())
		{
		}
		
		/** Construct an exception with the string and integer error code (just a number) */
		explicit GodError (const std::string& message, int errnoCode)
			: std::runtime_error(boost::str(boost::format("%s, fail due to %d (%s)")
						% message % errnoCode % strerror(errnoCode)))
		{
		}

		virtual ~GodError() throw()
		{
		}
	};

	/**
	 * File not found exception class
	 */
	class GodNotFoundError : public GodError
	{
	public:
		/** Construct an exception with the filename */
		explicit GodNotFoundError(const std::string& file)
			: GodError("File not found " + file)
		{
		}
	};
	
	/**
	 * Out of range exception class
	 */
	class GodOutOfRangeError : public GodError
	{
	public:
		/** Construct an exception with the message and failed out-of-range position */
		explicit GodOutOfRangeError (const std::string& message, size_t pos, size_t count)
			: GodError(boost::format("%s index %lu is out of range %lu") 
						% message % pos % count)
		{
		}
	};
	
	/**
	 * Assertion exception class. Thrown when assertion is failed.
	 */
  class AssertError : public GodError
	{
  public:
		/** Construct an assert exception */
    explicit AssertError (const std::string& message) : GodError(message){}
		/** Construct an assert exception */
    explicit AssertError (const boost::format& message) : GodError(message){}
  };

	/**
	 * Assert macro. Assert passes if expression Expr1 evaluates to true
	 */
	#define GOD_ASSERT(Expr1) libgod::assertTrue((Expr1), __LINE__)
	template <class T>

	void assertTrue (const T& left, unsigned line)
	{
		if (!(bool)left)
			throw AssertError(boost::format("assertTrue at %d : %s - %s")
					% line % (left?"true":"false") % left);
	}

};

#endif

