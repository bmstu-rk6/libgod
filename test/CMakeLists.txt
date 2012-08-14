include(CTest)

# all test programs

set(GOD_ALL_TESTS
	test_storage
	test_comparable
	test_equals
	testpoint
	fileread
	filereadctor
	filewrite
	testunionio
	testuniono
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

include_directories(${GTEST_INCLUDE_DIRS})

add_library(godtest STATIC ${GODTEST_SOURCES})

# tests targets

foreach(test ${GOD_ALL_TESTS})
  add_executable(${test} ${test}.cxx)
  target_link_libraries(${test} god)
  target_link_libraries(${test} godtest)
	target_link_libraries(${test} ${GTEST_BOTH_LIBRARIES})

	add_test(NAME "${test}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test})
endforeach(test ${TEST_testS})

# copy test files to the build dir

foreach(input_test ${GOD_ALL_INPUTS})
  set (dest "${PROJECT_BINARY_DIR}/${input_test}")
	if (LIBGOD_VERBOSE_TESTS)
  	message (STATUS " Copying ${input_test}")
	endif (LIBGOD_VERBOSE_TESTS)
	list(GET GOD_ALL_TESTS 0 ANY_TEST)
  add_custom_command (
			TARGET     ${ANY_TEST}
      POST_BUILD
      COMMAND    ${CMAKE_COMMAND}
			ARGS       -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/input/${input_test} ${dest}
			VERBATIM
  )
endforeach()


