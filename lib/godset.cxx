#include "common.h"
#include "libgod.h"
#include "godpoint.h"
#include "godset.h"

namespace libgod
{
	Set::Set(size_t dimParameter, size_t dimCriteria)
		: m_dimParameter(dimParameter),
		m_dimCriteria(dimCriteria)
	{
		if (m_dimParameter <= 0 || m_dimCriteria <= 0)
			throw GodError("dimensions should be posititive");
	}

	Set::Set (const Set& rhs)
		: m_dimParameter(rhs.m_dimParameter),
			m_dimCriteria(rhs.m_dimCriteria),
			m_points(rhs.m_points)
	{
		if (m_dimParameter <= 0 || m_dimCriteria <= 0)
			throw GodError("dimensions should be posititive");
	}

	Set::~Set()
	{
	}

	Set& Set::operator= (const Set& rhs)
	{
		if (this != &rhs)
		{
			if (m_dimParameter != rhs.m_dimParameter || 
					m_dimCriteria != rhs.m_dimCriteria)
			{
				throw GodError("cannot assign point with a different metric");
			}
			m_points = rhs.m_points;
		}
		return *this;
	}

	bool Set::operator== (const Set& rhs) const
	{
		return
			m_dimParameter == rhs.m_dimParameter &&
			m_dimCriteria == rhs.m_dimCriteria &&
			m_points == rhs.m_points;
	}

	bool Set::operator!= (const Set& rhs) const
	{
		return !(*this == rhs);
	}
		
	size_t Set::dimParameter() const
	{
		return m_dimParameter;
	}
	
	size_t Set::dimCriteria() const
	{
		return m_dimCriteria;
	}

	
	size_t Set::pointsCount() const
	{
		return m_points.size();
	}
		
	void Set::clear()
	{
		m_points.clear();
	}
		
	Point& Set::addPoint()
	{
		m_points.push_back(Point(m_dimParameter, m_dimCriteria));
		return m_points.back();
	}

	void Set::addPoint (const Point& point)
	{
		if (point.dimParameter() != m_dimParameter ||
				point.dimCriteria() != m_dimCriteria)
			throw GodError("added point has a different dimension than a set");
		m_points.push_back(point);
	}
	
	void Set::removePoint(size_t ind)
	{
		if (ind >= m_points.size())
			throw GodOutOfRangeError("set points ", ind, m_points.size());
		m_points.erase(m_points.begin() + ind);
	}

	const Point& Set::pointAt (size_t ind) const
	{
		if (ind >= m_points.size())
			throw GodOutOfRangeError("set points ", ind, m_points.size());
		return m_points[ind];
	}

	Point& Set::pointAt (size_t ind)
	{
		if (ind >= m_points.size())
			throw GodOutOfRangeError("set points ", ind, m_points.size());
		return m_points[ind];
	}

	const Point& Set::operator[] (size_t ind) const
	{
		return pointAt(ind);
	}

	Point& Set::operator[] (size_t ind)
	{
		return pointAt(ind);
	}

	void Set::swapPoints (size_t left_ind, size_t right_ind)
	{
		if (left_ind >= m_points.size())
			throw GodOutOfRangeError("set points ", left_ind, m_points.size());
		if (right_ind >= m_points.size())
			throw GodOutOfRangeError("set points ", right_ind, m_points.size());
		std::swap(m_points[left_ind], m_points[right_ind]);
	}
};


