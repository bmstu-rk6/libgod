#ifndef INC__GODASN1_H
#define INC__GODASN1_H

// forward declaration for an ASN.1 generated serializer
// do not want to leak them to a client
//struct God;

namespace libgod
{

	// Class wraps ASN.1 initialization and serialization 
	class GodASN1
	{
	public:
		typedef boost::shared_ptr<asn1::God> GodPtr;
	private:
		GodPtr m_root;
	public:
		GodASN1();

		GodASN1 (const std::string& file);

		GodASN1 (const GodASN1& rhs);

		~GodASN1();

		GodASN1& operator= (const GodASN1& rhs);

		GodPtr getRoot();

		void writeToFile (const std::string& file);
		void readFromFile (const std::string& file);

		friend std::ostream& operator<< (std::ostream& os, const GodASN1& rhs);
	};

};

#endif
