#ifndef LIBGOD_INC__GODSET_H
#define LIBGOD_INC__GODSET_H

namespace libgod
{

	class Set : public Container<Point, std::vector<Point> >
	{
		typedef Container<Point, std::vector<Point> > BaseType;
	public:
		Set(size_t dimParameter, size_t dimCriteria);
		Set (const Set& rhs);
	};


};

#endif

