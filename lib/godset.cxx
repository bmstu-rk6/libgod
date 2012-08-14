#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"

namespace libgod
{

	Set::Set()
		: Set::BaseType("set")
	{
	}

	Set::Set(size_t dimParameter, size_t dimCriteria)
		: Set::BaseType("set", dimParameter, dimCriteria)
	{
	}

	Set::Set (const Set& rhs)
		: Set::BaseType(rhs)
	{
	}

	bool Set::operator== (const Set& rhs) const
	{
		return deepEquals(rhs);
	}

	bool Set::operator!= (const Set& rhs) const
	{
		return !(*this == rhs);
	}
};


