# argp-standalone
argp-standalone is another standalone version of the argp argument parsing functions from glibc by Thomas Mathys.
It is distributed under the terms of the GNU LGPL v2.1.
It is currently available in source form only from https://github.com/tom42/argp-standalone.

# Compatibility
I haven't done any extensive testing, but I have successfully built version 1.0 with the following compilers:
* Visual Studio 2019, both for x86 and x64
* i686-pc-windows-msvc clang 10.0.0 (The one supplied with Visual Studio 2019)
* Cygwin gcc 10.2.0 for x64, with newlib
* Cygwin clang 8.0.1 for x64, with newlib
* Cygwin i686-w64-mingw32-gcc 10.2.0
* gcc 10.2.1 for x64, on GNU/Linux, with glibc
* i686-w64-mingw32-gcc, on GNU/Linux
* x86_64-w64-mingw32-gcc, on GNU/Linux

# Possible improvements for future versions
* Factor out duplicated ad hoc implementations of what's basically basename (search for occurrences of ARGP_PATH_SEPARATOR). Provide better implementations where possible. The current implementation has various shortcomings:
  * On Windows it only recognizes \ as the path separator, but should probably recognize both \ and /
  * It returns an empty string if the path ends with the path separator. This is normally not the case but I've seen it happening.
* Fix the preprocessor #warning in __argp_short_program_name:
  * On Windows we could fall back to GetModuleFileName
* gettext support
