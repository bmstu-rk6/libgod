#include "godtest.h"

namespace asn1
{
#include "God.h"
};
#include "godasn1.h"

namespace fileutils
{
	void readFile (std::string filename, std::vector<unsigned char>& bytes)
	{
		std::ifstream ifs(filename.c_str(), std::ios_base::binary);
		if (!ifs)
			throw libgod::GodNotFoundError(filename.c_str());

		ifs.exceptions (std::ios_base::failbit | std::ios_base::badbit);
		ifs.seekg(0, std::ios_base::end);
			
		bytes.resize(ifs.tellg());
		ifs.seekg(0, std::ios_base::beg);
		ifs.read((char*)&bytes[0], bytes.size());
	}

	bool equalsFiles(std::string filename1, std::string filename2) 
	{
		std::vector<unsigned char> bytes1, bytes2;
		readFile(filename1, bytes1);
		readFile(filename2, bytes2);
		return bytes1 == bytes2;
	}

	bool existsFile(std::string filename) 
	{
		std::ifstream ifs(filename.c_str());
		return (bool)ifs;
	}

	void removeFile(std::string filename) 
	{
		if (existsFile(filename))
		{
			if (remove(filename.c_str()))
				throw std::runtime_error("Cannot remove file " + filename);
		}
	}
};

void FileComparer::setFileName(std::string filename)
{
	m_inFilename = filename;
	m_outFilename = filename +".out";

	if (fileutils::existsFile(m_outFilename))
		fileutils::removeFile(m_outFilename);
}

/** Check file equality by XER contents (not binary contents) */
bool FileComparer::checkEquals()
{
	std::cout << "Comparing " << m_inFilename << " and " << m_outFilename << std::endl;
	//return fileutils::equalsFiles(m_inFilename, m_outFilename);

	std::stringstream ss1, ss2;
	libgod::GodASN1 ga1(m_inFilename);
	ga1.dump(ss1, ga1.getRoot().get());

	libgod::GodASN1 ga2(m_outFilename);
	ga2.dump(ss2, ga2.getRoot().get());

	return ss1.str() == ss2.str();
}


void FileComparerParametrized::SetUp()
{
	setFileName(GetParam());
}

