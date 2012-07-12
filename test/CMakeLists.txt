include(CTest)

# common library

set(GODTEST_SOURCES
	godtest.cxx
	godtest.h
)

# ------------------------
# all test programs
#


# tests for comparing read-and-write ASN.1 loop
set(GOD_TESTS_IO
	fileread
	filereadctor
)

# tests for comparing read-and-write Union
set(GOD_TESTS_UNION_IO
	testunionio
)

# tests for generating ASN.1
set(GOD_TESTS_OUT
	filewrite
	test_storage
)

# plain tests without parameters
set(GOD_TESTS_PLAIN
	test_equals
	test_comparable
)


# must list here all test sources

set(GOD_ALL_TESTS
	${GOD_TESTS_IO}
	${GOD_TESTS_UNION_IO}
	${GOD_TESTS_OUT}
	${GOD_TESTS_PLAIN}
)


# ------------------------
# all test data files
#
	
# test files to run for ASN/1 serilization
set(INPUT_RW_TESTS
	input1.asn1
	input2.asn1
)

# test files to run for union serilization
set(INPUT_UNION_TESTS
	input.union1
	input.union2
	input.union3
)

set(GOD_ALL_INPUTS
	${INPUT_RW_TESTS}
	${INPUT_UNION_TESTS}
)

# must list here all test sources


# library with testing primitives
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
  message (STATUS " Copying ${input_test}")
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

# run input+output tests
foreach(test ${GOD_TESTS_IO})
	foreach(filename ${INPUT_RW_TESTS})
		add_test(NAME "${test}_${filename}_pre" COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
	endforeach()
endforeach()

# run input+ouput tests for Union
foreach(test ${GOD_TESTS_UNION_IO})
	foreach(filename ${INPUT_UNION_TESTS})
		add_test(NAME "${test}_${filename}_pre" COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out) 
	endforeach()
endforeach()

# run output only tests
foreach(test ${GOD_TESTS_OUT})
	foreach(filename ${INPUT_RW_TESTS})
		add_test_verbose(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename})
	endforeach()
endforeach()

# run plain tests
foreach(test ${GOD_TESTS_PLAIN})
	add_test_verbose(NAME "${test}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test})
endforeach()
