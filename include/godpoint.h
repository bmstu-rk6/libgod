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

		/** Construct a bare point with specified dimensions, all values are set to 0 */
		Point(size_t dimParameter, size_t dimCriteria);
		/** Construct a point with specified dimensions, values are initialized from parameters and criteria arrays */
		Point(size_t dimParameter, size_t dimCriteria, const double* parameters, const double* criteria);
		/** Construct a copy of exisiting point, all contents are copied*/
		Point (const Point& rhs);
		~Point();
		/** Assigment operator, deep copy */
		Point& operator= (const Point& rhs);

		/** Deep comparison operator */
		bool operator== (const Point& rhs) const;

		/** Point is always non-bare */
		bool isBare() const;

		/** Returns count of parameters */
		size_t dimParameter() const;
		/** Returns count of criteria */
		size_t dimCriteria() const;

		/** @name Parameters accessors functions
		  * Modify criteria at given indices, range check is always performed
  		* @{*/
		double parameterAt(size_t ind) const;
		void setParameterAt(size_t ind, double value);
		double* parameters();
		const double* parameters() const;
		void setParameters(const double* value);
		/**@}*/

		/** @name Criteria accessors functions 
		 * Modify criteria at given indices, range check is always performed
		* @{*/
		double criterionAt(size_t ind) const;
		void setCriterionAt(size_t ind, double value);
		double* criteria();
		const double* criteria() const;
		void setCriteria(const double* value);
		/**@}*/

		/** @name Operators support
		 * boost::operators support, provides following operators: <=, >=, >, +, -, /, *, !=
		* @{*/
		bool operator<(const Point& rhs) const;
		Point operator+=(const Point& rhs);
		Point operator-=(const Point& rhs);
		Point operator*=(double mult);
		Point operator/=(double mult);
		/**@}*/
	};


};

#endif

