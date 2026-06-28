# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone - standalone version of glibc's argp functions.

add_executable(argp-test argp-test.c)
target_compile_definitions(argp-test PRIVATE HAVE_CONFIG_H)
if(WIN32)
  target_compile_definitions(argp-test PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
  target_compile_definitions(argp-test PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
argp_standalone_target_enable_warnings(argp-test)
target_include_directories(argp-test PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(argp-test PRIVATE argp-standalone)
add_test(NAME argp-test COMMAND argp-test)

add_executable(argp-compat-test argp-compat-test.c unity.c)
argp_standalone_target_enable_warnings(argp-compat-test)
target_include_directories(argp-compat-test PRIVATE "${PROJECT_BINARY_DIR}" ../src)
target_link_libraries(argp-compat-test PRIVATE argp-standalone)
add_test(NAME argp-compat-test COMMAND argp-compat-test)

add_executable(argp-failure-test argp-failure-test.c)
argp_standalone_target_enable_warnings(argp-failure-test)
target_link_libraries(argp-failure-test PRIVATE argp-standalone)
add_test(NAME argp-failure-test COMMAND argp-failure-test)
set_tests_properties(argp-failure-test PROPERTIES PASS_REGULAR_EXPRESSION "Error message format string: Permission denied")

add_executable(argp-cpp-test argp-cpp-test.cpp)
argp_standalone_target_enable_warnings(argp-cpp-test)
target_include_directories(argp-cpp-test PRIVATE ../src)
target_link_libraries(argp-cpp-test PRIVATE argp-standalone)
# TODO: add test(?) Or is it sufficient if we link?

add_executable(tst-argp1 tst-argp1.c)
argp_standalone_target_enable_warnings(tst-argp1)
target_link_libraries(tst-argp1 PRIVATE argp-standalone)
add_test(NAME tst-argp1 COMMAND tst-argp1)

add_executable(tst-argp2 tst-argp2.c)
argp_standalone_target_enable_warnings(tst-argp2)
target_link_libraries(tst-argp2 PRIVATE argp-standalone)
add_test(NAME tst-argp2 COMMAND tst-argp2)

add_executable(tst-ldbl-argp tst-ldbl-argp.c)
argp_standalone_target_enable_warnings(tst-ldbl-argp)
target_link_libraries(tst-ldbl-argp PRIVATE argp-standalone)
add_test(NAME tst-ldbl-argp-error COMMAND tst-ldbl-argp --error)
set_tests_properties(tst-ldbl-argp-error PROPERTIES PASS_REGULAR_EXPRESSION "test-argp: -1.000000-2.000000-3.000000-4.000000\nTry `test-argp --help' or `test-argp --usage' for more information.\n")
add_test(NAME tst-ldbl-argp-failure COMMAND tst-ldbl-argp --failure)
set_tests_properties(tst-ldbl-argp-failure PROPERTIES PASS_REGULAR_EXPRESSION "test-argp: -1.000000-2.000000-3.000000-4.000000\n")
