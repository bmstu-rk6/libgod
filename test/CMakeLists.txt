include(CTest)

if (BUILD_TESTING)

# all test programs

set(GOD_ALL_TESTS
    test_storage
    test_comparable
    test_equals
    testpoint
    testasn1
    testunionio
    testuniono
    testmetadata
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

find_package(GTest REQUIRED)

# library with testing primitives

add_library(godtest STATIC godtest.cxx)
target_link_libraries(godtest god)

set_property(TARGET godtest PROPERTY CXX_STANDARD 11)

# tests targets

foreach(test ${GOD_ALL_TESTS})
    add_executable(${test} ${test}.cxx)
    target_link_libraries(${test} godtest)
    target_link_libraries(${test} GTest::gtest GTest::gtest_main ${CMAKE_THREAD_LIBS_INIT})

    set_property(TARGET ${test} PROPERTY CXX_STANDARD 11)

    add_test(NAME "${test}" COMMAND ${CMAKE_BINARY_DIR}/bin/${test})
endforeach(test ${TEST_testS})

# copy test files to the build dir

foreach(input_test ${GOD_ALL_INPUTS})
    set (dest "${PROJECT_BINARY_DIR}/${input_test}")
    message (STATUS " Copying ${input_test}")
    list(GET GOD_ALL_TESTS 0 ANY_TEST)
    add_custom_command (
        TARGET     ${ANY_TEST}
        POST_BUILD
        COMMAND    ${CMAKE_COMMAND}
        ARGS       -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/input/${input_test} ${dest}
        VERBATIM
        )
endforeach()

endif()

