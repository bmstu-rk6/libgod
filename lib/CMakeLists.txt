set(GOD_INCLUDES
	${CMAKE_SOURCE_DIR}/include/comparable.h
	${CMAKE_SOURCE_DIR}/include/container.h
	${CMAKE_SOURCE_DIR}/include/goderror.h
	${CMAKE_SOURCE_DIR}/include/godmetadata.h
	${CMAKE_SOURCE_DIR}/include/godpoint.h
	${CMAKE_SOURCE_DIR}/include/godset.h
	${CMAKE_SOURCE_DIR}/include/godunion.h
	${CMAKE_SOURCE_DIR}/include/libgod.h
)

set(GOD_SOURCES
	common.h
	godasn1.cxx
	godasn1.h
	godbridge.cxx
	godbridge.h
	godmetadata.cxx
	godpoint.cxx
	godset.cxx
	godunion.cxx
	libgod.cxx
	storage.cxx
	storage.h
)

set(GOD_ALL_SOURCES 
	${GOD_INCLUDES}
	${GOD_SOURCES}
)

add_subdirectory(gen)
include_directories(gen)
include_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(god SHARED ${GOD_ALL_SOURCES} ${GOD_GENERATED_ASN_SOURCES} ${GOD_GENERATED_SUPPORT_SOURCES})

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
					${GOD_INCLUDES}
					${CMAKE_SOURCE_DIR}/include/libgod-config.h
				DESTINATION include/libgod)

