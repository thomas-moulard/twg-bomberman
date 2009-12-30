# N'expense pas les macros commençant par GCN_
m4_pattern_forbid([^GCN_])
AC_PREREQ([2.59])

## ----------------------- ##
## Configuration du paquet ##
## ----------------------- ##
AC_INIT([TWG: Bomberman Classic], [1.0], [thomas.moulard@games-creators.org], [twg-bomberman])

# Auxiliary files.
AC_CONFIG_AUX_DIR([build-aux])

# Automake.
AM_INIT_AUTOMAKE([1.9.6 foreign check-news dist-bzip2 no-dist-gzip -Wall
                                  nostdinc])


## ------------------------------- ##
## Paramétrage du compilateur C++  ##
## ------------------------------- ##

# Recherche d'un compilateur C++
AC_LANG([C++])
AC_PROG_CXX

# Augmente la vitesse de compilation.
if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -pipe"
fi

# Paramétrage des warnings.
GCN_CXX_WARNINGS([[-Wall],
                  [-W],
                  [-Wcast-align],
                  [-Wcast-qual],
                  [-Wformat],
                  [-Wmissing-prototypes],
                  [-Wstrict-prototypes],
                  [-Wwrite-strings],
                  [-Wbad-function-cast],
                  [-Wmissing-declarations],
                  [-Wnested-externs]])

## ---------------------------- ##
## Programmes supplémentaires.  ##
## ---------------------------- ##

# Gettext
# AM_GNU_GETTEXT_VERSION(0.16.1)
AM_GNU_GETTEXT([external])

# Nous n'avons pas besoin de bibliothèques statiques, augmente la vitesse
#   de compilation.
: ${enable_shared=no}
AC_PROG_LIBTOOL

## --------------- ##
## Configuration.  ##
## --------------- ##

# Parametrage de autoinnosetup.
AC_SUBST([AUTOINNOSETUP_APPID],[67b07ada-6676-4ec7-bd71-5280bdcb3b41])
AC_SUBST([AUTOINNOSETUP_DEFAULTGROUPNAME],["Games Creators Network/Two Week Game/Bomberman classic"])
AC_SUBST([AUTOINNOSETUP_LICENSEFILE],[COPYING])
AC_SUBST([AUTOINNOSETUP_COMPANY],["Games Creators Network"])
AC_SUBST([AUTOINNOSETUP_PUBLISHER],["Games Creators Network"])
AC_SUBST([AUTOINNOSETUP_PUBLISHER_URL],[http://www.games-creators.org/])
AC_SUBST([AUTOINNOSETUP_SUPPORT_URL],[https://forge.games-creators.org/projects/twg-bomberman/])
AC_SUBST([AUTOINNOSETUP_UPDATES_URL],[https://forge.games-creators.org/projects/twg-bomberman/])

# Récupération automatique de SDL.dll
AC_SUBST([AUTOGET_TARGETS], [SDL.dll])
AC_SUBST([AUTOGET_URLS],[http://www.libsdl.org/release/SDL-1.2.11-win32.zip])

# Définit la documentation en-ligne à insérer dans la tarball.
AC_SUBST([ONLINEDOC_URL],
[http://www.games-creators.org/wiki/Two_Week_Game])


# Crée le fichier config.h
AC_CONFIG_HEADERS([config.h])

# Autopackage
AC_CONFIG_FILES([autopackage/default.apspec])

# Crée les makefiles
AC_CONFIG_FILES([ po/Makefile.in
  Makefile
    src/Makefile
      src/core/Makefile
      src/game/Makefile
      src/graphic/Makefile
      src/sound/Makefile
      src/utils/Makefile
   doc/Makefile
   tests/Makefile
      tests/utils/Makefile
])

# Ecrit les fichiers.
AC_OUTPUT
