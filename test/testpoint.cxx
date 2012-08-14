#include "godtest.h"

// Pass zero and negative parameters to ligbod::Point constuctor
TEST(Point, NegativeParms)
{
	EXPECT_THROW(	libgod::Point(0,10), libgod::GodError);
	EXPECT_THROW(	libgod::Point(0,10), libgod::GodError);
	EXPECT_THROW(	libgod::Point(10,0), libgod::GodError);
	EXPECT_THROW(	libgod::Point(0,0), libgod::GodError);

	// NOTE: it should NOT throw because negative ints are converted to size_t
	#if 0
	EXPECT_THROW(   libgod::Point(-3,2), libgod::GodError);
	EXPECT_THROW(   libgod::Point(20,-7), libgod::GodError);
	EXPECT_THROW(   libgod::Point(-15,-33), libgod::GodError);
	#endif
}

// Pass not valid pointers to libgod::Point constructor
TEST(Point, constructor_null_ptrs)
{
	double a[5];
	EXPECT_THROW( libgod::Point(7,2, a, 0), libgod::GodError);
	EXPECT_THROW( libgod::Point(7,2, 0, a), libgod::GodError);
	EXPECT_THROW( libgod::Point(3,4, 0, 0), libgod::GodError);
}

// Pass pointers to array smaller than specified in dimensions
// NOTE: should work because we don't know array dimensions by the pointer
// 			 may fail or not
#if 0
TEST(Point, constructor_array_less_dim)
{
	double* a = new double [4];
	double* b = new double [1];
	EXPECT_THROW( libgod::Point(7,1,a,b), libgod::GodError);
	EXPECT_THROW( libgod::Point(1,7,b,a), libgod::GodError);
}
#endif

// Pass pointers to array smaller than specified in dimensions
// NOTE: should work because we don't know array dimensions by the pointer
TEST(Point, constructor_array_larger_dim)
{
	double* a = new double [10];
	double* b = new double [6];
	EXPECT_NO_THROW( libgod::Point(4,3,a,b));
}

// Pass equal pointers to array
TEST(Point, constructor_array_eq_ptr)
{
	double* a = new double [10];
	EXPECT_THROW( libgod::Point(10,10,a,a), libgod::GodError);
}

// Check correctness of constructor work
TEST(Point, constructor_array_init)
{
	size_t dp = 49, dc = 32;
	
	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	libgod::Point pt(dp, dc, p, c);
	
	// Check correctness of paramter and criteria sets saved into internal structures
	for (size_t i = 0; i < dp; i++)
		EXPECT_EQ(p[i], pt.parameterAt(i));
		
	for (size_t i = 0; i < dc; i++)
		EXPECT_EQ(c[i], pt.criterionAt(i));
}

// Check copy constructor work
void constructor_copy_helper()
{
	size_t dp = 3, dc = 2;
	double p[] = {1.2, -3.4, 0.93};
	double c[] = {5.2, -0.5};

	libgod::Point pt(dp,dc,p,c);
	libgod::Point pt_copy(pt);

	// Check equality of poin parameters
	EXPECT_EQ(pt.dimParameter(), pt_copy.dimParameter());
	EXPECT_EQ(pt.dimCriteria(), pt_copy.dimCriteria());

	// Check equality of parameter and criteria sets
	for (size_t i = 0; i < dp; i++)
		EXPECT_EQ(pt.parameterAt(i), pt_copy.parameterAt(i));

	for (size_t i = 0; i < dc; i++)
		EXPECT_EQ(pt.criterionAt(i), pt_copy.criterionAt(i));

	// Change some points in initial pt, check that pt_copy doesn't change
	pt.setParameterAt(2, 10.109);
	EXPECT_NE(pt.parameterAt(2), pt_copy.parameterAt(2));

	pt.setCriterionAt(1, -0.97);
	EXPECT_NE(pt.criterionAt(1), pt_copy.criterionAt(1));
}

TEST(Point, constructor_copy)
{
	EXPECT_NO_THROW(constructor_copy_helper());
}

// Check setCriterionAt and setParamterAt functions
void setSomethingAt_helper()
{
	size_t dp = 10, dc = 4;

	double* p = new double [dp];
	double* c = new double [dc];

	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;

	libgod::Point pt(dp, dc, p, c);

	// Change some criterion and paramter
	pt.setParameterAt(7, p[7] * 3);
	pt.setCriterionAt(2, c[2] * 2);

	// Check that only specific paramter and criterion are changed
	for (size_t i = 0; i < dp; i++) {
		if (i ==  7) 
			EXPECT_EQ(pt.parameterAt(i), p[i]*3);
		else
			EXPECT_EQ(pt.parameterAt(i), p[i]);
	}

	for (size_t i = 0; i < dc; i++) {
		if (i ==  2) 
			EXPECT_EQ(pt.criterionAt(i), c[i]*2);
		else
			EXPECT_EQ(pt.criterionAt(i), c[i]);
	}
}

