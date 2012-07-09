#ifndef INC__GODERROR_H
#define INC__GODERROR_H

namespace libgod
{

	class GodError : public std::runtime_error
	{
	public:
		explicit GodError (const std::string& message)
			: std::runtime_error(message)
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
	
	class GodOutOfRangeError : public std::out_of_range
	{
	public:
		explicit GodOutOfRangeError (const std::string& message, size_t pos, size_t count)
			: std::out_of_range(boost::str(boost::format("%s index %lu is out of range %lu") 
						% pos % count))
		{
		}

		virtual ~GodOutOfRangeError() throw()
		{
		}
	};

};

#endif

