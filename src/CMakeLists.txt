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

add_library(argp-standalone ${SOURCES} ${HEADERS})

target_compile_definitions(argp-standalone PRIVATE HAVE_CONFIG_H)

target_include_directories(
  argp-standalone
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  PUBLIC
  ../include/argp-standalone)
