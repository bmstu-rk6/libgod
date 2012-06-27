#ifndef LIBGOD_INC__STORAGE_H
#define LIBGOD_INC__STORAGE_H

namespace libgod
{

	class StorageImpl;
	class Storage : boost::noncopyable
	{
		boost::scoped_ptr<libgod::StorageImpl> m_impl;
		
		const std::string m_file;
	public:
		Storage (const std::string& file);
		~Storage();
		void write (const Union& aunion);
		void read (Union& aunion);

		void dump (std::ostream& os, const Union& aunion);
	};

};

#endif

