# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone - standalone version of glibc's argp functions.

cmake_minimum_required(VERSION 3.17.3)
project(argp-standalone VERSION 1.0.3 LANGUAGES C)
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_LIST_DIR}/cmake")


################################################################################
# Options
################################################################################

option(argp_standalone_BUILD_TESTING "Build argp-standalone tests" OFF)
option(argp_standalone_ENABLE_WARNINGS "Build argp-standalone with warnings enabled" OFF)


################################################################################
# Set up testing
################################################################################

if(argp_standalone_BUILD_TESTING)
  enable_testing()
endif()


################################################################################
# config.h
################################################################################

include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckVariableExists)
include(CMakePushCheckState)

cmake_push_check_state()
set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)

# Check for headers
check_include_file(mempcpy.h HAVE_MEMPCPY_H)
check_include_file(strcase.h HAVE_STRCASE_H)
check_include_file(strchrnul.h HAVE_STRCHRNUL_H)
check_include_file(strndup.h HAVE_STRNDUP_H)
check_include_file(sysexits.h HAVE_SYSEXITS_H)
check_include_file(unistd.h HAVE_UNISTD_H)

# Check for unlocked variants of stdio functions
check_symbol_exists(putc_unlocked stdio.h HAVE_DECL_PUTC_UNLOCKED)
check_symbol_exists(fputs_unlocked stdio.h HAVE_DECL_FPUTS_UNLOCKED)
check_symbol_exists(fwrite_unlocked stdio.h HAVE_DECL_FWRITE_UNLOCKED)

# Check for strerror_r etc.
# We only check for functions and their declarations here.
# The decision which one to use is made in the argp sources.
# We define all of HAVE_STRERROR_R, HAVE_DECL_STRERROR_R and
# HAVE_DECL_STRERROR here because the argp sources expect
# it to be done that way. Normally we'd just use a single
# call to check_symbol_exists to probe for a function.
cmake_push_check_state(RESET)
set(CMAKE_REQUIRED_DEFINITIONS -D_POSIX_C_SOURCE=200112L)
check_function_exists(strerror_r HAVE_STRERROR_R)
check_symbol_exists(strerror_r string.h HAVE_DECL_STRERROR_R)
check_symbol_exists(strerror string.h HAVE_DECL_STRERROR)
check_symbol_exists(strerror_s string.h HAVE_DECL_STRERROR_S)
cmake_pop_check_state()

# Check for miscellaneous functions
check_symbol_exists(asprintf stdio.h HAVE_ASPRINTF)
check_symbol_exists(mempcpy string.h HAVE_MEMPCPY)
check_symbol_exists(random stdlib.h HAVE_RANDOM)
check_symbol_exists(sleep unistd.h HAVE_SLEEP)

# strcasecmp should be in strings.h, but the argp source appears to expect it
# in string.h, so we probe for that (strings.h isn't included anywhere).
check_symbol_exists(strcasecmp string.h HAVE_STRCASECMP)

check_symbol_exists(strchrnul string.h HAVE_STRCHRNUL)
check_symbol_exists(strndup string.h HAVE_STRNDUP)

# Check for variables
check_symbol_exists(program_invocation_short_name errno.h HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME)
check_symbol_exists(program_invocation_name errno.h HAVE_DECL_PROGRAM_INVOCATION_NAME)
check_symbol_exists(__argv stdlib.h HAVE_DECL___ARGV)
check_variable_exists(__progname HAVE___PROGNAME)

# Check for types
check_type_size(ssize_t SSIZE_T)

cmake_pop_check_state()

configure_file(config.h.in config.h)


################################################################################
# Build our own code
################################################################################

include(ArgpStandaloneEnableWarnings)

add_subdirectory(src) # TODO: remove this
add_subdirectory(src243) # TODO: rename this into src
if(argp_standalone_BUILD_TESTING)
  add_subdirectory(test) # TODO: remove this
  add_subdirectory(test243) # TODO: rename this into test
endif()
