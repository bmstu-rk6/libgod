#ifndef LIBGOD_INC__GODSET_H
#define LIBGOD_INC__GODSET_H

namespace libgod
{

	class Set
	{
		typedef std::vector<Point> PointsType;

		const size_t m_dimParameter;
		const size_t m_dimCriteria;

		PointsType m_points;

	public:

		Set(size_t dimParameter, size_t dimCriteria);
		Set (const Set& rhs);
		~Set();
		Set& operator= (const Set& rhs);

		bool operator== (const Set& rhs) const;
		bool operator!= (const Set& rhs) const;

		size_t dimParameter() const;
		size_t dimCriteria() const;

		size_t pointsCount() const;

		void clear();

		Point& addPoint();
		void addPoint (const Point& point);
		void removePoint(size_t ind);

		const Point& pointAt (size_t ind) const;
		Point& pointAt (size_t ind);

		const Point& operator[] (size_t ind) const;
		Point& operator[] (size_t ind);

		void swapPoints (size_t left_ind, size_t right_ind);
	};


};

#endif

