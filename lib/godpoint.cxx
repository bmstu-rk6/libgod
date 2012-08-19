#include "common.h"
#include "libgod.h"
#include "godpoint.h"
#include "comparable.h"

namespace libgod
{
	Point::Point(size_t dimParameter, size_t dimCriteria)
		: m_dimParameter(dimParameter),
		m_dimCriteria(dimCriteria)
	{
		if (m_dimParameter <= 0 || m_dimCriteria <= 0)
			throw GodError("dimensions should be posititive");
		m_parameters.reset(new double[m_dimParameter]);
		m_criteria.reset(new double[m_dimCriteria]);
		memset(m_parameters.get(), 0, m_dimParameter * sizeof(double));
		memset(m_criteria.get(), 0, m_dimCriteria * sizeof(double));
	}
	
	Point::Point(size_t dimParameter, size_t dimCriteria, const double* parameters, const double* criteria)
		: m_dimParameter(dimParameter),
			m_dimCriteria(dimCriteria)
	{
		if (m_dimParameter <= 0 || m_dimCriteria <= 0)
			throw GodError("dimensions should be posititive");
		if (!parameters || !criteria)
			throw GodError("null pointers detected at ctor");
		if (parameters == criteria)
			throw GodError("passed the same pointer for parameters and criteria arrays, possibly a bug");
		m_parameters.reset(new double[m_dimParameter]);
		m_criteria.reset(new double[m_dimCriteria]);
		memcpy(m_parameters.get(), parameters, m_dimParameter * sizeof(double));
		memcpy(m_criteria.get(), criteria, m_dimCriteria * sizeof(double));
	}

	Point::Point (const Point& rhs)
		: m_dimParameter(rhs.m_dimParameter),
			m_dimCriteria(rhs.m_dimCriteria),
			m_parameters(new double[m_dimParameter]),
			m_criteria(new double[m_dimCriteria])
	{
		if (m_dimParameter <= 0 || m_dimCriteria <= 0)
			throw GodError("dimensions should be posititive");
		memcpy(m_parameters.get(), rhs.m_parameters.get(), m_dimParameter * sizeof(double));
		memcpy(m_criteria.get(), rhs.m_criteria.get(), m_dimCriteria * sizeof(double));
	}

	Point::~Point()
	{
	}
		
	void Point::preConditionOperator(const Point& rhs) const
	{
		if (m_dimParameter != rhs.m_dimParameter || m_dimCriteria != rhs.m_dimCriteria)
			throw GodError("Trying to combine points with different dimensions");
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

	bool Point::isBare() const
	{
		return false;
	}
	
	size_t Point::dimParameter() const
	{
		return m_dimParameter;
	}
	
	size_t Point::dimCriteria() const
	{
		return m_dimCriteria;
	}

	double Point::parameterAt(size_t ind) const
	{
		if (ind >= m_dimParameter)
			throw GodOutOfRangeError("parameter", ind, m_dimParameter);
		return m_parameters[ind];
	}

	void Point::setParameterAt(size_t ind, double value)
	{
		if (ind >= m_dimParameter)
			throw GodOutOfRangeError("parameter", ind, m_dimParameter);
		m_parameters[ind] = value;
	}

	double* Point::parameters()
	{
		return m_parameters.get();
	}
	
	const double* Point::parameters() const
	{
		return m_parameters.get();
	}
	
	void Point::setParameters(const double* value)
	{
		if (!value)
			throw GodError("null pointers detected");
		memcpy(m_parameters.get(), value, m_dimParameter * sizeof(double));
	}


	double Point::criterionAt(size_t ind) const
	{
		if (ind >= m_dimCriteria)
			throw GodOutOfRangeError("criteria", ind, m_dimCriteria);
		return m_criteria[ind];
	}

	void Point::setCriterionAt(size_t ind, double value)
	{
		if (ind >= m_dimCriteria)
			throw GodOutOfRangeError("criteria", ind, m_dimCriteria);
		m_criteria[ind] = value;
	}

	double* Point::criteria()
	{
		return m_criteria.get();
	}
	
	const double* Point::criteria() const
	{
		return m_criteria.get();
	}
	
	void Point::setCriteria(const double* value)
	{
		if (!value)
			throw GodError("null pointers detected");
		memcpy(m_criteria.get(), value, m_dimCriteria * sizeof(double));
	}
		
	bool Point::operator<(const Point& rhs) const
	{
		Comparable c;
		return c(*this, rhs);
	}

	Point Point::operator+=(const Point& rhs)
	{
		preConditionOperator(rhs);
		for (size_t i = 0; i < m_dimParameter; ++i)
			m_parameters[i] += rhs.m_parameters[i];
		for (size_t i = 0; i < m_dimCriteria; ++i)
			m_criteria[i] += rhs.m_criteria[i];
		return *this;
	}

	Point Point::operator-=(const Point& rhs)
	{
		preConditionOperator(rhs);
		for (size_t i = 0; i < m_dimParameter; ++i)
			m_parameters[i] -= rhs.m_parameters[i];
		for (size_t i = 0; i < m_dimCriteria; ++i)
			m_criteria[i] -= rhs.m_criteria[i];
		return *this;
	}

	Point Point::operator*=(double mult)
	{ 
		for (size_t i = 0; i < m_dimParameter; ++i)
			m_parameters[i] *= mult;
		for (size_t i = 0; i < m_dimCriteria; ++i)
			m_criteria[i] *= mult;
		return *this;
	}

	Point Point::operator/=(double mult)
	{
		for (size_t i = 0; i < m_dimParameter; ++i)
			m_parameters[i] /= mult;
		for (size_t i = 0; i < m_dimCriteria; ++i)
			m_criteria[i] /= mult;
		return *this;
	}
		
	
};


