#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"

namespace libgod
{
	Set::Set(size_t dimParameter, size_t dimCriteria)
		: Set::BaseType("set", dimParameter, dimCriteria)
	{
	}

	Set::Set (const Set& rhs)
		: Set::BaseType(rhs)
	{
	}

};


