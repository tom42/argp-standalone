# argp-standalone
argp-standalone is another standalone version of the argp argument parsing functions from glibc by Thomas Mathys.
It is distributed under the terms of the GNU LGPL v2.1.
It is currently available in source form only from https://github.com/tom42/argp-standalone.

# Possible improvements for future versions
* Factor out duplicated ad hoc implementations of what's basically basename (search for occurrences of ARGP_PATH_SEPARATOR). Provide better implementations where possible. The current implementation has various shortcomings:
  * On Windows it only recognizes \ as the path separator, but should probably recognize both \ and /
  * It returns an empty string if the path ends with the path separator. This is normally not the case but I've seen it happening.
* Fix the preprocessor #warning in __argp_short_program_name:
  * On Windows we could fall back to GetModuleFileName
* gettext support
