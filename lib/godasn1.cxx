#include "common.h"
#include <boost/shared_ptr.hpp>

namespace asn1
{
#include "God.h"
#include "Set.h"
#include "Point.h"
#include "der_encoder.h"
#include "xer_encoder.h"
};

#include "libgod.h"
#include "godasn1.h"
#include "goderror.h"

namespace libgod
{
	static int write_out(const void *buffer, size_t size, void *app_key)
	{
		std::ofstream *stream = reinterpret_cast<std::ofstream*>(app_key);
		if (!stream->write(reinterpret_cast<const char*>(buffer), size))
			return -1;
		return 0;
	}
	
	GodASN1::GodASN1()
		: m_root(new asn1::God_t)
	{
		memset(m_root.get(), 0, sizeof(asn1::God_t));
	}

	GodASN1::GodASN1 (const std::string& file)
		: m_root(new asn1::God_t)
	{
		memset(m_root.get(), 0, sizeof(asn1::God_t));
		readFromFile(file);
	}

	GodASN1::GodASN1 (const GodASN1& rhs)
	{
		*this = rhs;
	}

	GodASN1::~GodASN1()
	{
	}

	GodASN1& GodASN1::operator= (const GodASN1& rhs)
	{
		if (this == &rhs)
			return *this;

		m_root.reset(new asn1::God_t);
		memcpy(m_root.get(), rhs.m_root.get(), sizeof(asn1::God_t));
		return *this;
	}

	void GodASN1::writeToFile (const std::string& file)
	{
		asn1::asn_enc_rval_t status;
		std::ofstream ofs;
		try
		{
			ofs.open(file.c_str(), std::ios_base::binary);
			if (!ofs)
				throw GodNotFoundError(file);

			ofs.exceptions (std::ios_base::failbit | std::ios_base::badbit);
			asn1::God_t* raw = m_root.get();
			status = der_encode(&asn1::asn_DEF_God, raw, write_out, &ofs);
			if (status.encoded == -1)
				throw GodError("Can't encode data to ASN1 stream");
		}
		catch (std::exception& e)
		{
			if (ofs.is_open())
				ofs.close();
			// lose an exception
			if (unlink(file.c_str()))
				throw GodError("Encoding fails, also can't remove a file " + file);
			throw;
		}
	}

	void GodASN1::readFromFile (const std::string& file)
	{
		asn1::asn_dec_rval_t status;
		std::ifstream ifs;
		try
		{
			GodPtr temporary(new asn1::God_t);
			memset(temporary.get(), 0, sizeof(asn1::God_t));

			ifs.open(file.c_str(), std::ios_base::binary);
			if (!ifs)
				throw GodNotFoundError(file);

			ifs.exceptions (std::ios_base::failbit | std::ios_base::badbit);
			ifs.seekg(0, std::ios_base::end);
			
			std::vector<char> buf(ifs.tellg());
			ifs.seekg(0, std::ios_base::beg);
			ifs.read((char*)&buf[0], buf.size());

			asn1::God_t* raw = temporary.get();
			status = ber_decode(NULL, &asn1::asn_DEF_God, (void**)&raw, 
					&buf[0], buf.size());
			if (status.code == asn1::RC_OK)
			{
				temporary.swap(m_root);
			}
			else
			{
				asn1::asn_DEF_God.free_struct(&asn1::asn_DEF_God, raw, 0);
				throw GodError("Can't encode data to ASN1 stream");
			}
		}
		catch (std::exception& e)
		{
			if (ifs.is_open())
				ifs.close();
			throw;
		}
	}
	
	template <class ASNType, class ASNStruct>
	void genericDump (std::ostream& os, ASNType* asnType, ASNStruct* asnStruct)
	{
		asn1::asn_enc_rval_t status;
		xer_encode(asnType, asnStruct, asn1::XER_F_BASIC, write_out, &os);
		if (status.encoded == -1)
			os << "ERROR XER ENCODING";
	}

	void GodASN1::dump (std::ostream& os, asn1::God* asnStruct)
	{
		genericDump(os, &asn1::asn_DEF_God, asnStruct);
	}
	
	void GodASN1::dump (std::ostream& os, asn1::Set* asnStruct)
	{
		genericDump(os, &asn1::asn_DEF_Set, asnStruct);
	}
	
	void GodASN1::dump (std::ostream& os, asn1::Point* asnStruct)
	{
		genericDump(os, &asn1::asn_DEF_Point, asnStruct);
	}
	
	void GodASN1::dump (std::ostream& os, asn1::Metadata* asnStruct)
	{
		genericDump(os, &asn1::asn_DEF_Metadata, asnStruct);
	}
	
	void GodASN1::dump (std::ostream& os, asn1::MetadataEntry* asnStruct)
	{
		genericDump(os, &asn1::asn_DEF_MetadataEntry, asnStruct);
	}
	
	GodASN1::GodPtr GodASN1::getRoot()
	{
		return m_root;
	}
	
};

