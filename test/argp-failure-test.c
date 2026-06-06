/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

/* Smoke test our strerror replacement by calling into argp_failure.
   Print an error message which then needs to be checked e.g. by ctest. */

#include <stdlib.h>
#include "argp.h"

int main(int argc, char** argv)
{
  struct argp_state* state = NULL; /* argp_failure can work without state. */
  int status = 0; /* Keep argp_failure from calling exit. */

  argp_failure(state, status, EACCES , "Error message format string");
  return EXIT_SUCCESS;
}
