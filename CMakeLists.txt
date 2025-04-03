# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone: standalone version of glibc's argp functions.

cmake_minimum_required(VERSION 3.17.3)
project(argp-standalone VERSION 1.0.3 LANGUAGES C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_MAIN_PROJECT TRUE)
else()
  set(IS_MAIN_PROJECT FALSE)
endif()

if(IS_MAIN_PROJECT)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(CTest)
endif()


################################################################################
# config.h
################################################################################

include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckTypeSize)
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

# Check for strerror_r and strerror
# We only check for functions and their declarations here.
# The decision which one to use is made in the argp sources.
# We define all of HAVE_STRERROR_R, HAVE_DECL_STRERROR_R and
# HAVE_DECL_STRERROR here because the argp sources expect
# it to be done that way. Normally we'd just use a single
# call to check_symbol_exists to probe for a function.
check_function_exists(strerror_r HAVE_STRERROR_R)
check_symbol_exists(strerror_r string.h HAVE_DECL_STRERROR_R)
check_symbol_exists(strerror string.h HAVE_DECL_STRERROR)

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

# Check for types
check_type_size(ssize_t SSIZE_T)

cmake_pop_check_state()

configure_file(config.h.in config.h)


################################################################################
# Global OS specific options
################################################################################

if(WIN32)
  add_compile_definitions(
    _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
    _CRT_NONSTDC_NO_DEPRECATE
    _CRT_SECURE_NO_WARNINGS)
endif()


################################################################################
# Global compiler specific options
################################################################################

if(MSVC)
  add_compile_options(/W3)
  if(NOT IS_MAIN_PROJECT)
    # x64: suppress mostly harmless warnings about 64 to 32 bit conversion.
    add_compile_options(/wd4244 /wd4267)
  endif()
else()
  add_compile_options(-Wall -Wno-char-subscripts)
  add_compile_options(-fgnu89-inline)
endif()


################################################################################
# Subdirectories
################################################################################

add_subdirectory(src)

if((IS_MAIN_PROJECT OR argp-standalone_BUILD_TESTING) AND BUILD_TESTING)
  add_subdirectory(test)
endif()
