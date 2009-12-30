localedir = $(datadir)/locale

AM_CPPFLAGS =							\
		-I$(top_srcdir)/src				\
		-I$(top_srcdir)/lib/tinyxml 			\
		-I$(top_builddir) 				\
		`sdl-config --cflags` 				\
		-DLOCALEDIR=\"$(localedir)\"
AM_CXXFLAGS = $(WARNING_CXXFLAGS)

AM_LDFLAGS = `sdl-config --libs`	\
		    -lSDL_image		\
		    -lSDL_ttf		\
		    -lSDL_mixer	

LDADD = $(LIBINTL)

AUTODEV_CPPFLAGS_CODEBLOCKS = -DLOCALEDIR=\\".\\"
AUTODEV_LDFLAGS_CODEBLOCKS =

# Nos biblioth�ques, par ordre de d�pendance...
libcore_la = $(top_builddir)/src/core/libcore.la
libutil_la = $(top_builddir)/src/utils/libutil.la
libgame_la = $(top_builddir)/src/game/libgame.la
libgraphic_la = $(top_builddir)/src/graphic/libgraphic.la
libsound_la = $(top_builddir)/src/sound/libsound.la

# Liste des biblioth�ques
libcore = $(libcore_la)
libutil = $(libutil_la)
libgame = $(libgame_la)
libgraphic = $(libgraphic_la)
libsound = $(libsound_la)

# Et des d�pendances...
libcore +=
libutil +=
libgame +=
libgraphic +=
libsound +=





