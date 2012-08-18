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
		
		bool operator!= (const MetadataEntry& rhs) const
		{
			return !(*this == rhs);
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

	public:

		typedef MetadataSet::const_iterator const_iterator;

	private:
		MetadataSet m_metadataSet;
		
		const_iterator find_iterator(std::string name) const
		{
			return m_metadataSet.find(MetadataEntry(name,""));
		}

	public:

		Metadata()
		{
		}

		void add (const MetadataEntry& me)
		{
			if (is(me.name()))
					throw GodError("Metadata entry " + me.name() + " already exists");
			m_metadataSet.insert(me);
		}

		void remove (std::string name)
		{
			if (!is(name))
				throw GodError("Metadata entry " + name + " does not exist");
			m_metadataSet.erase(MetadataEntry(name,""));
		}

		bool is (std::string name) const
		{
			return find_iterator(name) != m_metadataSet.end();
		}

		const MetadataEntry& get (std::string name)
		{
			const_iterator it = find_iterator(name);
			if (it == m_metadataSet.end())
				throw GodError("Metadata entry " + name + " does not exist");
			return *it;
		}

		size_t size() const
		{
			return m_metadataSet.size();
		}

		bool empty() const
		{
			return m_metadataSet.empty();
		}

		const_iterator begin() const
		{
			return m_metadataSet.begin();
		}
		
		const_iterator end() const
		{
			return m_metadataSet.end();
		}
		
	};


};

#endif

