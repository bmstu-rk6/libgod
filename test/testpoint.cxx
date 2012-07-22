#include "godtest.h"

// Pass zero and negative parameters to ligbod::Point constuctor
int testpoint_constructor_neg_parms() {
	bool is_thrown = false;
	
	try {
		libgod::Point pt1(0,10);
		libgod::Point pt2(10,0);
		libgod::Point pt3(0,0);
		libgod::Point pt4(-3,2);
		libgod::Point pt5(20,-7);
		libgod::Point pt6(-15,-33);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	
	return !is_thrown;
}

// Pass not valid pointers to libgod::Point constructor
int testpoint_constructor_null_ptrs() {
	bool is_thrown = false;
	
	double a[5];
	
	try {
		libgod::Point pt1(7,2, a, 0);
		libgod::Point pt2(7,2, 0, a);
		libgod::Point pt3(3,4, 0, 0);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	
	return !is_thrown;
}

// Pass pointers to array smaller than specified in dimensions
int testpoint_constructor_array_less_dim() {
	bool is_thrown = false;
	
	double* a = new double [4];
	double* b = new double [1];
	
	try {
		libgod::Point pt1(7,1,a,b);
		libgod::Point pt2(1,7,b,a);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	
	// Exception shouldn't be thrown since memory is allocated more
	// then will be copied. 
	ASSERT_TRUE(!is_thrown);
	
	delete(a);
	delete(b);
	
	return is_thrown;
}

// Pass pointers to array smaller than specified in dimensions
int testpoint_constructor_array_larger_dim() {
	bool is_thrown = false;
	
	double* a = new double [10];
	double* b = new double [6];
	
	try {
		libgod::Point pt1(4,3,a,b);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	
	delete(a);
	delete(b);
	
	return !is_thrown;
}

// Pass equal pointers to array
int testpoint_constructor_array_eq_ptr() {
	bool is_thrown = false;
	
	double* a = new double [10];
	
	try {
		libgod::Point pt1(10,10,a,a);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	
	delete(a);
	
	return !is_thrown;
}

// Check correctness of constructor work
int testpoint_constructor_array_init() {
	size_t dp = 49, dc = 32;
	
	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	try {
		libgod::Point pt(dp, dc, p, c);
		
		// Check correctness of paramter and criteria sets saved into internal structures
		for (size_t i = 0; i < dp; i++)
			ASSERT_EQUAL(p[i], pt.parameterAt(i));
			
		for (size_t i = 0; i < dc; i++)
			ASSERT_EQUAL(c[i], pt.criterionAt(i));
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_constructor_array_init) error: " << ge.what() << std::endl;
	}
	
	delete(p);
	delete(c);
	
	return 0;
}

// Check copy constructor work
int testpoint_constructor_copy() {
	size_t dp = 3, dc = 2;
	double p[] = {1.2, -3.4, 0.93};
	double c[] = {5.2, -0.5};
	
	try {
		libgod::Point pt(dp,dc,p,c);
		libgod::Point pt_copy(pt);
		
		// Check equality of poin parameters
		ASSERT_EQUAL(pt.dimParameter(), pt_copy.dimParameter());
		ASSERT_EQUAL(pt.dimCriteria(), pt_copy.dimCriteria());
		
		// Check equality of parameter and criteria sets
		for (size_t i = 0; i < dp; i++)
			ASSERT_EQUAL(pt.parameterAt(i), pt_copy.parameterAt(i));
			
		for (size_t i = 0; i < dc; i++)
			ASSERT_EQUAL(pt.criterionAt(i), pt_copy.criterionAt(i));
			
		// Change some points in initial pt, check that pt_copy doesn't change
		pt.setParameterAt(2, 10.109);
		ASSERT_NONEQUAL(pt.parameterAt(2), pt_copy.parameterAt(2));
		
		pt.setCriterionAt(1, -0.97);
		ASSERT_NONEQUAL(pt.criterionAt(1), pt_copy.criterionAt(1));
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_constructor_copy) error: " << ge.what() << std::endl;
	}
	
	return 0;
}

// Check setCriterionAt and setParamterAt functions
int testpoint_setSomethingAt() {
	size_t dp = 10, dc = 4;
	
	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	try {
		libgod::Point pt(dp, dc, p, c);
		
		// Change some criterion and paramter
		pt.setParameterAt(7, p[7] * 3);
		pt.setCriterionAt(2, c[2] * 2);
		
		// Check that only specific paramter and criterion are changed
		for (size_t i = 0; i < dp; i++) {
			if (i ==  7) 
				ASSERT_EQUAL(pt.parameterAt(i), p[i]*3);
			else
				ASSERT_EQUAL(pt.parameterAt(i), p[i]);
		}
		
		for (size_t i = 0; i < dc; i++) {
			if (i ==  2) 
				ASSERT_EQUAL(pt.criterionAt(i), c[i]*2);
			else
				ASSERT_EQUAL(pt.criterionAt(i), c[i]);
		}
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_setSomethingAt) error: " << ge.what() << std::endl;
	}
	
	delete(p);
	delete(c);
	
	return 0;
}

// Check point correctness if user deletes or modifies initial arrays
int testpoint_delete_init_arrays() {
	size_t dp = 3, dc = 5;

	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;

	try {
		libgod::Point pt(dp, dc, p, c);
		
		// Delete p and c and check that pt is OK
		delete(p);
		delete(c);
		
		for (size_t i = 0; i < dp; i++)
			pt.setParameterAt(i, 1.0);
		for (size_t i = 0; i < dc; i++)
			pt.setCriterionAt(i, -1.0);
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_delete_init_arrays) error: " << ge.what() << std::endl;
	}
	
	return 0;
}

int testpoint_setParameters() {
	size_t dp = 5;
	bool is_thrown = false;

	double* p = new double [dp];
	
	// Generate random array
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	
	try {
		libgod::Point pt(4,3);

		// In this case it saves only part of p[] that can fit to pt		
		pt.setParameters(p);
		
		for (size_t i = 0; i < dp; i++)
			ASSERT_EQUAL(p[i], pt.parameterAt(i));
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);

	delete(p);

	return !is_thrown;
}

int testpoint_setCriteria() {
	size_t dc = 5;
	bool is_thrown = false;

	double* c = new double [dc];
	
	// Generate random array
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	try {
		libgod::Point pt(2,3);
		
		// In this case it saves only part of c[] that can fit to pt
		pt.setCriteria(c);
		
		for (size_t i = 0; i < dc; i++)
			ASSERT_EQUAL(c[i], pt.criterionAt(i));
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);

	delete(c);

	return !is_thrown;
}

int testpoint_setget_with_neg_index() {
	bool is_thrown = false;

	libgod::Point pt(2,3);
	
	// Check setParameterAt negative with negative parameter index
	try {
		pt.setParameterAt(-2, 1.0);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	is_thrown = false;
	
	// Check parameterAt negative with negative parameter index
	try {
		pt.parameterAt(-98121);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	is_thrown = false;
	
	// Check setCriterionAt negative with negative criteria index
	try {
		pt.setCriterionAt(-259, 1.0);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	is_thrown = false;
	
	// Check criterionAt negative with negative criteria index
	try {
		pt.criterionAt(-98122121);
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	ASSERT_TRUE(is_thrown);
	
	return 0;
}

int testpoint_equal_operator() {
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
	
	try {
		libgod::Point pt1(dp, dc, p, c);
		libgod::Point pt2(pt1);
		libgod::Point pt3(dc, dp, c, p);
		libgod::Point pt4(dp, dc);
		libgod::Point pt5(dp, dc, p2, c2);
		
		ASSERT_TRUE(pt1 == pt2);
		ASSERT_TRUE(!(pt1 != pt2));
		ASSERT_TRUE(pt1 != pt3);
		ASSERT_TRUE(!(pt1 == pt3));
		ASSERT_TRUE(pt1 != pt4);
		ASSERT_TRUE(!(pt1 == pt4));
		ASSERT_TRUE(pt1 != pt5);
		ASSERT_TRUE(!(pt1 == pt5));
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_equal_operator) error: " << ge.what() << std::endl;
	}
	
	return 0;
}

int testpoint_assignment_operator() {
	size_t dp = 3, dc = 5;
	
	double* p = new double [dp];
	double* c = new double [dc];
	
	// Generate random arrays
	for (size_t i = 0; i < dp; i++)
		p[i] = 1.0 * rand() / RAND_MAX;
	for (size_t i = 0; i < dc; i++)
		c[i] = 1.0 * rand() / RAND_MAX;
	
	// Check that assignment operator works correctly for equal points
	try {
		libgod::Point pt1(dp, dc, p, c);
		libgod::Point pt2(dp, dc);
		
		pt2 = pt1;
		
		ASSERT_TRUE(pt1 == pt2);
	}
	catch (libgod::GodError& ge) {
		std::cerr << "Test (testpoint_assignment_operator) error: " << ge.what() << std::endl;
	}
	
	// Check that points with different metrics couldn't be assigned
	bool is_thrown;
	
	try {
		libgod::Point pt1(dp, dc, p, c);
		libgod::Point pt2(dp+1, dc+1);
		
		pt2 = pt1;
	}
	catch (libgod::GodError& ge) {
		is_thrown = true;
	}
	
	ASSERT_TRUE(is_thrown);
	
	return 0;
}

int main (int argc, char *argv[]) {
	INIT_TEST(1);
	
	// Note: I suppose that tests aren't require special cases check
	// since smart people are supposed to use it
	int option = atoi(argv[1]);
	
	switch (option) {
		case 1: 	return testpoint_constructor_neg_parms();
		case 2:		return testpoint_constructor_null_ptrs();
		case 3: 	return testpoint_constructor_array_less_dim();
		case 4: 	return testpoint_constructor_array_larger_dim();
		case 5: 	return testpoint_constructor_array_eq_ptr();
		case 6: 	return testpoint_constructor_array_init();
		case 7: 	return testpoint_constructor_copy();
		case 8: 	return testpoint_setSomethingAt();
		case 9: 	return testpoint_delete_init_arrays();
		case 10: 	return testpoint_setParameters();
		case 11:	return testpoint_setCriteria();
		case 12:	return testpoint_setget_with_neg_index();
		case 13:	return testpoint_equal_operator();
		case 14:	return testpoint_assignment_operator();
		default: 	break;
	}
	
	return 0;
}
