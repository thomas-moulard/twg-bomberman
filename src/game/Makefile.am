include $(top_srcdir)/src/bomberman.mk

AUTODEV_CPPFLAGS_CODEBLOCKS += -I.. -I../.. -I../../lib/tinyxml

noinst_LTLIBRARIES = libgame.la
libgame_la_SOURCES =				\
		ia/behavior.cc			\
		ia/randombehavior.cc		\
		backgroundlayer.cc		\
		battlescene.cc			\
		battleoptionsscene.cc		\
		block.cc			\
		bomb.cc				\
		bombpowerup.cc			\
		classicbomb.cc			\
		devilpowerup.cc			\
		downlayer.cc			\
		endofbattlescene.cc		\
		firepowerup.cc			\
		followbomb.cc			\
		gameelement.cc			\
		humanplayer.cc			\
		iaplayer.cc			\
		introscene.cc			\
		layer.cc			\
		map.cc				\
		menuscene.cc			\
		minebomb.cc			\
		minepowerup.cc			\
		player.cc			\
		powerup.cc			\
		scene.cc			\
		shootpowerup.cc			\
		speedpowerup.cc			\
		throwpowerup.cc			\
		updownlayer.cc			\
		uplayer.cc

include $(top_srcdir)/build-aux/autoget.am
include $(top_srcdir)/build-aux/autodev.am
include $(top_srcdir)/build-aux/autoinnosetup.am