set(GOD_SOURCES
	libgod.cxx
	godasn1.cxx
	godasn1.h
	godpoint.cxx
	godpoint.h
	godset.cxx
	godset.h
	godunion.cxx
	godunion.h
	goderror.h
	storage.cxx
	storage.h
	container.h
	common.h
	asserts.h
	comparable.h
)

add_subdirectory(gen)
include_directories(gen)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(god SHARED ${GOD_SOURCES} ${GOD_GENERATED_ASN_SOURCES} ${GOD_GENERATED_SUPPORT_SOURCES})

configure_file(
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h.in"
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h"
)

set_source_files_properties(${GOD_GENERATED_ASN_SOURCES} PROPERTIES GENERATED 1)
set_source_files_properties(${GOD_GENERATED_SUPPORT_SOURCES} PROPERTIES GENERATED 1)
add_dependencies(god generate_asn1_sources)

set_target_properties(god PROPERTIES
		VERSION ${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION} 
		SOVERSION ${LIBGOD_SOVERSION})

install(TARGETS god DESTINATION lib)
install(FILES
					${CMAKE_SOURCE_DIR}/include/libgod.h
					${CMAKE_SOURCE_DIR}/lib/goderror.h
					${CMAKE_SOURCE_DIR}/lib/container.h
					${CMAKE_SOURCE_DIR}/lib/godpoint.h
					${CMAKE_SOURCE_DIR}/lib/godset.h
					${CMAKE_SOURCE_DIR}/lib/godunion.h
					${CMAKE_SOURCE_DIR}/lib/storage.h
					${CMAKE_SOURCE_DIR}/lib/container.h
					${CMAKE_SOURCE_DIR}/lib/comparable.h
					${CMAKE_SOURCE_DIR}/include/libgod-config.h
				DESTINATION include/libgod)

