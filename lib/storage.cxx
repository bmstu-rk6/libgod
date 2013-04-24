#include "common.h"
#include "libgod.h"
#include "container.h"
#include "godpoint.h"
#include "godset.h"
#include "godunion.h"
#include "goderror.h"
#include "storage.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace asn1
{
#include "God.h"
}
#endif
#include "godasn1.h"
#include "godbridge.h"

namespace libgod
{


	Storage::Storage (const std::string& file)
		:	m_impl(new GodBridge),
			m_file(file)
	{
	}

	Storage::~Storage()
	{
	}

	void Storage::write (const Union& aunion)
	{
		m_impl->convertToASN1Data(aunion, m_impl->asn1Storage.getRoot().get());
		m_impl->asn1Storage.writeToFile(m_file);
	}

	void Storage::read (Union& aunion)
	{
		m_impl->asn1Storage.readFromFile(m_file);
		m_impl->convertFromASN1Data(aunion, m_impl->asn1Storage.getRoot().get());
	}
	
	std::ostream& operator<< (std::ostream& os, const Metadata& rhs)
	{
		genericDump<asn1::Metadata, Metadata>(os,rhs);
		return os;
	}
	
	std::ostream& operator<< (std::ostream& os, const MetadataEntry& rhs)
	{
		genericDump<asn1::MetadataEntry, MetadataEntry>(os,rhs);
		return os;
	}
	
	std::ostream& operator<< (std::ostream& os, const Union& rhs)
	{
		genericDump<asn1::God, Union>(os,rhs);
		return os;
	}

	std::ostream& operator<< (std::ostream& os, const Set& rhs)
	{
		genericDump<asn1::Set, Set>(os,rhs);
		return os;
	}

	std::ostream& operator<< (std::ostream& os, const Point& rhs)
	{
		genericDump<asn1::Point, Point>(os,rhs);
		return os;
	}


};
