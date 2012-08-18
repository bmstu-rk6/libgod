#ifndef LIBGOD_INC__GODBRIDGE_H
#define LIBGOD_INC__GODBRIDGE_H

namespace libgod
{
	class GodBridge : boost::noncopyable
	{
	private:

		void convertFromASN1Data (Metadata& ametadata, const asn1::Metadata* metadata);
	public:
		GodASN1 asn1Storage;

		void convertToASN1Data (const Point& apoint, asn1::Point* point);
		void convertToASN1Data (const Set& aset, asn1::Set* set);
		void convertToASN1Data (const Union& aunion, asn1::God* god);
		void convertToASN1Data (const Metadata& ametadata, asn1::Metadata* metadata);
		void convertToASN1Data (const MetadataEntry& ametadataEntry, asn1::MetadataEntry* metadataEntry);

		void convertFromASN1Data (Union& aunion, const asn1::God* god);
	};
	
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

