# Locate SDL2_mixer library
#
# This module defines:
# SDL2_MIXER_LIBRARY, the name of the library to link against
# SDL2_MIXER_FOUND, if false, do not try to link to SDL2_mixer
# SDL2_MIXER_INCLUDE_DIR, where to find the headers
# SDL2_MIXER_VERSION_STRING - human-readable string containing the version of SDL_mixer
#
# $SDL2_DIR is an environment or cmake variable that would correspond to the
# ./configure --prefix=$SDL2_DIR used in building SDL2.
#
# $SDL2_MIXER_DIR is an environment or cmake variable that would
# correspond to the ./configure --prefix=$SDL2_MIXER_DIR
# used in building SDL2_mixer.
#
# Created by Eric Wing.  This was influenced by the FindSDL2.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

# Modified by Egor Makarenko, 2016

#=============================================================================
# Copyright 2005-2009 Kitware, Inc.
# Copyright 2012 Benjamin Eikel
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

message("<FindSDL2_mixer.cmake>")

set(SDL2_MIXER_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    $ENV{SDL2_DIR} # Windows
    $ENV{SDL2_MIXER_DIR}
    ${SDL2_DIR}
    ${SDL2_MIXER_DIR}
)

find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
    HINTS
    $ENV{SDL2_DIR}
    $ENV{SDL2_MIXER_DIR}
    PATH_SUFFIXES include/SDL2 include
    PATHS ${SDL2_MIXER_SEARCH_PATHS}
)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VC_LIB_PATH_SUFFIX lib/x64)
else ()
    set(VC_LIB_PATH_SUFFIX lib/x86)
endif ()

find_library(SDL2_MIXER_LIBRARY
    NAMES SDL2_mixer
    HINTS
    $ENV{SDL2_DIR}
    $ENV{SDL2_MIXER_DIR}
    PATH_SUFFIXES lib64 lib ${VC_LIB_PATH_SUFFIX}
    PATHS ${SDL2_MIXER_SEARCH_PATHS}
)

if (SDL2_MIXER_INCLUDE_DIR AND EXISTS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h")
    file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL2_MIXER_MAJOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL2_MIXER_MINOR_VERSION[ \t]+[0-9]+$")
    file(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL2_MIXER_PATCHLEVEL[ \t]+[0-9]+$")
    string(REGEX REPLACE "^#define[ \t]+SDL2_MIXER_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MAJOR "${SDL2_MIXER_VERSION_MAJOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL2_MIXER_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MINOR "${SDL2_MIXER_VERSION_MINOR_LINE}")
    string(REGEX REPLACE "^#define[ \t]+SDL2_MIXER_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_PATCH "${SDL2_MIXER_VERSION_PATCH_LINE}")
    set(SDL2_MIXER_VERSION_STRING ${SDL2_MIXER_VERSION_MAJOR}.${SDL2_MIXER_VERSION_MINOR}.${SDL2_MIXER_VERSION_PATCH})
    unset(SDL2_MIXER_VERSION_MAJOR_LINE)
    unset(SDL2_MIXER_VERSION_MINOR_LINE)
    unset(SDL2_MIXER_VERSION_PATCH_LINE)
    unset(SDL2_MIXER_VERSION_MAJOR)
    unset(SDL2_MIXER_VERSION_MINOR)
    unset(SDL2_MIXER_VERSION_PATCH)
endif ()

set(SDL2_MIXER_LIBRARY ${SDL2_MIXER_LIBRARY})
set(SDL2_MIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_mixer
    REQUIRED_VARS SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR
    VERSION_VAR SDL2_MIXER_VERSION_STRING)

mark_as_advanced(SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR)
