# SPDX-FileCopyrightText: 2026 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone: standalone version of glibc's argp functions.

function(argp_standalone_target_enable_warnings target)

  if(NOT argp_standalone_ENABLE_WARNINGS)
    return()
  endif()

  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${target} PRIVATE -Werror)
    target_compile_options(${target} PRIVATE -Wall)
  endif()

  if(MSVC)
    target_compile_options(${target} PRIVATE /WX)
    target_compile_options(${target} PRIVATE /W3)
    # x64: suppress mostly harmless warnings about 64 to 32 bit conversion.
    target_compile_options(${target} PRIVATE /wd4244 /wd4267)
  endif()

endfunction()
