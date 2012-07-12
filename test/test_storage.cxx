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

int main(int argc, char* argv[])
{
	INIT_TEST(1);
	try
	{
		const size_t dp = 2, dc = 3; 
		{
			libgod::Union aunion(dp,dc);

			libgod::Set& aset1 = aunion.add();
			aset1.add(randPoint(dp,dc));
			aset1.add(randPoint(dp,dc));
			
			ASSERT_EQUAL(aunion.size(), 1);
			ASSERT_EQUAL(aunion[0].size(), 2);
			
			libgod::Set& aset2 = aunion.add();
			aset2.add(randPoint(dp,dc));
			aset2.add(randPoint(dp,dc));
			aset2.add(randPoint(dp,dc));

			ASSERT_EQUAL(aunion.size(), 2);
			ASSERT_EQUAL(aunion[1].size(), 3);
			ASSERT_EQUAL(aunion[0].size(), 2);

			ASSERT_EQUAL(aunion.dimParameter(), dp);
			ASSERT_EQUAL(aunion[0].dimParameter(), dp);
			ASSERT_EQUAL(aunion[0][0].dimParameter(), dp);


			// storage tests
			libgod::Storage storage(argv[1]);
			storage.write(aunion);
			std::cout << aunion;
			
			libgod::Union nunion(dp,dc);
			storage.read(nunion);
			std::cout << nunion;
			
			ASSERT_EQUAL(aunion.size(), dp);
			ASSERT_EQUAL(aunion.size(), nunion.size());
			
			// test reading from a non-existent file
			{
				bool is_thrown = false;
				try
				{
					libgod::Union u;
					libgod::Storage storage(std::string(argv[1]) + "_does_not_exists");
					storage.read(u);
				}
				catch (libgod::GodError& ge)
				{
					is_thrown = true;
				}
				ASSERT_TRUE(is_thrown);
			}

			// test operator<<
			// TODO make more deep test, now we are sure
			// that they doesn't fail
			std::cout << aunion << std::endl;
			std::cout << aset1 << std::endl;
			std::cout << aset1[0] << std::endl;
			

		}

	}
	catch (std::exception& e)
	{
		std::cerr << "Test error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
