#ifndef INC__GODERROR_H
#define INC__GODERROR_H

namespace libgod
{

	// Generic error class
	class GodError : public std::runtime_error
	{
	public:
		explicit GodError (const std::string& message)
			: std::runtime_error(message)
		{
		}
		
		explicit GodError (const boost::format& fmt)
			: std::runtime_error(fmt.str())
		{
		}
		
		explicit GodError (const std::string& message, int errnoCode)
			: std::runtime_error(boost::str(boost::format("%s, fail due to %d (%s)")
						% message % errnoCode % strerror(errnoCode)))
		{
		}

		virtual ~GodError() throw()
		{
		}
	};

	// File not found error
	class GodNotFoundError : public GodError
	{
	public:
		explicit GodNotFoundError(const std::string& file)
			: GodError("File not found " + file)
		{
		}
	};
	

	// Range error
	class GodOutOfRangeError : public GodError
	{
	public:
		explicit GodOutOfRangeError (const std::string& message, size_t pos, size_t count)
			: GodError(boost::format("%s index %lu is out of range %lu") 
						% message % pos % count)
		{
		}
	};
	
	// Assert
  class AssertError : public GodError
	{
  public:
    explicit AssertError (const std::string& message) : GodError(message){}
    explicit AssertError (const boost::format& message) : GodError(message){}
  };

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

