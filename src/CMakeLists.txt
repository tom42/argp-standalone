# argp-standalone: standalone version of glibc's argp functions.
# Copyright (C) 2020 Thomas Mathys <tom42@github.com>
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

set(
  HEADERS
  "${argp-standalone_SOURCE_DIR}/include/argp-standalone/argp.h"
  argp-compat.h
  argp-fmtstream.h
  argp-getopt.h
  argp-getopt_int.h
  argp-namefrob.h)

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

add_library(argp-standalone ${HEADERS} ${SOURCES})

source_group(TREE "${PROJECT_SOURCE_DIR}" FILES ${HEADERS} ${SOURCES})

target_compile_definitions(argp-standalone PRIVATE HAVE_CONFIG_H)

target_include_directories(
  argp-standalone
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  PUBLIC
  ../include/argp-standalone)
