# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWPS_DLL_IMPORT@

am_pyfwps_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pyfwps.c pyfwps.h \
	pyfwps_codepage.c pyfwps_codepage.h \
	pyfwps_error.c pyfwps_error.h \
	pyfwps_guid.c pyfwps_guid.h \
	pyfwps_integer.c pyfwps_integer.h \
	pyfwps_libcerror.h \
	pyfwps_libclocale.h \
	pyfwps_libfguid.h \
	pyfwps_libfwps.h \
	pyfwps_python.h \
	pyfwps_record.c pyfwps_record.h \
	pyfwps_records.c pyfwps_records.h \
	pyfwps_set.c pyfwps_set.h \
	pyfwps_sets.c pyfwps_sets.h \
	pyfwps_storage.c pyfwps_storage.h \
	pyfwps_store.c pyfwps_store.h \
	pyfwps_unused.h

pyexec_LTLIBRARIES = pyfwps.la

nodist_pyfwps_la_SOURCES = $(BUILT_SOURCES)

pyfwps_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libfwps/libfwps.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBFGUID_LIBADD@

pyfwps_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pyfwps_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyfwps/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyfwps*.[ch]

distclean: clean
	/bin/rm -f Makefile

