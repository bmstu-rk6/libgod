#ifndef LIBGOD_INC__GODPOINT_H
#define LIBGOD_INC__GODPOINT_H

#include "libgod-config.h"
#include <boost/scoped_array.hpp>
#include <stdexcept>
#include "goderror.h"

namespace libgod
{

	class Point
	{
		typedef boost::scoped_array<double> ArrayType;

		const size_t m_dimParameter;
		const size_t m_dimCriteria;

		ArrayType m_parameters;
		ArrayType m_criteria;
	public:

		Point(size_t dimParameter, size_t dimCriteria);
		Point (const Point& rhs);
		~Point();
		Point& operator= (const Point& rhs);

		bool operator== (const Point& rhs) const;
		
		bool operator!= (const Point& rhs) const;
	};


};

#endif

