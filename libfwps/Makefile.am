AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFWPS_DLL_EXPORT@

lib_LTLIBRARIES = libfwps.la

libfwps_la_SOURCES = \
	libfwps.c \
	libfwps_codepage.h \
	libfwps_debug.c libfwps_debug.h \
	libfwps_definitions.h \
	libfwps_extern.h \
	libfwps_error.c libfwps_error.h \
	libfwps_format_class_identifier.c libfwps_format_class_identifier.h \
	libfwps_libcdata.h \
	libfwps_libcerror.h \
	libfwps_libcnotify.h \
	libfwps_libfguid.h \
	libfwps_libuna.h \
	libfwps_notify.c libfwps_notify.h \
	libfwps_property_identifier.c libfwps_property_identifier.h \
	libfwps_record.c libfwps_record.h \
	libfwps_set.c libfwps_set.h \
	libfwps_store.c libfwps_store.h \
	libfwps_support.c libfwps_support.h \
	libfwps_types.h \
	libfwps_unused.h

libfwps_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@PTHREAD_LIBADD@

libfwps_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libfwps_definitions.h.in \
	libfwps.rc \
	libfwps.rc.in

DISTCLEANFILES = \
	libfwps_definitions.h \
	libfwps.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libfwps ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libfwps_la_SOURCES)