TEST(Point, setSomethingAt)
{
	EXPECT_NO_THROW(setSomethingAt_helper());
}

// Check point correctness if user deletes or modifies initial arrays
void delete_init_arrays_helper()
{
	size_t dp = 3, dc = 5;

	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;

	libgod::Point pt(dp, dc, p, c);

	// Delete p and c and check that pt is OK
	delete(p);
	delete(c);

	for (size_t i = 0; i < dp; i++)
		pt.setParameterAt(i, 1.0);
	for (size_t i = 0; i < dc; i++)
		pt.setCriterionAt(i, -1.0);
}

TEST(Point, delete_init_arrays)
{
	EXPECT_NO_THROW(delete_init_arrays_helper());
}

void setParameters_helper()
{
	size_t dp = 5;

	double* p = new double [dp];
	
	// Generate random array
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	
	libgod::Point pt(4,3);

	// In this case it saves only part of p[] that can fit to pt		
	pt.setParameters(p);

	for (size_t i = 0; i < dp; i++)
		EXPECT_EQ(p[i], pt.parameterAt(i));
}

TEST(Point, setParameters)
{
	EXPECT_THROW(setParameters_helper(), libgod::GodError);
}

void setCriteria_helper()
{
	size_t dc = 5;

	double* c = new double [dc];
	
	// Generate random array
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	libgod::Point pt(2,3);

	// In this case it saves only part of c[] that can fit to pt
	pt.setCriteria(c);

	for (size_t i = 0; i < dc; i++)
		EXPECT_EQ(c[i], pt.criterionAt(i));
}

TEST(Point, setCriteria)
{
	EXPECT_THROW(setCriteria_helper(), libgod::GodError);
}

// does NOT properly work because negative indicies are
// just large unsigned size_t numbers
#if 0
TEST(Point, setget_with_neg_index)
{
	libgod::Point pt(2,3);
	
	// Check setParameterAt negative with negative parameter index
	EXPECT_NO_THROW(pt.setParameterAt(-2, 1.0));
	
	// Check parameterAt negative with negative parameter index
	EXPECT_THROW(pt.parameterAt(-98121), libgod::GodError);
	
	// Check setCriterionAt negative with negative criteria index
	EXPECT_NO_THROW(pt.setCriterionAt(-259.1, 1.0));
	
	// Check criterionAt negative with negative criteria index
	EXPECT_NO_THROW(pt.criterionAt(-98122121));
}
#endif

TEST(Point, equal_operator)
{
	size_t dp = 2, dc = 3;
	
	double* p = new double [dp];
	double* c = new double [dc];
	double* p2 = new double [dp];
	double* c2 = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++) {
		p[i] = 1.0 * rand() / RAND_MAX;
		p2[i] = 1.0 * rand() / RAND_MAX;
	}
	for (size_t i = 0; i < dc; i++) {
		c[i] = 1.0 * rand() / RAND_MAX;
		c2[i] = 1.0 * rand() / RAND_MAX;
	}

	libgod::Point pt1(dp, dc, p, c);
	libgod::Point pt2(pt1);
	libgod::Point pt3(dc, dp, c, p);
	libgod::Point pt4(dp, dc);
	libgod::Point pt5(dp, dc, p2, c2);

	EXPECT_TRUE( pt1 == pt2);
	EXPECT_FALSE(pt1 != pt2);
	EXPECT_TRUE( pt1 != pt3);
	EXPECT_FALSE(pt1 == pt3);
	EXPECT_TRUE( pt1 != pt4);
	EXPECT_FALSE(pt1 == pt4);
	EXPECT_TRUE( pt1 != pt5);
	EXPECT_FALSE(pt1 == pt5);
}

TEST(Point, assignment_operator)
{
	size_t dp = 3, dc = 5;
	
	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	// Check that assignment operator works correctly for equal points
	libgod::Point pt1(dp, dc, p, c);
	libgod::Point pt2(dp, dc);
		
	pt2 = pt1;
		
	EXPECT_EQ(pt1, pt2);
	
	// Check that points with different metrics couldn't be assigned
	
	libgod::Point pt3(dp, dc, p, c);
	libgod::Point pt4(dp+1, dc+1);
		
	EXPECT_THROW(pt4 = pt3, libgod::GodError);
}

