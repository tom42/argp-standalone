/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

#include <stdlib.h>
#include "argp.h"
#include "argp-compat.h"

static const char doc[] = "Various tests for argp-standalone, to be run with CTest";

#define OPT_ARGP_FAILURE 256

static struct argp_option options[] =
{
  { "argp-failure", OPT_ARGP_FAILURE, NULL, 0, "Smoke test the strerror replacement by calling into argp_failure. This will print an error message which needs to be checked e.g. by CTest."},
  { 0 }
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
  switch (key)
  {
    case OPT_ARGP_FAILURE:
      argp_failure(state, 0, EACCES, "Error message format string");
      return 0;
    default:
      return ARGP_ERR_UNKNOWN;
  }
}

static struct argp argp = { options, parse_opt, 0, doc };

int main(int argc, char** argv)
{
  /* CTest seems to pass Unix style path separators in argv[0] even on Windows.
     This breaks the various ad hoc basename implementations inside argp,
     so let's fix argv[0] here. */
  if (argc > 0)
  {
    for (char* p = argv[0]; *p; ++p)
    {
      if (*p == '/')
      {
        *p = ARGP_PATH_SEPARATOR;
      }
    }
  }

  argp_parse(&argp, argc, argv, 0, 0, 0);
  return EXIT_SUCCESS;
}
