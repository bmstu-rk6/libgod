set(GOD_GENERATED_ASN_FILES
	${CMAKE_SOURCE_DIR}/lib/gen/God.h
	${CMAKE_SOURCE_DIR}/lib/gen/God.c
)

set(GOD_GENERATED_SUPPORT_FILES
	${CMAKE_SOURCE_DIR}/lib/gen/asn_application.h
	${CMAKE_SOURCE_DIR}/lib/gen/asn_codecs.h
	${CMAKE_SOURCE_DIR}/lib/gen/asn_codecs_prim.c
	${CMAKE_SOURCE_DIR}/lib/gen/asn_codecs_prim.h
	${CMAKE_SOURCE_DIR}/lib/gen/asn_internal.h
	${CMAKE_SOURCE_DIR}/lib/gen/asn_system.h
	${CMAKE_SOURCE_DIR}/lib/gen/ber_decoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/ber_decoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/ber_tlv_length.c
	${CMAKE_SOURCE_DIR}/lib/gen/ber_tlv_length.h
	${CMAKE_SOURCE_DIR}/lib/gen/ber_tlv_tag.c
	${CMAKE_SOURCE_DIR}/lib/gen/ber_tlv_tag.h
	${CMAKE_SOURCE_DIR}/lib/gen/BIT_STRING.c
	${CMAKE_SOURCE_DIR}/lib/gen/BIT_STRING.h
	${CMAKE_SOURCE_DIR}/lib/gen/constr_TYPE.c
	${CMAKE_SOURCE_DIR}/lib/gen/constr_TYPE.h
	${CMAKE_SOURCE_DIR}/lib/gen/constraints.c
	${CMAKE_SOURCE_DIR}/lib/gen/constraints.h
	${CMAKE_SOURCE_DIR}/lib/gen/der_encoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/der_encoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/INTEGER.c
	${CMAKE_SOURCE_DIR}/lib/gen/INTEGER.h
	${CMAKE_SOURCE_DIR}/lib/gen/NativeEnumerated.c
	${CMAKE_SOURCE_DIR}/lib/gen/NativeEnumerated.h
	${CMAKE_SOURCE_DIR}/lib/gen/NativeInteger.c
	${CMAKE_SOURCE_DIR}/lib/gen/NativeInteger.h
	${CMAKE_SOURCE_DIR}/lib/gen/OCTET_STRING.c
	${CMAKE_SOURCE_DIR}/lib/gen/OCTET_STRING.h
	${CMAKE_SOURCE_DIR}/lib/gen/per_decoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/per_decoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/per_encoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/per_encoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/per_support.c
	${CMAKE_SOURCE_DIR}/lib/gen/per_support.h
	${CMAKE_SOURCE_DIR}/lib/gen/xer_decoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/xer_decoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/xer_encoder.c
	${CMAKE_SOURCE_DIR}/lib/gen/xer_encoder.h
	${CMAKE_SOURCE_DIR}/lib/gen/xer_support.c
	${CMAKE_SOURCE_DIR}/lib/gen/xer_support.h
)

# exported

set(GOD_GENERATED_ASN_SOURCES
	${GOD_GENERATED_ASN_FILES}
	PARENT_SCOPE)

set(GOD_GENERATED_SUPPORT_SOURCES
	${GOD_GENERATED_SUPPORT_FILES} 
	PARENT_SCOPE)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES Makefile.am.sample)

# generation command

add_custom_command(
		OUTPUT  ${GOD_GENERATED_ASN_FILES} ${GOD_GENERATED_SUPPORT_FILES}
		COMMAND ${ASN1C_EXECUTABLE} "${CMAKE_SOURCE_DIR}/lib/god-defs.asn"
		COMMAND rm -f Makefile.am.example
		COMMAND rm -f converter-sample.c
		DEPENDS "${CMAKE_SOURCE_DIR}/lib/god-defs.asn"
		COMMENT generating ASN definitions
		VERBATIM)

add_custom_target(generate_asn1_sources 
		DEPENDS "${CMAKE_SOURCE_DIR}/lib/god-defs.asn" ${GOD_GENERATED_ASN_FILES})
	
		
#DEPENDS ${CMAKE_SOURCE_DIR}/lib/gen/God.c ${CMAKE_SOURCE_DIR}/lib/gen/God.h)

