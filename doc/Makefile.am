DOXYGEN = doxygen

.PHONY: doc html onlinedoc

doc: html onlinedoc

# Si le projet est lié à de la documentation en-ligne.
# Définissez ONLINEDOC_URL dans le configure.ac. Cette
# variable contient l'url du/des documents).
#
# Exemples:
# "http://www.example.com/a.html"
# "http://www.example.com/a.html http://www.example.com/b.html"
onlinedoc:
	@if test -n "$(ONLINEDOC_URL)"; then \
	 mkdir onlinedoc; \
	 cd onlinedoc; \
	 for d in "$(ONLINEDOC_URL)"; do \
	  wget "$$d"; \
	 done; \
	fi;

html-local: Doxyfile
	$(DOXYGEN)

edit = sed -e "s|@ID@|$$Id|" \
	   -e 's,@PACKAGE_NAME\@,$(PACKAGE_NAME),g' \
	   -e 's,@PACKAGE_VERSION\@,$(PACKAGE_VERSION),g' \
	   -e 's,@top_builddir\@,$(top_builddir),g' \
	   -e 's,@top_srcdir\@,$(top_srcdir),g'

EXTRA_DIST = Doxyfile.in
CLEANFILES = Doxyfile

# Nous utilisons sed pour générer le fichier Doxyfile.
Doxyfile: $(top_srcdir)/ChangeLog $(srcdir)/Doxyfile.in
	Id=`grep '^\$$Id' $(top_srcdir)/ChangeLog`; \
	$(edit) $(srcdir)/Doxyfile.in >Doxyfile

clean-local:
	rm -rf html latex onlinedoc

include $(top_srcdir)/build-aux/autoinnosetup.am