#ifndef LIBGOD_INC__GODBRIDGE_H
#define LIBGOD_INC__GODBRIDGE_H

namespace libgod
{
	/**
	 * God Bridge is a class for conversion domain objects (Point, Set and Union)
	 * to corresponding ASN.1 serialized objects
	 */
	class GodBridge : boost::noncopyable
	{
	private:

		void convertFromASN1Data (Metadata& ametadata, const asn1::Metadata* metadata);
	public:
		/** ASN.1 storage object for conversions */
		GodASN1 asn1Storage;

		/** Convert a domain object to corresponding ASN.1 objects
		 * @{*/
		void convertToASN1Data (const Point& apoint, asn1::Point* point);
		void convertToASN1Data (const Set& aset, asn1::Set* set);
		void convertToASN1Data (const Union& aunion, asn1::God* god);
		void convertToASN1Data (const Metadata& ametadata, asn1::Metadata* metadata);
		void convertToASN1Data (const MetadataEntry& ametadataEntry, asn1::MetadataEntry* metadataEntry);
		/**@}*/

		/** Convert a top level ASN.1 god object to the Union object */
		void convertFromASN1Data (Union& aunion, const asn1::God* god);
	};
	
	/** Dump a domain object to the XER ASN.1 representation
	 * Uses a GodBridge inside
	 */
	template <class ASNStruct, class T>
	void genericDump(std::ostream& os, const T& rhs)
	{
		GodBridge bridge;
		ASNStruct asnStruct;
		bridge.convertToASN1Data(rhs, &asnStruct);
		bridge.asn1Storage.dump(os, &asnStruct);
	}


};

#endif

