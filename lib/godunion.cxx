#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"
#include "godunion.h"

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
		
	bool Union::doEquals (const Union& rhs) const
	{
		return
			m_dimParameter == rhs.m_dimParameter &&
			m_dimCriteria == rhs.m_dimCriteria &&
			m_items.size() == rhs.m_items.size();
	}

	// TODO add reorder compare
	bool Union::deepEquals (const Union& rhs) const
	{
		return doEquals( rhs ) && m_items == rhs.m_items;
	}

};


