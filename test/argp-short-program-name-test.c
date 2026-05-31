/*
 * SPDX-FileCopyrightText: 2026 Thomas Mathys
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * argp-standalone - standalone version of glibc's argp functions.
 */
#undef NDEBUG
#include <assert.h>
#include <string.h>

char* __argp_basename(char* name);
char* __argp_short_program_name();

int main(int argc, char** argv)
{
  assert(strcmp(__argp_short_program_name(), __argp_basename(argv[0])) == 0);
  return 0;
}
