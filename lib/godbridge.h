#ifndef LIBGOD_INC__GODBRIDGE_H
#define LIBGOD_INC__GODBRIDGE_H

namespace libgod
{
	class GodBridge : boost::noncopyable
	{
	public:
		GodASN1 asn1Storage;

		void convertToASN1Data (const Point& apoint, asn1::Point* point);
		void convertToASN1Data (const Set& aset, asn1::Set* set);
		void convertToASN1Data (const Union& aunion, asn1::God* god);

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

