#include "godtest.h"

class FileUnionOTest : public FileComparer
{
};

// Returns a point that was read from .bin file prepared by gendata4test program
libgod::Point readPoint (size_t dp, size_t dc, std::ifstream& file)
{
	libgod::Point p(dp,dc);
	
	size_t ind = 0;
	double *p_data = new double [dp+dc];
	
	file.read((char*)p_data, sizeof(double)*(dp+dc));
	
	for (size_t i=0; i < dp; i++) {
		p.setParameterAt(i,p_data[ind]);
		ind++;
	}
	for (size_t i=0; i < dc; i++) {
		p.setCriterionAt(i,p_data[ind]);
		ind++;
	}

	delete(p_data);
	
	return p;
}

// Returns a point with random parameters and criteria
libgod::Point randPoint (size_t dp, size_t dc) {
	libgod::Point p(dp,dc);
	
	for (size_t i = 0; i < dp; i++)
		p.setParameterAt(i, 1.0 * rand() / RAND_MAX);
	for (size_t i = 0; i < dc; i++)
		p.setCriterionAt(i, 1.0 * rand() / RAND_MAX);
		
	return p;
}

// Test 1. Check that exception is thrown if input file isn't found
TEST_F(FileUnionOTest, notfound)
{
	setFileName("../notfound");

	libgod::Union un1;	
	EXPECT_THROW(libgod::Storage(m_inFilename).read(un1), libgod::GodError);
}

// Test 2. Check that saved union corresponds with ideal data file
// Union with 1 empty set
TEST_F(FileUnionOTest, union1)
{
	setFileName("../input.union1");
	
	libgod::Storage st(m_outFilename);
	libgod::Union un(10,7);
	un.add();
			
	st.write(un);

	EXPECT_TRUE(checkEquals());
}

// Test 3. Union with 2 sets, 2 points each
TEST_F(FileUnionOTest, union2)
{
	setFileName("../input.union2");

	libgod::Storage st(m_outFilename);
	libgod::Union un(5,3);
	double parameters[] = {1.2, -0.9, 6.7, 1.209, 4.731};
	double criteria[] = {0.99, 0.76, 0.12};

	for (int i=0; i<2; i++) {
		libgod::Set& s = un.add();
		for (int j=0; j<2; j++) {
			libgod::Point& p = s.add();
			p.setParameters(parameters);
			p.setCriteria(criteria);
		}
	}

	st.write(un);

	EXPECT_TRUE(checkEquals());
}

// Test 4. Union wirh 10 sets, (i+1)*10 points each
// --------------------------------------------------
// NOTE: each time when input.union3 is regenerated by gendata4test, 
//       input.union3.bin aslo should be refreshed
TEST_F(FileUnionOTest, union3)
{
	setFileName("../input.union3");

	const size_t dp = 2, dc = 3;
	libgod::Storage st(m_outFilename);
	libgod::Union un(dp,dc);

	std::ifstream datafile;
	datafile.open((m_inFilename+".bin").c_str(), std::ios::binary | std::ios::in);

	for (int i=0; i<10; i++) {
		libgod::Set& s = un.add();
		for (int j=0; j<(i+1); j++) {
			s.add(readPoint(dp,dc,datafile));
		}
	}

	st.write(un);
	datafile.close();

	EXPECT_TRUE(checkEquals());
}
	
	// Test 5. Serialization of random Union size > 20 MB.
	//	Number of points = 600000
	//	Number of sets   = 1000
TEST_F(FileUnionOTest, DISABLED_processrand)
{
	setFileName("../input.unionrand");

	const size_t dp = 3, dc = 2;
	const size_t dsets = 1000, dpoints_per_set = 600;

	libgod::Storage st(m_outFilename);
	libgod::Union un(dp, dc);

	for (int i=0; i<dsets; i++) {
		libgod::Set& s = un.add();
		for (int j=0; j < dpoints_per_set; j++)
			s.add(randPoint(dp,dc));
	}

	st.write(un);

	EXPECT_TRUE(checkEquals());
}
