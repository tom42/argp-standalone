# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone - standalone version of glibc's argp functions.

add_library(
  argp-standalone
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

target_compile_definitions(argp-standalone PRIVATE HAVE_CONFIG_H)
argp_standalone_target_enable_warnings(argp-standalone)

target_include_directories(
  argp-standalone
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}"
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

# TODO: when done possibly run a diff what we changed and then mark source locations with some sort of marker comment?
#       * In any case, clean up things!
#./src/argp-compat.h
#./src/argp-getopt_ext.h
#./src/argp-fs-xinl.c
#./src/argp-fmtstream.c
#./src/argp-getopt_int.h
#./src/argp-pvh.c
#./src/argp-getopt_core.h
#./src/argp-pv.c
#./src/argp-getopt.h
#./src/argp-compat.c
#./src/getopt1.c
#./src/argp-fmtstream.h
#./src/argp-parse.c
#./src/argp-namefrob.h
#./src/argp-xinl.c
#./src/argp-eexst.c
#./src/argp-ba.c
#./src/getopt.c
#./src/argp-help.c
#./test/argp-compat-test.c
#./test/argp-test.c
#./test/unity_internals.h
#./test/tst-ldbl-argp.c
#./test/unity.c
#./test/argp-failure-test.c
#./test/tst-argp1.c
#./test/tst-argp2.c
#./test/unity.h
#./test/test_support.h
#./include/argp-standalone/argp.h
