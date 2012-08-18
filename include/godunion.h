#ifndef LIBGOD_INC__GODUNION_H
#define LIBGOD_INC__GODUNION_H

namespace libgod
{

	class Union : public Container<Set, std::list<Set> >
	{
		typedef Container<Set, std::list<Set> > BaseType;

		bool invokeEquals (const Union& rhs) const;
	protected:
		// Union has light equals for operator==
		//virtual bool doEquals (const Union& rhs) const;
	public:
		Union();
		Union(size_t dimParameter, size_t dimCriteria);
		Union(const Union& rhs);
		
		bool operator== (const Union& rhs) const;
		bool operator!= (const Union& rhs) const;
		bool deepEquals (const Union& rhs) const;
	};

};

#endif

