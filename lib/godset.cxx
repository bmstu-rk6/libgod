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

	size_t Set::size() const
	{
		return m_points.size();
	}
		
	void Set::clear()
	{
		m_points.clear();
	}


	Set::iterator Set::begin()
	{
		return m_points.begin();
	}

	Set::const_iterator Set::begin() const
	{
		return m_points.begin();
	}

	Set::iterator Set::end()
	{
		return m_points.end();
	}

	Set::const_iterator Set::end() const
	{
		return m_points.end();
	}

	Set::iterator Set::atIndex(size_t ind)
	{
		if (ind >= size())
			throw GodOutOfRangeError("set point ", ind, size());
		Set::iterator it = begin();
		std::advance(it, ind);
		return it;
	}

	Set::const_iterator Set::atIndex(size_t ind) const
	{
		if (ind >= size())
			throw GodOutOfRangeError("set point ", ind, size());
		Set::const_iterator it = begin();
		std::advance(it, ind);
		return it;
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
		removePoint(atIndex(ind));
	}
	
	void Set::removePoint(Set::iterator iter)
	{
		if (iter >= end())
			throw GodOutOfRangeError("set points ", std::distance(begin(), iter), size());
		m_points.erase(iter);
	}

	const Point& Set::operator[] (size_t ind) const
	{
		return *atIndex(ind);
	}

	Point& Set::operator[] (size_t ind)
	{
		return *atIndex(ind);
	}

	void Set::swapPoints (size_t left_ind, size_t right_ind)
	{
		if (left_ind >= size())
			throw GodOutOfRangeError("set points ", left_ind, size());
		if (right_ind >= size())
			throw GodOutOfRangeError("set points ", right_ind, size());
		std::swap(m_points[left_ind], m_points[right_ind]);
	}
};


