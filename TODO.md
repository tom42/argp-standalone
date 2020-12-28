* Figure out what's wrong with building with mingw on cygwin?
  * Well maybe try mingw without cygwin first (e.g. on a Linux box)
* Figure out what's wrong on Linux?
  * mingw: detecting size_t fails
  * native: undefined references to getopt stuff
* Search for usages of strrchr or '/' literals. This are path separators, and we should use the native one!
  * This is duplicated like 3 times
  * Factor out all occurrences into one method, can put that into argp-compat.c
  * Fix it for windows. I suppose the current implementation is sufficient for Unixoids.
* __argp_short_program_name: there is that warning in there (gcc only)
  * This is only executed if there is no sane argv[0], so having this is not THAT critical
* Add LGPL blurb to
  * All CMakeLists.txt
  * config.h.in
  * compatibility header
  * compatibility source file
* Get source groups working properly?
* Process the argp Makefile
  * It shows which files should be compiled with -fexceptions (err...do we want that?)
* Test
  * VS2019, x86/x64
  * Cygwin, x86/x64
  * Mingw, x86/x64
  * gcc on some GNU/Linux, x86/x64
* Final review: patched files vs. original 2.24 files
* Document missing things:
  * gettext support has been removed altogether
