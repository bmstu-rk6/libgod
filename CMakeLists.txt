cmake_minimum_required (VERSION 3.1)
project(god C CXX)

set(LIBGOD_MAJOR_VERSION "1")
set(LIBGOD_MINOR_VERSION "0")
set(LIBGOD_PATCH_VERSION "0")
set(LIBGOD_SOVERSION "1")

set(LIBGOD_STR_VERSION "${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION}")

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(ASN1C REQUIRED) 
find_package(Boost REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(Doxygen)

if(Boost_FOUND)
	include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
	add_definitions(/W2)
elseif(CMAKE_COMPILER_IS_GNUCC)
	add_definitions(-Wall -Wno-sign-compare)
endif()

option(BUILD_DOCUMENTATION "Use Doxygen to create documentation" OFF)
if(BUILD_DOCUMENTATION)
  if (NOT DOXYGEN_FOUND)
    message(FATAL_ERROR 
      "Doxygen is needed to build the documentation. Please install it correctly")
  endif()
	# add a target to generate API documentation with Doxygen
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(BUILD_DOCUMENTATION)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(examples/simple)
add_subdirectory(examples/gendata)
