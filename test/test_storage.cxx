#include "godtest.h"
#include "comparable.h"

libgod::Point randPoint (size_t dp, size_t dc)
{
	libgod::Point p(dp,dc);
	for (size_t i = 0; i < dp; ++i)
		p.setParameterAt(i, 1.0 * rand() / RAND_MAX);
	for (size_t i = 0; i < dc; ++i)
		p.setCriterionAt(i, 1.0 * rand() / RAND_MAX);
	return p;
}

const size_t dp = 2, dc = 3; 

TEST(Storage, Numeric)
{
	libgod::Union aunion(dp,dc);

	libgod::Set& aset1 = aunion.add();
	aset1.add(randPoint(dp,dc));
	aset1.add(randPoint(dp,dc));

	ASSERT_EQ(aunion.size(), 1);
	EXPECT_EQ(aunion[0].size(), 2);

	libgod::Set& aset2 = aunion.add();
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));

	ASSERT_EQ(aunion.size(), 2);
	EXPECT_EQ(aunion[1].size(), 3);
	EXPECT_EQ(aunion[0].size(), 2);

	ASSERT_EQ(aunion.dimParameter(), dp);
	EXPECT_EQ(aunion[0].dimParameter(), dp);
	EXPECT_EQ(aunion[0][0].dimParameter(), dp);
}

TEST(Storage, ReadWrite)
{
	libgod::Union aunion(dp,dc);

	libgod::Set& aset1 = aunion.add();
	aset1.add(randPoint(dp,dc));
	aset1.add(randPoint(dp,dc));

	libgod::Set& aset2 = aunion.add();
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));
	aset2.add(randPoint(dp,dc));

	std::ostringstream oss;

	libgod::Storage storage("tmp.asn1");
	storage.write(aunion);
	oss << aunion;

	libgod::Union nunion(dp,dc);
	storage.read(nunion);
	oss << nunion;

	EXPECT_EQ(aunion.size(), dp);
	EXPECT_EQ(aunion.size(), nunion.size());
}

void ReadNonExistentFileHelper()
{
	libgod::Union u;
	libgod::Storage storage(std::string("___file_does_not_exists"));
	storage.read(u);
}

TEST(Storage, ReadNonExistentFile)
{
	ASSERT_THROW(ReadNonExistentFileHelper(), libgod::GodError);
}

TEST(Storage, StreamOut)
{
	libgod::Union aunion(dp,dc);

	libgod::Set& aset = aunion.add();
	aset.add(randPoint(dp,dc));
	aset.add(randPoint(dp,dc));

	// test operator<<
	// TODO make more deep test, now we are sure
	// that they doesn't fail
	std::ostringstream oss;
	oss << aunion << std::endl;
	oss << aset << std::endl;
	oss << aset[0] << std::endl;
}

