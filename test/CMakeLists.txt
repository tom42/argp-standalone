# argp-standalone: standalone version of glibc's argp functions.
# Copyright (C) 2020 Thomas Mathys
#
# argp-standalone is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# argp-standalone is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

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
