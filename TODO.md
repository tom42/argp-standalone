* Replace check_function_exists by check_symbol_exists
  * Why do we use both for strerror?
  * Should we set CMAKE_REQUIRED_DEFINITIONS during probing?
* MSVC: disable warnings about converting from __int64 to int and the like, but only if we are not the main project
* __argp_short_program_name: there is that warning in there (gcc only)
* Cygwin: should fix warnings about conflicting declarations of getopt stuff, caused by including unistd.h which provide both sleep() and getopt()
* Add LGPL blurb to
  * All CMakeLists.txt
  * config.h.in
  * compatibility header
  * compatibility source file
* Enable warnings as errors for Visual Studio (what about /W4?)
* Enable warnings as errors for gcc and raise warning level
* What about optimizations?
* Do we have pointer size problems on x64?
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
