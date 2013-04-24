#ifndef LIBGOD_INC__GODSET_H
#define LIBGOD_INC__GODSET_H

namespace libgod
{

	/**
	 * Class represents ordered set of Point.
	 * All points must be of similar parameter and criteria dimensions.
	 * Adding wrongly shaped points results to an exception
	 */
	class Set : public Container<Point, std::vector<Point> >
	{
		/** Generic base type as a vector of points */
		typedef Container<Point, std::vector<Point> > BaseType;
	public:
		/** 
		 * Lazy construction an empty set without specified dimensions. 
		 * Set acquires dimensions from first inserted point */
		Set();
		/** Construct an empty set of specified dimensions */
		Set(size_t dimParameter, size_t dimCriteria);
		/** Construct a copy of exisiting set, all contents are copied */
		Set (const Set& rhs);

		/** Shallow compare of two sets */
		bool operator== (const Set& rhs) const;
		/** Shallow compare of two sets */
		bool operator!= (const Set& rhs) const;
	};


};

#endif

