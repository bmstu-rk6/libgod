set(GOD_INCLUDES
    ${CMAKE_SOURCE_DIR}/include/comparable.h
    ${CMAKE_SOURCE_DIR}/include/container.h
    ${CMAKE_SOURCE_DIR}/include/goderror.h
    ${CMAKE_SOURCE_DIR}/include/godmetadata.h
    ${CMAKE_SOURCE_DIR}/include/godpoint.h
    ${CMAKE_SOURCE_DIR}/include/godset.h
    ${CMAKE_SOURCE_DIR}/include/godunion.h
    ${CMAKE_SOURCE_DIR}/include/libgod.h
    ${CMAKE_SOURCE_DIR}/include/storage.h
)

set(GOD_SOURCES
    godasn1.cxx
    godbridge.cxx
    godmetadata.cxx
    godpoint.cxx
    godset.cxx
    godunion.cxx
    libgod.cxx
    storage.cxx
)


# asn1c generation

add_subdirectory(gen)

set_source_files_properties(
    ${GOD_GENERATED_ASN_SOURCES}
    ${GOD_GENERATED_SUPPORT_SOURCES}
    PROPERTIES GENERATED 1)

# Library definition

add_library(god
    ${GOD_INCLUDES}
    ${GOD_SOURCES}
    ${GOD_GENERATED_ASN_SOURCES}
    ${GOD_GENERATED_SUPPORT_SOURCES}
)

configure_file(
    "${CMAKE_SOURCE_DIR}/include/libgod-config.h.in"
    "${CMAKE_SOURCE_DIR}/include/libgod-config.h"
)

add_dependencies(god generate_asn1_sources)

# Versions

set_target_properties(god PROPERTIES
    VERSION ${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION} 
    SOVERSION ${LIBGOD_SOVERSION})

target_include_directories(god
PUBLIC
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/lib/gen
)

set_property(TARGET god PROPERTY CXX_STANDARD 11)

# Install

install(TARGETS god DESTINATION lib)
install(FILES
    ${GOD_INCLUDES}
    ${CMAKE_SOURCE_DIR}/include/libgod-config.h
    DESTINATION include/libgod)

