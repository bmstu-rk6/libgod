#ifndef INC__GODASN1_H
#define INC__GODASN1_H

// forward declaration for an ASN.1 generated serializer
// do not want to leak them to a client
//struct God;

namespace libgod
{

	/**
	 * GodASN1 wraps ASN.1 initialization and serialization 
	 */
	class GodASN1
	{
	public:
		/** Shared pointer to god ASN.1 object */
		typedef boost::shared_ptr<asn1::God> GodPtr;
	private:
		GodPtr m_root;
	public:
		/** Construct a wrapper from the file and init a god ASN.1 object to zeroes */
		GodASN1();

		/** Construct a wrapper from the file and read god ASN.1 object */
		GodASN1 (const std::string& file);

		/** Construct a copy of wrapper */
		GodASN1 (const GodASN1& rhs);

		~GodASN1();

		/** Assign a wrapper */
		GodASN1& operator= (const GodASN1& rhs);

		/** Returns a pointer to god ASN.1 object */ 
		GodPtr getRoot();

		/** Write a god object to the file */
		void writeToFile (const std::string& file);
		/** Read a god object from the file */
		void readFromFile (const std::string& file);

		/** @name Pretty stream dump functions
		 * Dump a XER representation of ASN.1 structures to the
		 * specified ostream.
		 * @{*/
		void dump (std::ostream& os, asn1::God* asnStruct);
		void dump (std::ostream& os, asn1::Set* asnStruct);
		void dump (std::ostream& os, asn1::Point* asnStruct);
		void dump (std::ostream& os, asn1::Metadata* asnStruct);
		void dump (std::ostream& os, asn1::MetadataEntry* asnStruct);
		/**@}*/
	};

};

#endif
