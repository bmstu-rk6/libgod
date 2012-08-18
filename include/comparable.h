#ifndef LIBGOD_INC__ORDER_H
#define LIBGOD_INC__ORDER_H

namespace libgod
{

	/**
	 * Provides less-than comparators for point, set and union
	 */
	class Comparable
	{
		bool compareParameters(const Point& left, const Point& right) const
		{
			return 
				std::lexicographical_compare(
					left.parameters(), left.parameters() + left.dimParameter(),
					right.parameters(), right.parameters() + right.dimParameter());
		}

		bool compareCriteria(const Point& left, const Point& right) const
		{
			return 
				std::lexicographical_compare(
					left.criteria(), left.criteria() + left.dimCriteria(),
					right.criteria(), right.criteria() + right.dimCriteria());
		}

		template <class T>
		bool compareGeneric (const T& left, const T& right) const
		{
			if (left.isBare() && !right.isBare()) return true;
			if (right.isBare() && !left.isBare()) return false;
			if (left.dimParameter() < right.dimParameter()) return true;
			if (right.dimParameter() < left.dimParameter()) return false;
			if (left.dimCriteria() < right.dimCriteria()) return true;
			if (right.dimCriteria() < left.dimCriteria()) return false;
			if (std::lexicographical_compare(left.begin(), left.end(), 
						right.begin(), right.end(), *this)) 
				return true;
			if (std::lexicographical_compare(right.begin(), right.end(), 
						left.begin(), left.end(), *this)) 
				return false;
			return false;
		}

	public:
		
		bool operator() (const Point& left, const Point& right) const
		{
			if (compareParameters(left,right)) return true;
			if (compareParameters(right,left)) return false;
			if (compareCriteria(left,right)) return true;
			if (compareCriteria(right,left)) return false;
			return false;
		}

		bool operator() (const Set& left, const Set& right) const
		{
			return compareGeneric(left, right);
		}
		
		bool operator() (const Union& left, const Union& right) const
		{
			return compareGeneric(left, right);
		}
	};


};

#endif

