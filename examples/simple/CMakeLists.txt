cmake_minimum_required (VERSION 3.1)
project(simple CXX)

add_executable(simple simple.cxx)
target_link_libraries(simple god)
