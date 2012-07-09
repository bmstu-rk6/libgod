cmake_minimum_required (VERSION 2.6)
project(god C CXX)

set(LIBGOD_MAJOR_VERSION "1")
set(LIBGOD_MINOR_VERSION "0")
set(LIBGOD_PATCH_VERSION "0")
set(LIBGOD_SOVERSION "1")

set(LIBGOD_STR_VERSION "${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(ASN1C REQUIRED) 
find_package(Boost REQUIRED)

if(Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
endif()

enable_testing()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(examples/simple)
add_subdirectory(examples/gendata)
