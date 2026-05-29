# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone - standalone version of glibc's argp functions.

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
