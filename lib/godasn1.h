#ifndef INC__GODASN1_H
#define INC__GODASN1_H

namespace libgod
{

	class GodASN1
	{
	protected:
		typedef boost::shared_ptr<God_t> GodPtr;
		GodPtr m_root;
	public:
		GodASN1();

		GodASN1 (const GodASN1& rhs);

		~GodASN1();

		GodASN1& operator= (const GodASN1& rhs);

		void writeToFile (const std::string& file);
		void readFromFile (const std::string& file);

		friend std::ostream& operator<< (std::ostream& os, const GodASN1& rhs);
	};

/*	class GodFile
	{
		God_t m_root;
		std::string m_fileName;
	public:
		GodASN1();

		GodASN1 (const GodASN1& rhs);

		~GodASN1();

		GodASN1& operator= (const GodASN1& rhs);

		std::string getFileName () const;
		void setFileName (const std::string fileName) const;
	};*/

};

#endif
