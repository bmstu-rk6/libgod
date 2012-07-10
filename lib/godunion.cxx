#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"
#include "godunion.h"
#include "comparable.h"

namespace libgod
{
	Union::Union()
		: Union::BaseType("union")
	{
	}

	Union::Union(size_t dimParameter, size_t dimCriteria)
		: Union::BaseType("union", dimParameter, dimCriteria)
	{
	}

	Union::Union (const Union& rhs)
		: Union::BaseType(rhs)
	{
	}
		
	bool Union::operator== (const Union& rhs) const
	{
		return 
				dimParameter() == rhs.dimParameter() &&
				dimCriteria() == rhs.dimCriteria() &&
				size() == rhs.size();
	}

	bool Union::operator!= (const Union& rhs) const
	{
		return !(*this == rhs);
	}

	// TODO let deepEquals to ignore set order
	bool Union::deepEquals (const Union& rhs) const
	{
		return Union::BaseType::deepEquals(rhs);
	}
	
};


