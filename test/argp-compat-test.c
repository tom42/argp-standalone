/*
 * SPDX-FileCopyrightText: 2026 Thomas Mathys
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * argp-standalone - standalone version of glibc's argp functions.
 */
#include <errno.h>
#include "argp-compat.h"
#include "argp-namefrob.h"
#include "unity.h"

void setUp() {}
void tearDown() {}

static char** g_argv;

void test__argp_short_program_name(void)
{
  TEST_ASSERT_EQUAL_STRING(__argp_basename(g_argv[0]), __argp_short_program_name());
}

void test_argp_compat_strerror(void)
{
  char buf[200];
  TEST_ASSERT_EQUAL_STRING("Permission denied", argp_compat_strerror(EACCES, buf, sizeof(buf)));
}

int main(int argc, char** argv)
{
  g_argv = argv;
  UNITY_BEGIN();
  RUN_TEST(test__argp_short_program_name);
  RUN_TEST(test_argp_compat_strerror);
  return UNITY_END();
}
