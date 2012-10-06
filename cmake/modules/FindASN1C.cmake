# - Try to find ASN1C
# - Copied from one of cmake templates
# -------------------------
# Once done this will define
#
#  ASN1C_FOUND - system has ASN1C
#  ASN1C_EXECUTABLE - the ASN1C executable

#=============================================================================
# Copyright 2006-2009 Kitware, Inc.
# Copyright 2006 Alexander Neundorf <neundorf@kde.org>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PROGRAM(ASN1C_EXECUTABLE NAMES asn1c 
	HINTS ENV${ASN1C_ROOT}/asn1c ${ASN1C_ROOT}/asn1c)

# handle the QUIETLY and REQUIRED arguments and set ASN1C_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ASN1C DEFAULT_MSG ASN1C_EXECUTABLE)

MARK_AS_ADVANCED(ASN1C_EXECUTABLE)

