include $(top_srcdir)/src/bomberman.mk

AM_CPPFLAGS += $(BINRELOC_CFLAGS)

AUTODEV_CPPFLAGS_CODEBLOCKS += -I.. -I../.. -I../../lib/tinyxml

noinst_LTLIBRARIES = libutil.la
libutil_la_SOURCES =				\
		binreloc.c			\
		binreloc.h			\
		pathmanager.cc			\
		smartpointer.cc			\
		timemanager.cc			\
		resourcemanager.cc		\
		debug.cc

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am