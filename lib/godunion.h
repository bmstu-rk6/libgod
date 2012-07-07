#ifndef LIBGOD_INC__GODUNION_H
#define LIBGOD_INC__GODUNION_H

namespace libgod
{

	class Union : public Container<Set, std::list<Set> >
	{
		typedef Container<Set, std::list<Set> > BaseType;
	public:
		Union(size_t dimParameter, size_t dimCriteria);
		Union(const Union& rhs);
		Union();
	};

};

#endif

