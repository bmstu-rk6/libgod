#ifndef INC__GODERROR_H
#define INC__GODERROR_H

namespace libgod
{

	class GodError : std::runtime_error
	{
	public:
		explicit GodError (const std::string& message)
			: std::runtime_error(message)
		{
		}

		virtual ~GodError() throw()
		{
		}
	};
	
	namespace detail
	{
		inline std::string outOfRangeSuffix(size_t pos, size_t count)
		{
			char buf[64];
			if (snprintf(buf, sizeof(buf), " index %lu is out of range %lu", pos, count ) >= sizeof(buf))
				buf[sizeof(buf)-1] = 0;
			return buf;
		}
	};

	class GodOutOfRangeError : std::out_of_range
	{
	public:
		explicit GodOutOfRangeError (const std::string& message, size_t pos, size_t count)
			: std::out_of_range(message + detail::outOfRangeSuffix(pos,count)) 
		{
		}

		virtual ~GodOutOfRangeError() throw()
		{
		}
	};

};

#endif

