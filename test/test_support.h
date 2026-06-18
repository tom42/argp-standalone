/* SPDX-FileCopyrightText: 2020 Thomas Mathys
   SPDX-License-Identifier: LGPL-2.1-or-later
   argp-standalone - standalone version of glibc's argp functions. */

#ifndef ARGP_TEST_SUPPORT_H_INCLUDED
#define ARGP_TEST_SUPPORT_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>

/* Implementation of random() for systems that don't have it.
 * Suitable for test purposes only, not for production code. */
#if defined(HAVE_RANDOM) && !HAVE_RANDOM
static int random(void)
{
  return rand();
}
#endif

/* Implementation of xasprintf() for systems that don't have it.
 * Suitable for test purposes only, not for production code. */
#if defined(HAVE_XASPRINTF) && !HAVE_XASPRINTF
static int xvsnprintf(char* buf, size_t siz, const char* fmt, va_list ap)
{
  const int slen = vsnprintf(buf, siz, fmt, ap);
  if (slen < 0)
  {
    fprintf(stderr, "xvsnprintf: vsnprintf returned a negative value (%d)\n", slen);
    exit(EXIT_FAILURE);
  }

  return slen;
}

static void* xmalloc(size_t siz)
{
  char* p = malloc(siz);
  if (!p)
  {
    fprintf(stderr, "xmalloc: malloc returned NULL\n");
    exit(EXIT_FAILURE);
  }

  return p;
}

static char* xasprintf(const char* fmt, ...)
{
  // TODO: this is tricky. Review/debug

  /* Measure length of resulting string. */
  va_list ap;
  va_start(ap, fmt);
  const int slen = xvsnprintf(NULL, 0, fmt, ap);
  va_end(ap);

  /* Calculate buffer size: add one for the terminating 0.
     The +1 cannot overflow since slen is int. */
  const size_t bufsiz = (size_t)slen + 1;

  /* Allocate memory, abort if insufficient memory. */
  char* buf = xmalloc(bufsiz);

  /* Print to buffer. */
  va_start(ap, fmt);
  xvsnprintf(buf, bufsiz, fmt, ap);
  va_end(ap);

  /* Ensure string is terminated. Not necessary with a conforming snprintf,
     but remember the broken _snprintf that Microsoft has. */
  buf[bufsiz - 1] = '\0';

  return buf;
}
#endif

#endif
