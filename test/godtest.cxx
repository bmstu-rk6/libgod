#include "godtest.h"

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


void FileComparer::setFileName(std::string inFilename)
{
	m_inFilename = inFilename;
	m_outFilename = inFilename+".out";
}

void FileComparer::SetUp()
{
	if (fileutils::existsFile(m_outFilename))
		fileutils::removeFile(m_outFilename);
}

bool FileComparer::checkEquals()
{
	return fileutils::equalsFiles(m_inFilename, m_outFilename);
}

