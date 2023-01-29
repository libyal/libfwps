AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFOLE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBFWPS_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYFWPS = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	$(TESTS_PYFWPS)

check_SCRIPTS = \
	pyfwps_test_set.py \
	pyfwps_test_store.py \
	pyfwps_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fwps_test_error \
	fwps_test_property_identifier \
	fwps_test_record \
	fwps_test_set \
	fwps_test_storage \
	fwps_test_store \
	fwps_test_support

fwps_test_error_SOURCES = \
	fwps_test_error.c \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_unused.h

fwps_test_error_LDADD = \
	../libfwps/libfwps.la

fwps_test_property_identifier_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_property_identifier.c \
	fwps_test_unused.h

fwps_test_property_identifier_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

fwps_test_record_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_record.c \
	fwps_test_unused.h

fwps_test_record_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

fwps_test_set_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_set.c \
	fwps_test_unused.h

fwps_test_set_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

fwps_test_storage_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_storage.c \
	fwps_test_unused.h

fwps_test_storage_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

fwps_test_store_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_store.c \
	fwps_test_unused.h

fwps_test_store_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

fwps_test_support_SOURCES = \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_support.c \
	fwps_test_unused.h

fwps_test_support_LDADD = \
	../libfwps/libfwps.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

