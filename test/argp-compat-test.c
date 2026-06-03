/*
 * SPDX-FileCopyrightText: 2026 Thomas Mathys
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * argp-standalone - standalone version of glibc's argp functions.
 */
#undef NDEBUG
#include <assert.h>
#include <string.h>
#include "argp-compat.h"
#include "argp-namefrob.h"

static void test__argp_short_program_name(char** argv)
{
  assert(strcmp(__argp_short_program_name(), __argp_basename(argv[0])) == 0);
}

static void test_argp_compat_strerror()
{
  // TODO: pass correct args: is the buf/sizeof(buf) thing correct?
  // TODO: awesome: it already gets unwieldy: can we source a tiny unit test framework for C with better assertion messages?
  char buf[200];
  assert(strcmp(argp_compat_strerror(EACCES, buf, sizeof(buf)), "") == 0);
}

int main(int argc, char** argv)
{
  test__argp_short_program_name(argv);
  test_argp_compat_strerror();
  return 0;
}
