* Process the argp Makefile
  * It shows which files should be compiled with -fexceptions (err...do we want that?)
    CFLAGS-argp-help.c = $(uses-callbacks) -fexceptions
    CFLAGS-argp-parse.c = $(uses-callbacks)
    CFLAGS-argp-fmtstream.c = -fexceptions
  * What does -fexceptions exactly? How do we achieve the same for MSVC?
  * What's uses-callbacks
* Test
  * VS2019, x86/x64
  * Cygwin, x86/x64
  * Mingw, x86/x64
  * gcc on some GNU/Linux, x86/x64
* Final review: patched files vs. original 2.24 files
* Document missing things:
  * gettext support has been removed altogether
  * Build instructions for selected systems:
    * Using Visual Studio
    * Using MinGW on Linux
* Make a tag at the very least
* Make the repository public