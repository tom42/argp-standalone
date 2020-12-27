* Review all the conditional compilation with _MSC_VER and WIN32. I think most of it is wrong
  We can see this is so when we try building with clang
  #if defined(_MSC_VER) && defined(WIN32)	32	C:\work\experiments\argp-standalone\src\argp-compat.c	34	C:\work\experiments\argp-standalone\src
  #if defined(_MSC_VER) && defined(WIN32)	46	C:\work\experiments\argp-standalone\src\argp-compat.c	34	C:\work\experiments\argp-standalone\src
* Likewise, fix wrong conditional flags in main CMakeLists: some things are compiler specific, some are platform specific
* Search for usages of strrchr or '/' literals. This are path separators, and we should use the native one!
* MSVC: disable warnings about converting from __int64 to int and the like, but only if we are not the main project
* __argp_short_program_name: there is that warning in there (gcc only)
  * This is only executed if there is no sane argv[0], so having this is not THAT critical
* Add LGPL blurb to
  * All CMakeLists.txt
  * config.h.in
  * compatibility header
  * compatibility source file
* Get source groups working properly?
* Set up the test CMakeLists.txt (this is still empty)
  * Add all test binaries
* Process the argp Makefile
  * It provides command line arguments for some of the tests
  * It shows which files should be compiled with -fexceptions (err...do we want that?)
* Test
  * VS2019, x86/x64
  * Cygwin, x86/x64
  * Mingw, x86/x64
  * gcc on some GNU/Linux, x86/x64
* Final review: patched files vs. original 2.24 files
* Document missing things:
  * gettext support has been removed altogether
