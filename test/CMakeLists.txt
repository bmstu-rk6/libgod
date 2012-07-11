include(CTest)

set(GODTEST_SOURCES
	godtest.cxx
	godtest.h
)

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

set(GOD_TESTS
	${GOD_TESTS_IO}
	${GOD_TESTS_UNION_IO}
	${GOD_TESTS_OUT}
	${GOD_TESTS_PLAIN}
)
	
# test files to run for ASN/1 serilization
set(INPUT_TESTS
	input1.asn1
	input2.asn1
)

# test files to run for union serilization
set(INPUT_UNION_TESTS
	input.union1
	input.union2
	input.union3
)

# library with testing primitives
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/lib/gen)

add_library(godtest STATIC ${GODTEST_SOURCES})

foreach(test ${GOD_TESTS})
  add_executable(${test} ${test}.cxx)
  target_link_libraries(${test} god)
	target_link_libraries(${test} godtest)
endforeach(test ${TEST_testS})

# copy test files to the build dir
foreach(input_test ${INPUT_TESTS})
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

# run input+output tests
foreach(test ${GOD_TESTS_IO})
	foreach(filename ${INPUT_TESTS})
		add_test(NAME "${test}_${filename}_pre" COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
	endforeach()
endforeach()

# run input+ouput tests for Union
foreach(test ${GOD_TESTS_UNION_IO})
	foreach(filename ${INPUT_UNION_TESTS})
		add_test(NAME "${test}_${filename}_pre" COMMAND ${CMAKE_COMMAND} -E remove ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out)
		add_test(NAME "${test}_${filename}_post" COMMAND ${CMAKE_COMMAND} -E compare_files ${PROJECT_BINARY_DIR}/${filename} ${PROJECT_BINARY_DIR}/${filename}.out) 
	endforeach()
endforeach()

# run output only tests
foreach(test ${GOD_TESTS_OUT})
	foreach(filename ${INPUT_TESTS})
		add_test(NAME "${test}_${filename}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test} ${PROJECT_BINARY_DIR}/${filename})
	endforeach()
endforeach()

# run plain tests
foreach(test ${GOD_TESTS_PLAIN})
	add_test(NAME "${test}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test})
endforeach()
