/*
 * SPDX-FileCopyrightText: 2020 Thomas Mathys
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * argp-standalone - standalone version of glibc's argp functions.
 */

/*
 * Ensure we get the POSIX version of strerror_r.
 * We do not try to use the GNU version if available.
 * We'd have to be able to detect whether we have GNU or POSIX,
 * and that is just hairy and not worth the trouble.
 */
#undef _GNU_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <string.h>
#include "argp-compat.h"

#if defined(HAVE_MEMPCPY) && !HAVE_MEMPCPY
void* argp_compat_mempcpy(void* out, const void* in, size_t n)
{
    memcpy(out, in, n);
    return (char*)out + n;
}
#endif

#if defined(HAVE_SLEEP) && !HAVE_SLEEP
#if defined(_WIN32)
void argp_compat_sleep(unsigned int seconds)
{
  for (; seconds; --seconds)
  {
    Sleep(1000);
  }
}
#else
#error No replacement for sleep() is available for the target platform
#endif
#endif

#if defined(HAVE_STRCASECMP) && !HAVE_STRCASECMP
#if defined(_WIN32)
int argp_compat_strcasecmp(const char* s1, const char* s2)
{
  return _stricmp(s1, s2);
}
#else
#error No replacement for strcasecmp() is available for the target platform
#endif
#endif

#if defined(HAVE_STRCHRNUL) && !HAVE_STRCHRNUL
const char* argp_compat_strchrnul(const char* s, int c)
{
  while (*s && (*s != c))
  {
    ++s;
  }
  return s;
}
#endif

#if defined (HAVE_STRNDUP) && !HAVE_STRNDUP
char* argp_compat_strndup(const char* s, size_t n)
{
  char* result;

  /* Find out how many chars to copy: entire string or n characters? */
  size_t s_len = strlen(s);
  if (s_len < n)
    n = s_len;

  /* Get memory, return 0 if insufficient memory. */
  result = malloc(n + 1);
  if (!result)
    return result;

  /* Copy (sub)string and terminate it */
  memcpy(result, s, n);
  result[n] = '\0';
  return result;
}
#endif

// TODO: document: this falls back to strerror and is therefore not necessarily thread-safe
// TODO: replace BSD and strerror path with this, one way or another
// TODO: should we check for the BSD function instead in CMakeLists?
// TODO: remember to also fix all items in argp-compat.h
char* argp_compat_strerror(int errnum, char buf[], size_t size)
{
#ifdef _GNU_SOURCE
#error _GNU_SOURCE must not be defined here
#endif

  /* Prefer strerror_s. It's the most sane API, actually. */
#if defined(HAVE_DECL_STRERROR_S) && HAVE_DECL_STRERROR_S
  strerror_s(buf, size, errnum);
  return buf;
#elif defined(HAVE_DECL_STRERROR_R) && HAVE_DECL_STRERROR_R
  // TODO: strerror_r returns error code here. Handle it: need to clarify, but in case of error I think the buffer is not written to, so we should do so.
  //       Quote from random page: POSIX states that the contents of buf are unspecified on error, although this implementation guarantees a NUL-terminated string for all except n of 0.
  //       So we better maybe
  //       * If the return code is 0 (no error) write "no error", possibly truncated
  //       * Possibly specially handle ERANGE if buffer is too short (then again, now?)
  //       * In call other cases, write "unknown error", possibly truncated
  //       * Doesn't need to be too smart, client code should simply supply a large enough buffer, it's not like the messages are normally very long
  int result = strerror_r(errnum, buf, size);
  (void)result; // TODO: actually do something with result
  return buf;
#else
  return strerror(errnum);
#endif
}
