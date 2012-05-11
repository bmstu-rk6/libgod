set(GOD_SOURCES
	libgod.cxx
	godfile.cxx
	godfile.h
	godasn1.cxx
	godasn1.h
	goderror.h
	common.h
)

add_subdirectory(gen)
include_directories(gen)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(god SHARED ${GOD_SOURCES} ${GOD_GENERATED_ASN_SOURCES} ${GOD_GENERATED_SUPPORT_SOURCES})

configure_file(
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h.in"
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h"
)

if(Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
endif()

set_source_files_properties(${GOD_GENERATED_ASN_SOURCES} PROPERTIES GENERATED 1)
set_source_files_properties(${GOD_GENERATED_SUPPORT_SOURCES} PROPERTIES GENERATED 1)
add_dependencies(god generate_asn1_sources)

set_target_properties(god PROPERTIES
		VERSION ${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION} 
		SOVERSION ${LIBGOD_SOVERSION})

install(TARGETS god DESTINATION lib)
install(FILES
					${CMAKE_SOURCE_DIR}/include/libgod.h
					${CMAKE_SOURCE_DIR}/include/libgod-config.h
				DESTINATION include/libgod)
