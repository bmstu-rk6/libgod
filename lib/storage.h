#ifndef LIBGOD_INC__STORAGE_H
#define LIBGOD_INC__STORAGE_H

namespace libgod
{
	// Storage class
	// Holds a persistent serializer and allows to read/write God structures
	class GodBridge;
	class Storage : boost::noncopyable
	{
		boost::scoped_ptr<libgod::GodBridge> m_impl;
		
		const std::string m_file;
	public:
		Storage (const std::string& file);
		~Storage();
		void write (const Union& aunion);
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

