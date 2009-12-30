include $(top_srcdir)/src/bomberman.mk
AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS += -I$(top_builddir)

bin_PROGRAMS = smartpointer1
dist_smartpointer1_SOURCES = smartpointer1.cc

smartpointer1_LDADD = $(top_builddir)/src/libbomberman.la

TESTS = smartpointer1

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am