#ifndef LIBGOD_INC__METADATA_H
#define LIBGOD_INC__METADATA_H

namespace libgod
{

	/**
	 * MetadataEntry represent a key-value pair.
	 * Used to store various user data along with optimization data
	 */
	class MetadataEntry
	{
		std::string m_name;
		std::string m_value;
	public:
		/** Create an empty metadata entry without name */
		MetadataEntry();
		/** Create a copy of metadata entry */
		MetadataEntry (const MetadataEntry& rhs);
		/** Create an metadata entry with name and value */
		MetadataEntry (std::string name, std::string value);

		/** Assign a metadata entry */
		MetadataEntry& operator= (const MetadataEntry& rhs);

		/** Return a name of metadata entry */
		std::string name() const;
		/** Return a value of metadata entry */
		std::string value() const;

		/** Compare two metadata entries by content */
		bool operator== (const MetadataEntry& rhs) const;
		/** Compare two metadata entries by content */
		bool operator!= (const MetadataEntry& rhs) const;
		/** Order two metadata entries by key, lexigographically */
		bool operator< (const MetadataEntry& rhs) const;
	};
	

	/**
	 * Metadata storage
	 * Contains a key-value storage. All metadata entries must be with unique keys.
	 */
	class Metadata
	{
		typedef std::set<MetadataEntry> MetadataSet;
	public:
		/** Iterator for underlying set */
		typedef MetadataSet::const_iterator const_iterator;

	private:
		/** Set of metadata entries, ordered by key */
		MetadataSet m_metadataSet;
		
		/** Set access by key implementation */
		const_iterator find_iterator(std::string name) const;

	public:

		/** Add a metadata entry */
		void add (const MetadataEntry& me);
		/** Remove a metadata entry specified by name */
		void remove (std::string name);
		/** Returns is there a metadata entry by specified name */
		bool is (std::string name) const;
		/** Get a metadata entry specified by name */
		const MetadataEntry& get (std::string name);
		/** Returns count of metadata entries */
		size_t size() const;
		/** Returns whether metadata contains any entries */
		bool empty() const;
		/** Begin iterator of underlying set */
		const_iterator begin() const;
		/** End iterator of underlying set */
		const_iterator end() const;
	};

};

#endif

