cmake_minimum_required (VERSION 3.1)
project(gendata CXX)

add_executable(gendata4test gendata4test.cxx)
add_executable(printgod printgod.cxx)
target_link_libraries(gendata4test god)
target_link_libraries(printgod god)
