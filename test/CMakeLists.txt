include(CTest)

# all test programs

set(GOD_ALL_TESTS
	fileread
	filereadctor
	testuniono
	testunionio
	testpoint
	filewrite
	test_storage
	test_equals
	test_comparable
)

# libgod::Point tests
set(GOD_POINT_TESTS
	testpoint_constructor_neg_parms
	testpoint_constructor_null_ptrs
	testpoint_constructor_array_less_dim
	testpoint_constructor_array_larger_dim
	testpoint_constructor_array_eq_ptr
	testpoint_constructor_array_init
	testpoint_constructor_copy
	testpoint_setSomethingAt
	testpoint_delete_init_arrays
	testpoint_setParameters
	testpoint_setCriteria
	testpoint_setget_with_neg_index
	testpoint_equal_operator
	testpoint_assignment_operator
)



# all test data files

set(GOD_ALL_INPUTS
	input1.asn1
	input2.asn1
	input.union1
	input.union2
	input.union3
	input.union3.bin
)

# library with testing primitives

set(GODTEST_SOURCES
	godtest.cxx
	godtest.h
)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/lib/gen)

add_library(godtest STATIC ${GODTEST_SOURCES})


# tests targets

foreach(test ${GOD_ALL_TESTS})
  add_executable(${test} ${test}.cxx)
  target_link_libraries(${test} god)
	target_link_libraries(${test} godtest)
endforeach(test ${TEST_testS})

# copy test files to the build dir

foreach(input_test ${GOD_ALL_INPUTS})
  set (dest "${PROJECT_BINARY_DIR}/${input_test}")
	if (LIBGOD_VERBOSE_TESTS)
  	message (STATUS " Copying ${input_test}")
	endif (LIBGOD_VERBOSE_TESTS)
  add_custom_command (
      TARGET     godtest
      POST_BUILD
      COMMAND    ${CMAKE_COMMAND}
			ARGS       -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/input/${input_test} ${dest}
			VERBATIM
  )
endforeach()


# adds a test and prints it's command line

macro(add_test_verbose)
	if (LIBGOD_VERBOSE_TESTS)
		message(STATUS "Generated test ${ARGV}")
	endif (LIBGOD_VERBOSE_TESTS)
	add_test(${ARGV})
endmacro(add_test_verbose)

# shortut macro for input-output test
# assume that a test reads ARG1 file and write the exactyle same ARG2 file
# test compares both files and both if they are not same
macro(def_test_input_output test filename)
	add_test(NAME "${test}_${filename}_pre" COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${filename}.out)
	add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
	add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
endmacro(def_test_input_output)

# shortut macro for output test
# assume that a test writes an ARG2 file
macro(def_test_output test filename)
	add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename})
endmacro(def_test_output)

# assume that a test writes an ARG2+"_out" and compare it with ARG2 file 
macro(def_test_output_cmp test filename)
	add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename})
	add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
endmacro(def_test_output_cmp)

# shortut macro for a simple test
macro(def_test_plain test)
	add_test_verbose(NAME "${test}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test})
endmacro(def_test_plain)

# shorcut macro for simple test and ARG2 as parameter
macro(def_test_plain_arg testname testexec arg)
	add_test_verbose(NAME "${testname}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${testexec} ${arg})
endmacro(def_test_plain_arg)


# --------------------------------------------------------
# actual test defintions

def_test_output(testuniono nofound)
def_test_output_cmp(testuniono input.union1)
def_test_output_cmp(testuniono input.union2)
def_test_output_cmp(testuniono input.union3)
#def_test_output(testuniono input.unionrand)

def_test_input_output(testunionio input.union1)
def_test_input_output(testunionio input.union2)
def_test_input_output(testunionio input.union3)
#def_test_input_output(testunionio input.unionrand)

def_test_input_output(fileread input1.asn1)
def_test_input_output(fileread input2.asn1)

def_test_input_output(filereadctor input1.asn1)
def_test_input_output(filereadctor input2.asn1)

def_test_output(filewrite input1.asn1)
def_test_output(filewrite input2.asn1)

def_test_output(test_storage input1.asn1)
def_test_output(test_storage input2.asn1)

def_test_plain(test_equals)
def_test_plain(test_comparable)

# Test libgod::Point
MATH(EXPR i "1")
foreach(testname ${GOD_POINT_TESTS})
	def_test_plain_arg(${testname} testpoint ${i})
	MATH(EXPR i "${i}+1")
endforeach()


