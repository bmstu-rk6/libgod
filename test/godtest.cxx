#include "godtest.h"

namespace fileutils
{
	int compareFiles(FILE* f1, FILE* f2) 
	{
		int N = 10000;
		char buf1[N];
		char buf2[N];
		
		do {
			size_t r1 = fread(buf1, 1, N, f1);
			size_t r2 = fread(buf2, 1, N, f2);

			if (r1 != r2 || memcmp(buf1, buf2, r1)) {
				return 0; 
			}
		} while (!feof(f1) && !feof(f2));

		return feof(f1) && feof(f2);
	}

	bool equalsFiles(std::string filename1, std::string filename2) 
	{
		FILE *f1 = fopen(filename1.c_str(), "r");
		FILE *f2 = fopen(filename2.c_str(), "r");
		bool result = f1 && f2 && compareFiles(f1, f2);
		if (f1)
			fclose(f1);
		if (f2)
			fclose(f2);
		return result;
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

