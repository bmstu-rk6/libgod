cmake_minimum_required (VERSION 2.6)
project(god CXX)

set(LIBGOD_MAJOR_VERSION "1")
set(LIBGOD_MINOR_VERSION "0")
set(LIBGOD_PATCH_VERSION "0")
set(LIBGOD_SOVERSION "1")

set(LIBGOD_STR_VERSION "${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
add_subdirectory(src)
add_subdirectory(examples/simple)
