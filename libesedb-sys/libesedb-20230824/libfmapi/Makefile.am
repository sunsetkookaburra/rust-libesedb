if HAVE_LOCAL_LIBFMAPI
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ 

noinst_LTLIBRARIES = libfmapi.la

libfmapi_la_SOURCES = \
	libfmapi_class_identifier.c libfmapi_class_identifier.h \
	libfmapi_checksum.c libfmapi_checksum.h \
	libfmapi_codepage.c libfmapi_codepage.h \
	libfmapi_debug.c libfmapi_debug.h \
	libfmapi_definitions.h \
	libfmapi_entry_identifier.c libfmapi_entry_identifier.h \
	libfmapi_error.c libfmapi_error.h \
	libfmapi_extern.h \
	libfmapi_libcerror.h \
	libfmapi_libcnotify.h \
	libfmapi_libfdatetime.h \
	libfmapi_libfguid.h \
	libfmapi_libfwnt.h \
	libfmapi_libuna.h \
	libfmapi_lzfu.c libfmapi_lzfu.h \
	libfmapi_one_off_entry_identifier.c libfmapi_one_off_entry_identifier.h \
	libfmapi_property_type.c libfmapi_property_type.h \
	libfmapi_service_provider_identifier.c libfmapi_service_provider_identifier.h \
	libfmapi_support.c libfmapi_support.h \
	libfmapi_types.h \
	libfmapi_unused.h \
	libfmapi_value_type.c libfmapi_value_type.h \
	libfmapi_x400_object_identifier.h
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libfmapi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfmapi_la_SOURCES)

