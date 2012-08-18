#ifndef LIBGOD_INC__METADATA_H
#define LIBGOD_INC__METADATA_H

namespace libgod
{

	/*
	 * MetadataEntry
	 */

	class MetadataEntry
	{
		std::string m_name;
		std::string m_value;
	public:
		MetadataEntry();
		MetadataEntry (const MetadataEntry& rhs);
		MetadataEntry (std::string name, std::string value);

		MetadataEntry& operator= (const MetadataEntry& rhs);

		std::string name() const;
		std::string value() const;
		bool operator== (const MetadataEntry& rhs) const;
		bool operator!= (const MetadataEntry& rhs) const;
		bool operator< (const MetadataEntry& rhs) const;
	};
	

	/*
	 * Metadata
	 */

	class Metadata
	{
		typedef std::set<MetadataEntry> MetadataSet;
	public:
		typedef MetadataSet::const_iterator const_iterator;

	private:
		MetadataSet m_metadataSet;
		
		const_iterator find_iterator(std::string name) const;

	public:

		void add (const MetadataEntry& me);
		void remove (std::string name);
		bool is (std::string name) const;
		const MetadataEntry& get (std::string name);
		size_t size() const;
		bool empty() const;
		const_iterator begin() const;
		const_iterator end() const;
	};

};

#endif

