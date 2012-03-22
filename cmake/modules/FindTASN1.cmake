# - Try to find TASN1
# --- COPIED FROM TASN1 ---
# -------------------------
# Once done this will define
#
#  TASN1_FOUND - system has TASN1
#  TASN1_INCLUDE_DIR - the TASN1 include directory
#  TASN1_LIBRARIES - Link these to use TASN1

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

FIND_PATH(TASN1_INCLUDE_DIR libtasn1.h )

FIND_LIBRARY(TASN1_LIBRARIES NAMES tasn1 )

# handle the QUIETLY and REQUIRED arguments and set TASN1_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TASN1 DEFAULT_MSG TASN1_LIBRARIES TASN1_INCLUDE_DIR)

MARK_AS_ADVANCED(TASN1_INCLUDE_DIR TASN1_LIBRARIES)

