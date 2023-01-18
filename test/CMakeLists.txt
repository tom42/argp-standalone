# SPDX-FileCopyrightText: 2020 Thomas Mathys
# SPDX-License-Identifier: LGPL-2.1-or-later
# argp-standalone: standalone version of glibc's argp functions.

add_executable(argp-test argp-test.c)
target_compile_definitions(argp-test PRIVATE HAVE_CONFIG_H)
target_include_directories(argp-test PRIVATE "${PROJECT_BINARY_DIR}")
target_link_libraries(argp-test PRIVATE argp-standalone)

add_executable(tst-argp1 tst-argp1.c)
target_link_libraries(tst-argp1 PRIVATE argp-standalone)

add_executable(tst-argp2 tst-argp2.c)
target_link_libraries(tst-argp2 PRIVATE argp-standalone)

add_executable(bug-argp1 bug-argp1.c)
target_link_libraries(bug-argp1 PRIVATE argp-standalone)

add_executable(bug-argp2 bug-argp2.c)
target_link_libraries(bug-argp2 PRIVATE argp-standalone)

add_test(NAME argp-test COMMAND argp-test)
add_test(NAME tst-argp1 COMMAND tst-argp1)
add_test(NAME tst-argp2 COMMAND tst-argp2)
add_test(NAME bug-argp1 COMMAND bug-argp1 --help)
add_test(NAME bug-argp2 COMMAND bug-argp2 -d 111 --dstaddr 222 -p 333 --peer 444)
