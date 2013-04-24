#ifndef LIBGOD_INC__GODPOINT_H
#define LIBGOD_INC__GODPOINT_H

namespace libgod
{

	/**
	 * Class represents a point.
	 * Point contains a vector of parameters and a vector of criteria.
	 * Points supports natural arithmetic, comparison operations.
	 */
	class Point 
    : boost::addable< Point
    , boost::subtractable< Point     
    , boost::equality_comparable< Point
    , boost::partially_ordered< Point
    , boost::dividable< Point, double
    , boost::multipliable< Point, double
      > > > > > >
	{
		typedef boost::scoped_array<double> ArrayType;

		const size_t m_dimParameter;
		const size_t m_dimCriteria;

		ArrayType m_parameters;
		ArrayType m_criteria;
		
		void preConditionOperator(const Point& rhs) const;

	public:

		Point(size_t dimParameter, size_t dimCriteria);
		Point(size_t dimParameter, size_t dimCriteria, const double* parameters, const double* criteria);
		Point (const Point& rhs);
		~Point();
		Point& operator= (const Point& rhs);

		bool operator== (const Point& rhs) const;

		bool isBare() const;

		size_t dimParameter() const;
		size_t dimCriteria() const;

		double parameterAt(size_t ind) const;
		void setParameterAt(size_t ind, double value);
		double* parameters();
		const double* parameters() const;
		void setParameters(const double* value);

		double criterionAt(size_t ind) const;
		void setCriterionAt(size_t ind, double value);
		double* criteria();
		const double* criteria() const;
		void setCriteria(const double* value);

		// boost::operators support
		// boost provides following operators: <=, >=, >, +, -, /, *, !=
		bool operator<(const Point& rhs) const;
		Point operator+=(const Point& rhs);
		Point operator-=(const Point& rhs);
		Point operator*=(double mult);
		Point operator/=(double mult);
	};


};

#endif

