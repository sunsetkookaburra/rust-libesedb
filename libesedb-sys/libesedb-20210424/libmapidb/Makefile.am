if HAVE_LOCAL_LIBMAPIDB
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@

noinst_LTLIBRARIES = libmapidb.la

libmapidb_la_SOURCES = \
	libmapidb_database.c libmapidb_database.h \
	libmapidb_definitions.h \
	libmapidb_error.c libmapidb_error.h \
	libmapidb_extern.h \
	libmapidb_folder.c libmapidb_folder.h \
	libmapidb_libcerror.h \
	libmapidb_libcnotify.h \
	libmapidb_support.c libmapidb_support.h \
	libmapidb_types.h \
	libmapidb_unused.h
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libmapidb ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libmapidb_la_SOURCES)

