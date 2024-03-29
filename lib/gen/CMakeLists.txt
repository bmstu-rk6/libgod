set(GOD_GENERATED_ASN_FILES
    ${CMAKE_BINARY_DIR}/lib/gen/Set.c
    ${CMAKE_BINARY_DIR}/lib/gen/Set.h
    ${CMAKE_BINARY_DIR}/lib/gen/Union.c
    ${CMAKE_BINARY_DIR}/lib/gen/Union.h
    ${CMAKE_BINARY_DIR}/lib/gen/God.c
    ${CMAKE_BINARY_DIR}/lib/gen/God.h
    ${CMAKE_BINARY_DIR}/lib/gen/Header.c
    ${CMAKE_BINARY_DIR}/lib/gen/Header.h
    ${CMAKE_BINARY_DIR}/lib/gen/Metadata.c
    ${CMAKE_BINARY_DIR}/lib/gen/Metadata.h
    ${CMAKE_BINARY_DIR}/lib/gen/MetadataEntry.c
    ${CMAKE_BINARY_DIR}/lib/gen/MetadataEntry.h
    ${CMAKE_BINARY_DIR}/lib/gen/Metric.c
    ${CMAKE_BINARY_DIR}/lib/gen/Metric.h
    ${CMAKE_BINARY_DIR}/lib/gen/Point.c
    ${CMAKE_BINARY_DIR}/lib/gen/Point.h
    ${CMAKE_BINARY_DIR}/lib/gen/Points.c
    ${CMAKE_BINARY_DIR}/lib/gen/Points.h
    ${CMAKE_BINARY_DIR}/lib/gen/Version.c
    ${CMAKE_BINARY_DIR}/lib/gen/Version.h
    )

set(GOD_GENERATED_SUPPORT_FILES
    ${CMAKE_BINARY_DIR}/lib/gen/asn_application.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_codecs.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_codecs_prim.c
    ${CMAKE_BINARY_DIR}/lib/gen/asn_codecs_prim.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_internal.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_SEQUENCE_OF.c
    ${CMAKE_BINARY_DIR}/lib/gen/asn_SEQUENCE_OF.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_SET_OF.c
    ${CMAKE_BINARY_DIR}/lib/gen/asn_SET_OF.h
    ${CMAKE_BINARY_DIR}/lib/gen/asn_system.h
    ${CMAKE_BINARY_DIR}/lib/gen/ber_decoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/ber_decoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/ber_tlv_length.c
    ${CMAKE_BINARY_DIR}/lib/gen/ber_tlv_length.h
    ${CMAKE_BINARY_DIR}/lib/gen/ber_tlv_tag.c
    ${CMAKE_BINARY_DIR}/lib/gen/ber_tlv_tag.h
    ${CMAKE_BINARY_DIR}/lib/gen/BIT_STRING.c
    ${CMAKE_BINARY_DIR}/lib/gen/BIT_STRING.h
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SEQUENCE.c
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SEQUENCE.h
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SEQUENCE_OF.c
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SEQUENCE_OF.h
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SET_OF.c
    ${CMAKE_BINARY_DIR}/lib/gen/constr_SET_OF.h
    ${CMAKE_BINARY_DIR}/lib/gen/constr_TYPE.c
    ${CMAKE_BINARY_DIR}/lib/gen/constr_TYPE.h
    ${CMAKE_BINARY_DIR}/lib/gen/constraints.c
    ${CMAKE_BINARY_DIR}/lib/gen/constraints.h
    ${CMAKE_BINARY_DIR}/lib/gen/der_encoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/der_encoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/INTEGER.c
    ${CMAKE_BINARY_DIR}/lib/gen/INTEGER.h
    ${CMAKE_BINARY_DIR}/lib/gen/NativeEnumerated.c
    ${CMAKE_BINARY_DIR}/lib/gen/NativeEnumerated.h
    ${CMAKE_BINARY_DIR}/lib/gen/NativeInteger.c
    ${CMAKE_BINARY_DIR}/lib/gen/NativeInteger.h
    ${CMAKE_BINARY_DIR}/lib/gen/NativeReal.c
    ${CMAKE_BINARY_DIR}/lib/gen/NativeReal.h
    ${CMAKE_BINARY_DIR}/lib/gen/OCTET_STRING.c
    ${CMAKE_BINARY_DIR}/lib/gen/OCTET_STRING.h
    ${CMAKE_BINARY_DIR}/lib/gen/per_decoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/per_decoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/per_encoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/per_encoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/per_opentype.c
    ${CMAKE_BINARY_DIR}/lib/gen/per_opentype.h
    ${CMAKE_BINARY_DIR}/lib/gen/per_support.c
    ${CMAKE_BINARY_DIR}/lib/gen/per_support.h
    ${CMAKE_BINARY_DIR}/lib/gen/REAL.c
    ${CMAKE_BINARY_DIR}/lib/gen/REAL.h
    ${CMAKE_BINARY_DIR}/lib/gen/UTF8String.c
    ${CMAKE_BINARY_DIR}/lib/gen/UTF8String.h
    ${CMAKE_BINARY_DIR}/lib/gen/xer_decoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/xer_decoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/xer_encoder.c
    ${CMAKE_BINARY_DIR}/lib/gen/xer_encoder.h
    ${CMAKE_BINARY_DIR}/lib/gen/xer_support.c
    ${CMAKE_BINARY_DIR}/lib/gen/xer_support.h
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
    COMMAND ${ASN1C_EXECUTABLE} -S ${ASN1C_SUPPORT_PATH} -Werror "${CMAKE_SOURCE_DIR}/lib/god-defs.asn"
    COMMAND rm -f ${CMAKE_BINARY_DIR}/lib/gen/Makefile.am.sample ${CMAKE_BINARY_DIR}/lib/gen/converter-sample.c
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib/gen
    DEPENDS "${CMAKE_SOURCE_DIR}/lib/god-defs.asn"
    COMMENT generating ASN definitions
    VERBATIM)

add_custom_target(generate_asn1_sources 
    DEPENDS "${CMAKE_SOURCE_DIR}/lib/god-defs.asn" ${GOD_GENERATED_ASN_FILES})

