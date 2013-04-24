#ifndef LIBGOD_INC__STORAGE_H
#define LIBGOD_INC__STORAGE_H

namespace libgod
{
	class GodBridge;

	/** Storage class
	 *  Holds a persistent serializer and allows to read/write God structures
	 */
	class Storage : boost::noncopyable
	{
		/** Opaque pointer to GodBridge */
		boost::scoped_ptr<libgod::GodBridge> m_impl;
		
		/** Saved filename */
		const std::string m_file;
	public:
		/** Create a storage and link it to the filename. 
		 * Storage does read or write a file in the constructor
		 */
		Storage (const std::string& file);
		~Storage();
		/** Write a union to associated file */
		void write (const Union& aunion);
		/** Read a union from associated file */
		void read (Union& aunion);
	};
	
	// Dump XER encoding
	std::ostream& operator<< (std::ostream& os, const Union& rhs);
	std::ostream& operator<< (std::ostream& os, const Set& rhs);
	std::ostream& operator<< (std::ostream& os, const Point& rhs);
	std::ostream& operator<< (std::ostream& os, const Metadata& rhs);
	std::ostream& operator<< (std::ostream& os, const MetadataEntry& rhs);

};

#endif

