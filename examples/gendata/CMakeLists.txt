project(gendata CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)

#add_executable(gendata_100p gendata_100p.cxx)
add_executable(gendata4test gendata4test.cxx)
#add_executable(printgod printgod.cxx)

#target_link_libraries(gendata_100p god)
target_link_libraries(gendata4test god)
#target_link_libraries(printgod god)
