#include "common.h"
#include "libgod.h"
#include "godpoint.h"

namespace libgod
{
	Point::Point(size_t dimParameter, size_t dimCriteria)
		: m_dimParameter(dimParameter),
		m_dimCriteria(dimCriteria),
		m_parameters(new double[m_dimParameter]),
		m_criteria(new double[m_dimCriteria])
	{
	}

	Point::Point (const Point& rhs)
		: m_dimParameter(rhs.m_dimParameter),
			m_dimCriteria(rhs.m_dimCriteria),
			m_parameters(new double[m_dimParameter]),
			m_criteria(new double[m_dimCriteria])
	{
		memcpy(m_parameters.get(), rhs.m_parameters.get(), m_dimParameter * sizeof(double));
		memcpy(m_criteria.get(), rhs.m_criteria.get(), m_dimCriteria * sizeof(double));
	}

	Point::~Point()
	{
	}

	Point& Point::operator= (const Point& rhs)
	{
		if (this != &rhs)
		{
			if (m_dimParameter != rhs.m_dimParameter || 
					m_dimCriteria != rhs.m_dimCriteria)
			{
				throw GodError("cannot assign point with a different metric");
			}
			memcpy(m_parameters.get(), rhs.m_parameters.get(), m_dimParameter * sizeof(double));
			memcpy(m_criteria.get(), rhs.m_criteria.get(), m_dimCriteria * sizeof(double));
		}
		return *this;
	}

	bool Point::operator== (const Point& rhs) const
	{
		return
			m_dimParameter == rhs.m_dimParameter &&
			m_dimCriteria == rhs.m_dimCriteria &&
			!memcmp(m_parameters.get(), rhs.m_parameters.get(), m_dimParameter * sizeof(double)) &&
			!memcmp(m_criteria.get(), rhs.m_criteria.get(), m_dimCriteria * sizeof(double));
	}

	bool Point::operator!= (const Point& rhs) const
	{
		return !(*this == rhs);
	}
};


