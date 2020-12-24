cmake_minimum_required(VERSION 3.17.3)
project(argp-standalone VERSION 1.0 LANGUAGES C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
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
check_function_exists(strndup HAVE_STRNDUP)

# Check for types
check_type_size(ssize_t SSIZE_T)

configure_file(config.h.in config.h)


################################################################################
# Global compiler specific options
################################################################################

if(MSVC)
  add_compile_options(/W3)
  add_compile_definitions(
    _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
    _CRT_NONSTDC_NO_DEPRECATE
    _CRT_SECURE_NO_WARNINGS)
else()
  add_compile_options(-Wall -Wno-char-subscripts)
endif()

################################################################################
# Subdirectories
################################################################################

add_subdirectory(src)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR argp-standalone_BUILD_TESTING) AND BUILD_TESTING)
  add_subdirectory(test)
endif()
