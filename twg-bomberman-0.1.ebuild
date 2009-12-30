# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit subversion games

ESVN_REPO_URI="https://forge.games-creators.org/svn/twg-bomberman/trunk/"

DESCRIPTION="TWG Bomberman is a bomberman clone (svn)"
HOMEPAGE="https://forge.games-creators.org/projects/twg-bomberman/"
SRC_URI=""

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="-*"
IUSE=""

DEPEND="media-libs/libsdl
        media-libs/sdl-image
        media-libs/sdl-mixer
        media-libs/sdl-ttf"

RDEPEND="${DEPEND}"

pkg_setup() {
	games_pkg_setup
	if ! built_with_use media-libs/sdl-image png ; then
		die "Please emerge sdl-image with USE=png"
	fi
}

src_unpack() {
        subversion_src_unpack
}

src_compile() {
	[[ -x ./bootstrap ]] && { ./bootstrap || die "bootstrap failed"; }
        games_src_compile
}

src_install() {
        emake DESTDIR="${D}" install || die "make install failed"
	prepgamesdirs
}

pkg_preinst() {
        games_pkg_preinst
}

pkg_postinst() {
        games_pkg_postinst
}
