#ifndef LIBGOD_INC__GODPOINT_H
#define LIBGOD_INC__GODPOINT_H

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
		Point(size_t dimParameter, size_t dimCriteria, const double* parameters, const double* criteria);
		Point (const Point& rhs);
		~Point();
		Point& operator= (const Point& rhs);

		bool operator== (const Point& rhs) const;
		bool operator!= (const Point& rhs) const;

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
	};


};

#endif

