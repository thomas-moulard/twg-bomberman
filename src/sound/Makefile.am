include $(top_srcdir)/src/bomberman.mk

AUTODEV_CPPFLAGS_CODEBLOCKS += -I.. -I../.. -I../../lib/tinyxml

noinst_LTLIBRARIES = libsound.la
libsound_la_SOURCES = soundmanager.cc \
		sound.cc

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am