/* SPDX-FileCopyrightText: 2026 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

#include <errno.h>
#include <string.h>
#include "config.h"
#include "argp-compat.h"
#include "argp-namefrob.h"
#include "unity.h"

static char** g_argv;

// TODO: add tests that ensure ARGP_PATH_SEPARATOR is used (failing that, add it to some sort of upgrade checklist)
//       * One place is the hidden --program-name option. We can probably invoke argp-test with CTest and check the output,
//         provided CMake/CTest know about different path separators.
//       * What about the other place in parser_init? If we're lucky, argp-test can be used to test that too

static char* unsafe_make_native_path(const char* unix_path)
{
    static char buf[1000]; /* Static buffer, therefore unsafe. */
    strncpy(buf, unix_path, sizeof(buf));
    buf[sizeof(buf) - 1] = 0; /* strncpy may leave buf unterminated. */

    for (char* p = buf; *p; ++p)
    {
        if (*p == '/')
        {
            *p = ARGP_PATH_SEPARATOR;
        }
    }

    return buf;
}

void test___argp_basename(void)
{
  TEST_ASSERT_EQUAL_STRING("", __argp_basename(unsafe_make_native_path("/")));
  TEST_ASSERT_EQUAL_STRING("", __argp_basename(unsafe_make_native_path("/a/")));
  TEST_ASSERT_EQUAL_STRING("a", __argp_basename(unsafe_make_native_path("/a")));
  TEST_ASSERT_EQUAL_STRING("b", __argp_basename(unsafe_make_native_path("/a/b")));
}

void test___argp_short_program_name(void)
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
  TEST_ASSERT_TRUE_MESSAGE(result, str);
}

void test_argp_compat_strerror_unknown_error(void)
{
  char buf[200];
  const char* str = argp_compat_strerror(-1, buf, sizeof(buf));
  int result = !strcmp(str, "Unknown error") || !strcmp(str, "Unknown error -1");
  TEST_ASSERT_TRUE_MESSAGE(result, str);
}

void test_argp_compat_strerror_buffer_too_short(void)
{
  /* Note: cppreference states regarding strerror_s that
     "If the message had to be truncated to fit the buffer and bufsz is greater than 3,
     then only bufsz-4 bytes are written, and the characters "..." are appended before
     the null terminator."
     At least Microsoft's standard library doesn't appear to do so. */
  char buf[5];
#if defined(HAVE_DECL_STRERROR_S) && HAVE_DECL_STRERROR_S
  TEST_ASSERT_EQUAL_STRING("Perm", argp_compat_strerror(EACCES, buf, sizeof(buf)));
  TEST_ASSERT_EQUAL_STRING("P", argp_compat_strerror(EACCES, buf, 2));
  TEST_ASSERT_EQUAL_STRING("", argp_compat_strerror(EACCES, buf, 1));
  TEST_ASSERT_EQUAL_STRING("", argp_compat_strerror(EACCES, buf, 0));
#else
  /* Message comes from our strerror_r wrapper handling ERANGE. */
  TEST_ASSERT_EQUAL_STRING("ERAN", argp_compat_strerror(EACCES, buf, sizeof(buf)));
  TEST_ASSERT_EQUAL_STRING("E", argp_compat_strerror(EACCES, buf, 2));
  TEST_ASSERT_EQUAL_STRING("", argp_compat_strerror(EACCES, buf, 1));
  TEST_ASSERT_EQUAL_STRING("", argp_compat_strerror(EACCES, buf, 0));
#endif
}

void setUp() {}

void tearDown() {}

int main(int argc, char** argv)
{
  g_argv = argv;
  UNITY_BEGIN();
  RUN_TEST(test___argp_basename);
  RUN_TEST(test___argp_short_program_name);
  RUN_TEST(test_argp_compat_strerror);
  RUN_TEST(test_argp_compat_strerror_no_error);
  RUN_TEST(test_argp_compat_strerror_unknown_error);
  RUN_TEST(test_argp_compat_strerror_buffer_too_short);
  return UNITY_END();
}
