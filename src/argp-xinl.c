// TODO: see whether we can replace this file by an older one that maybe makes more sense
//       * Check the following functions are the same in here and in argp.h
//         * __argp_usage:        OK except the difference in calling argp_state_help vs __argp_state_help
//         * _option_is_short
//         * _option_is_end
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined _LIBC || defined HAVE_FEATURES_H
# include <features.h>
#endif

#include <argp.h>

//#ifdef _LIBC // TODO: this is odd: this is the only place where these functions still have definitions - why do we compile them only if in _LIBC?

void
__argp_usage (const struct argp_state *__state)
{
  argp_state_help (__state, stderr, ARGP_HELP_STD_USAGE);
}
#ifdef weak_alias
weak_alias (__argp_usage, argp_usage)
#endif

int
_option_is_short (const struct argp_option *__opt) // TODO: had to rename this from __option_is_short to _option_is_short because there is no weak alias anymore
{
  if (__opt->flags & OPTION_DOC)
    return 0;
  else
    {
      int __key = __opt->key;
      return __key > 0 && __key <= UCHAR_MAX && isprint (__key);
    }
}
#ifdef weak_alias
weak_alias (__option_is_short, _option_is_short)
#endif

int
_option_is_end (const struct argp_option *__opt) // TODO: had to rename this from __option_is_end to _option_is_end because there is no weak alias anymore
{
  return !__opt->key && !__opt->name && !__opt->doc && !__opt->group;
}
#ifdef weak_alias
weak_alias (__option_is_end, _option_is_end)
#endif

//#endif // TODO: this is odd: this is the only place where these functions still have definitions - why do we compile them only if in _LIBC?
