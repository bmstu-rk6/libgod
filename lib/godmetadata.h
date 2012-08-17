#ifndef LIBGOD_INC__METADATA_H
#define LIBGOD_INC__METADATA_H

namespace libgod
{

	class MetadataEntry
	{
		std::string m_name;
		std::string m_value;
	public:
		MetadataEntry()
		{
		}

		MetadataEntry (const MetadataEntry& rhs)
			: m_name(rhs.m_name),
				m_value(rhs.m_value)
		{
		}

		MetadataEntry (std::string name, std::string value)
			: m_name(name),
				m_value(value)
		{
		}

		MetadataEntry& operator= (const MetadataEntry& rhs)
		{
			m_name = rhs.m_name;
			m_value = rhs.m_value;
			return *this;
		}

		std::string name() const
		{
			return m_name;
		}
		
		std::string value() const
		{
			return m_value;
		}

		bool operator== (const MetadataEntry& rhs) const
		{
			return m_name == rhs.m_name && m_value == rhs.m_value;
		}
	
		bool operator< (const MetadataEntry& rhs) const
		{
			return m_name < rhs.m_name;
		}
	};
	
	inline std::ostream& operator<< (std::ostream& os, const MetadataEntry& rhs)
	{
		os << rhs.name() << "=" << rhs.value();
		return os;
	}



	class Metadata
	{
		typedef std::set<MetadataEntry> MetadataSet;

		MetadataSet m_metadataSet;
		
		MetadataSet::const_iterator find_iterator(std::string name) const
		{
			return m_metadataSet.find(MetadataEntry(name,""));
		}

	public:

		Metadata()
		{
		}

		void add (const MetadataEntry& me)
		{
			m_metadataSet.insert(me);
		}

		void remove (std::string name)
		{
			m_metadataSet.erase(MetadataEntry(name,""));
		}

		bool is (std::string name) const
		{
			return find_iterator(name) != m_metadataSet.end();
		}

		const MetadataEntry& get (std::string name)
		{
			MetadataSet::const_iterator it = find_iterator(name);
			if (it == m_metadataSet.end())
				throw GodError("Metadata entry " + name + " not found");
			return *it;
		}

		size_t size() const
		{
			return m_metadataSet.size();
		}
	};


};

#endif

