/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

// C++ compilation and linking test.
// The code doesn't do anything actually useful.

#include <argp.h>
#include <argp-fmtstream.h>
#include <argp-getopt.h>
#include <cstdio>

int main(int argc, char** argv)
{
  argp_failure(nullptr, 0, 0, "failure message");
  argp_fmtstream_free(argp_make_fmtstream(stdout, 0, 0, 0));
  getopt(0, argv, "");
  getopt_long(0, argv, "", nullptr, nullptr);
}
