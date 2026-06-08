# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone - standalone version of glibc's argp functions.

# TODO: rename once old version is out of the way
add_library(
  argp-standalone243
  argp-ba.c
  argp-eexst.c
  argp-fmtstream.c)

target_compile_definitions(argp-standalone243 PRIVATE HAVE_CONFIG_H)
argp_standalone_target_enable_warnings(argp-standalone243)

target_include_directories(
  argp-standalone243
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}"
  PUBLIC
  ../include/argp-standalone243) # TODO: rename directory once the old one is gone

# TODO: we have now suddenly a subdirectory in include: include/argp-standalone243/argp. Do we want this? Should we hide this a little bit better?
# TODO: port stuff below
# TODO: ensure we have all files:
#       * include/argp.h
#       * include/argp-fmtstream.h
#       * All the getopt stuff
#       * argp src:
#         * argp-fs-xinl.c
#         * argp-help.c
#         * argp-parse.c
#         * argp-pv.c
#         * argp-pvh.c
#         * argp-test.c
#         * argp-xinl.c
#         * argp.h
#         * bits/argp-ldbl.h
#         * bug-argp1.c
#         * bug-argp2.c
#         * Makefile
#         * tst-argp1.c
#         * tst-argp2.c
#         * tst-ldbl-argp.c
#         * Versions
if(0)
set(
  SOURCES
  argp-ba.c
  argp-compat.c
  argp-eexst.c
  argp-fmtstream.c
  argp-fs-xinl.c
  argp-help.c
  argp-parse.c
  argp-pv.c
  argp-pvh.c
  argp-xinl.c
  getopt.c
  getopt1.c)

add_library(argp-standalone ${SOURCES})

target_compile_definitions(argp-standalone PRIVATE HAVE_CONFIG_H)
argp_standalone_target_enable_warnings(argp-standalone)

target_include_directories(
  argp-standalone
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  PUBLIC
  ../include/argp-standalone)


################################################################################
# OS specific options
################################################################################

if(WIN32)
  target_compile_definitions(argp-standalone PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
  # We currently use the strchrnul() provided by macOS, but that requires 15.4.
  set(CMAKE_OSX_DEPLOYMENT_TARGET 15.4)
endif()


################################################################################
# Compiler specific options
################################################################################

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  # gcc and clang need -fgnu89-inline to compile and link release builds
  target_compile_options(argp-standalone PRIVATE -fgnu89-inline)
endif()
endif()
