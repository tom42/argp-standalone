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
static char* xasprintf(const char* fmt, ...)
{
  // TODO: this is tricky. Review/debug

  /* Measure length of resulting string. */
  va_list ap;
  va_start(ap, fmt);
  const int slen = vsnprintf(NULL, 0, fmt, ap);
  va_end(ap);
  if (slen < 0)
  {
    fprintf(stderr, "xasprintf: vsnprintf returned a negative value (%d)\n", slen);
    exit(EXIT_FAILURE);
  }

  /* Calculate buffer size. The + 1 cannot overflow since slen is int. */
  size_t bufsiz = (size_t)slen + 1;

  /* Allocate memory, abort if insufficient memory. */
  char* buf = malloc(bufsiz);
  if (!buf)
  {
    fprintf(stderr, "xasprintf: malloc returned NULL\n");
    exit(EXIT_FAILURE);
  }

  /* Print to buffer. */
  va_start(ap, fmt);
  // TODO: what to pass here, bufsiz or slen?
  vsnprintf(buf, slen, fmt, ap); // TODO: again, this may fail, although it should not. Anyway, handle it for the sake of completeness
  // TODO: is buf terminated in any case or do we have to do this ourselves?
  va_end(ap);

  return buf;

	// TODO: below is test code, redo this
#if 0
		  /* Format text and ensure it is terminated in any case. */
		vsnprintf(strp, bufsize, fmt, ap);
	strp[bufsize - 1] = 0;
	
		
		return strp; // This should contain "Glork a foonly (ZOT defaults to 29)" (35 characters excluding the terminating zero)
#endif
}
#endif

#endif
