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

};

#endif

