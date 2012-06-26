#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"
#include "godunion.h"

namespace libgod
{
	Union::Union(size_t dimParameter, size_t dimCriteria)
		: Union::BaseType("union", dimParameter, dimCriteria)
	{
	}

	Union::Union (const Union& rhs)
		: Union::BaseType(rhs)
	{
	}

};


