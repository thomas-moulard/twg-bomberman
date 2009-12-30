#ifndef UTILS_GETTEXT_HH
# define UTILS_GETTEXT_HH
# include "core/application.hh"

// gettext.h contient quelques avertissements.
// Nous ne souhaitons pas avoir a maintenir une
// version sans ces problèmes nous-même, les
// warnings vont donc être désactivé pour ce
// fichier.
# if defined __GNUC__
#  pragma GCC system_header
# elif defined __SUNPRO_CC
#  pragma disable_warn
# elif defined _MSC_VER
#  pragma warning(push, 1)
#endif

# include "utils/gettext.h"

# if defined __SUNPRO_CC
#  pragma enable_warn
# elif defined _MSC_VER
#  pragma warning(pop)
# endif

# define _(String) (::core::mygettext(String))

#endif /* !UTILS_GETTEXT_HH */
