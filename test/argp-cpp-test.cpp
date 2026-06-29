/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

#include <argp.h>
#include <argp-fmtstream.h>
#include <argp-getopt.h>
#include <cstdio>

int main()
{
  // TODO: do something slightly more useful? (test all headers? actually no, other headers are not public)
  argp_failure(nullptr, 0, 0, "failure");
  argp_fmtstream_free(argp_make_fmtstream(stdout, 0, 0, 0));
  getopt(0, nullptr, nullptr); // TODO: real args, verify return code?
  getopt_long(0, nullptr, nullptr, nullptr, nullptr); // TODO: real args, verify return code?
}
