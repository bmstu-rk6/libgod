#include "common.h"
#include "libgod.h"
#include "godmetadata.h"

namespace libgod
{
	/*
	 * MetadataEntry
	 */

	MetadataEntry::MetadataEntry()
	{
	}

	MetadataEntry::MetadataEntry (const MetadataEntry& rhs)
		: m_name(rhs.m_name),
		m_value(rhs.m_value)
	{
	}

	MetadataEntry::MetadataEntry (std::string name, std::string value)
		: m_name(name),
		m_value(value)
	{
	}

	MetadataEntry& MetadataEntry::operator= (const MetadataEntry& rhs)
	{
		m_name = rhs.m_name;
		m_value = rhs.m_value;
		return *this;
	}

	std::string MetadataEntry::name() const
	{
		return m_name;
	}

	std::string MetadataEntry::value() const
	{
		return m_value;
	}

	bool MetadataEntry::operator== (const MetadataEntry& rhs) const
	{
		return m_name == rhs.m_name && m_value == rhs.m_value;
	}

	bool MetadataEntry::operator!= (const MetadataEntry& rhs) const
	{
		return !(*this == rhs);
	}

	bool MetadataEntry::operator< (const MetadataEntry& rhs) const
	{
		return m_name < rhs.m_name;
	}
	

	/*
	 * Metadata
	 */
		
	Metadata::const_iterator Metadata::find_iterator(std::string name) const
	{
		return m_metadataSet.find(MetadataEntry(name,""));
	}

	void Metadata::add (const MetadataEntry& me)
	{
		if (is(me.name()))
			throw GodError("Metadata entry " + me.name() + " already exists");
		m_metadataSet.insert(me);
	}

	void Metadata::remove (std::string name)
	{
		if (!is(name))
			throw GodError("Metadata entry " + name + " does not exist");
		m_metadataSet.erase(MetadataEntry(name,""));
	}

	bool Metadata::is (std::string name) const
	{
		return find_iterator(name) != m_metadataSet.end();
	}

	const MetadataEntry& Metadata::get (std::string name)
	{
		const_iterator it = find_iterator(name);
		if (it == m_metadataSet.end())
			throw GodError("Metadata entry " + name + " does not exist");
		return *it;
	}

	size_t Metadata::size() const
	{
		return m_metadataSet.size();
	}

	bool Metadata::empty() const
	{
		return m_metadataSet.empty();
	}

	Metadata::const_iterator Metadata::begin() const
	{
		return m_metadataSet.begin();
	}

	Metadata::const_iterator Metadata::end() const
	{
		return m_metadataSet.end();
	}



};
