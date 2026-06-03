/*
 * SPDX-FileCopyrightText: 2026 Thomas Mathys
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * argp-standalone - standalone version of glibc's argp functions.
 */
#include <errno.h>
#include <string.h>
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
  TEST_ASSERT_EQUAL_STRING("No such file or directory", argp_compat_strerror(ENOENT, buf, sizeof(buf)));
}

void test_argp_compat_strerror_no_error(void)
{
  char buf[200];
  const char* str = argp_compat_strerror(0, buf, sizeof(buf));

  int result = !strcmp(str, "No error") || !strcmp(str, "Success");

  if (!result)
  {
    char message[400];
    snprintf(message, sizeof(message), "Unexpected error message: %s", str);
    TEST_FAIL_MESSAGE(message);
  }
}

void test_argp_compat_strerror_buffer_too_short(void)
{
  // Note: cppreference states regarding strerror_s that
  // "If the message had to be truncated to fit the buffer and bufsz is greater than 3,
  // then only bufsz-4 bytes are written, and the characters "..." are appended before
  // the null terminator."
  // At least Microsoft's standard library doesn't appear to do so.
  char buf[5];
  TEST_ASSERT_EQUAL_STRING("Perm", argp_compat_strerror(EACCES, buf, sizeof(buf)));
  TEST_ASSERT_EQUAL_STRING("P", argp_compat_strerror(EACCES, buf, 2));
  TEST_ASSERT_EQUAL_STRING("", argp_compat_strerror(EACCES, buf, 1));
}

int main(int argc, char** argv)
{
  g_argv = argv;
  UNITY_BEGIN();
  RUN_TEST(test__argp_short_program_name);
  RUN_TEST(test_argp_compat_strerror);
  RUN_TEST(test_argp_compat_strerror_no_error);
  RUN_TEST(test_argp_compat_strerror_buffer_too_short);
  return UNITY_END();
}
