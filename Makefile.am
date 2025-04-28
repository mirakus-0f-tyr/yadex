SUBDIRS = atclib src docsrc ygd
EXTRA_DIST = autogen.sh GPL LGPL Makefile.am README.md README.orig \
	TODO.orig boost configure.ac

# yadex.cfg
dist_sysconf_DATA = yadex.cfg

# rule to make "local install" - convenient
# since the needed files are in multiple dirs
localinst:
	-@mkdir app
	@cp -av src/yadex app
	@cp -av $(top_srcdir)/yadex.cfg app
	@cp -av $(top_srcdir)/ygd/* app

clean-local:
	@rm -rf app

distclean-local:
	@rm -v config.cc
	@rm -v config.o
	@rm -v config.etc
	@rm -v config.share
	@rm -v Makefile

