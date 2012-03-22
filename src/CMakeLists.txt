set(GOD_SOURCES
	libgod.cxx
)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(god SHARED ${GOD_SOURCES})

configure_file(
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h.in"
	"${CMAKE_SOURCE_DIR}/include/libgod-config.h"
)

find_package(TASN1 REQUIRED) 
if (TASN1_FOUND)
	include_directories(${TASN1_INCLUDE_DIRS})
	target_link_libraries(god ${TASN1_LIBRARIES})
endif (TASN1_FOUND)

set_target_properties(god PROPERTIES
		VERSION ${LIBGOD_MAJOR_VERSION}.${LIBGOD_MINOR_VERSION}.${LIBGOD_PATCH_VERSION} 
		SOVERSION ${LIBGOD_SOVERSION})

install(TARGETS god DESTINATION lib)
install(FILES
					${CMAKE_SOURCE_DIR}/include/libgod.h
					${CMAKE_SOURCE_DIR}/include/libgod-config.h
				DESTINATION include/libgod)
