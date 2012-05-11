#ifndef INC__GODERROR_H
#define INC__GODERROR_H

namespace libgod
{

	class GodError : std::runtime_error
	{
	public:
		explicit GodError (const std::string& message)
			: std::runtime_error(message.c_str()) 
		{
		}

		virtual ~GodError() throw()
		{
		}
	};

};

#endif

