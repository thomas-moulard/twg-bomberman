include $(top_srcdir)/src/bomberman.mk
AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS =				\
	core				\
	game				\
	graphic				\
	sound				\
	utils

bin_PROGRAMS = bomberman

dist_bomberman_SOURCES = main.cc
nodist_bomberman_SOURCES =  data.stamp

bomberman_LDADD = libbomberman.la

AUTODEV_CPPFLAGS_CODEBLOCKS +=  -I.. \
				-I../lib/tinyxml
AUTODEV_LDFLAGS_CODEBLOCKS += core/libcore.a \
			      game/libgame.a \
			      graphic/libgraphic.a \
			      utils/libutil.a \
			      sound/libsound.a \
			      libbomberman.a \
			      libintl.a \
			      -lSDL \
			      -lSDLmain \
		              -lSDL_ttf \
			      -lSDL_image \
			      -lSDL_mixer

# -- data --
data.stamp:
	! test -f data && $(LN_S) $(top_srcdir)/src/data data || true
	touch data.stamp

CLEANFILES = data.stamp

# -- version.cc --
EXTRA_DIST = version.cc.in
CLEANFILES += version.stamp
version.stamp: $(top_srcdir)/ChangeLog $(srcdir)/version.cc.in
	@rm -f version.tmp
	@touch version.tmp
# Vérifiez bien qu'il n'y a pas de `/' dans Id. La date peut être séparée
# par des `/' au lieu des `-', que sed n'apprécie pas.
	@Id=`sed -n '/^\$$Id/{s,/,-,g;p;q;}' $(top_srcdir)/ChangeLog`; \
	sed -e "s/@ID@/$$Id/" $(srcdir)/version.cc.in >version.cc.tmp
	$(top_srcdir)/build-aux/move-if-change version.cc.tmp version.cc
	@mv -f version.tmp version.stamp

version.cc: version.stamp
	@if test -f version.cc; then :; else \
	  rm -f version.stamp; \
	  $(MAKE) $(AM_MAKEFLAGS) version.stamp; \
	fi


# -- libbomberman.la --
lib_LTLIBRARIES = libbomberman.la
libbomberman_la_SOURCES = 		\
	version.cc 			\
	../lib/tinyxml/tinystr.cpp 	\
	../lib/tinyxml/tinyxml.cpp 	\
	../lib/tinyxml/tinyxmlerror.cpp \
	../lib/tinyxml/tinyxmlparser.cpp


nodist_libbomberman_la_SOURCES = version.cc
BUILT_SOURCES = $(nodist_libbomberman_la_SOURCES)
CLEANFILES    += $(nodist_libbomberman_la_SOURCES)

libbomberman_la_LIBADD =		\
	$(libcore_la)			\
	$(libgame_la)			\
	$(libgraphic_la)		\
	$(libsound_la)			\
	$(libutil_la)

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am




