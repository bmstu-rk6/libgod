#ifndef LIBGOD_INC__GODUNION_H
#define LIBGOD_INC__GODUNION_H

namespace libgod
{

	/**
	 * Class represents a union - ordered sets of Set.
	 * Sets are stored in a linked list for zero-cost adding 
	 * and removing.
	 * All sets must be of similar parameter and criteria dimensions.
	 * Adding wrongly shaped sets results to an exception
	 */
	class Union : public Container<Set, std::list<Set> >
	{
		/** Generic base type as a list of sets */
		typedef Container<Set, std::list<Set> > BaseType;

		/** 
		 * A bit hackish method
		 * We cant't invoke base class method
		 * not on the self
		 */
		bool invokeEquals (const Union& rhs) const;
	public:
		/** 
		 * Lazy construction an empty union without specified dimensions. 
		 * Union acquires dimensions from first inserted set */
		Union();
		/** Construct an empty union of specified dimensions */
		Union(size_t dimParameter, size_t dimCriteria);
		/** Construct a copy of exisiting union, all contents are copied*/
		Union(const Union& rhs);
		
		/** Shallow compare of two sets */
		bool operator== (const Union& rhs) const;
		/** Shallow compare of two sets */
		bool operator!= (const Union& rhs) const;

		/** Deep compare of two sets */
		bool deepEquals (const Union& rhs) const;
	};

};

#endif

