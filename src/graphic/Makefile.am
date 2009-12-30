include $(top_srcdir)/src/bomberman.mk

AUTODEV_CPPFLAGS_CODEBLOCKS += -I.. -I../.. -I../../lib/tinyxml

noinst_LTLIBRARIES = libgraphic.la
libgraphic_la_SOURCES =				\
		gui/guielement.cc		\
		gui/choiceelement.cc		\
		graphicmanager.cc		\
		imageelement.cc			\
		textelement.cc			\
		visualelement.cc

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am