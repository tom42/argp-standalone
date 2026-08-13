<!--
SPDX-FileCopyrightText: 2026 Thomas Mathys
SPDX-License-Identifier: LGPL-2.1-or-later
argp-standalone - standalone version of glibc's argp functions.
-->

# Checklist for upgrading glibc
* Search the glibc code for ad hoc implementations of `basename`, which need
  to be made portable. Search for the literal `'/'`, and replace it by
  `ARGP_PATH_SEPARATOR` from `argp-compat.h`.
