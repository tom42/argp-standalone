/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* Testing of long double conversions in argp.h functions.
   Copyright (C) 2018-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <argp.h>
#include <string.h>

static const struct argp_option
options[] =
{
  { "error", 'e', "format", OPTION_ARG_OPTIONAL,
    "Run argp_error function with a format string", 0 },
  { "failure", 'f', "format", OPTION_ARG_OPTIONAL,
    "Run argp_failure function with a format string", 0 },
  { NULL, 0, NULL, 0, NULL }
};

static error_t
parser (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
      case 'e':
	argp_error (state, "%Lf%f%Lf%f", (long double) -1, (double) -2,
		    (long double) -3, (double) -4);
	break;
      case 'f':
	argp_failure (state, 0, 0, "%Lf%f%Lf%f", (long double) -1,
		      (double) -2, (long double) -3, (double) -4);
	break;
      default:
	return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp
argp =
{
  options, parser
};

int
main(int argc, char** argv)
{
  int remaining;
  argv[0] = "test-argp";
  argp_parse (&argp, argc, argv, 0, &remaining, NULL);
}
