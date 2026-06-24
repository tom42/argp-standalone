/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

#include <argp.h>

int main()
{
  // TODO: do something slightly more useful? (test all headers? actually no, other headers are not public)
  argp_failure(nullptr, 0, 0, "failure");
}