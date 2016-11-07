AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBFWPS_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	fwps_test_error \
	fwps_test_storage \
	fwps_test_support \
	fwps_test_value

fwps_test_error_SOURCES = \
	fwps_test_error.c \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_unused.h

fwps_test_error_LDADD = \
	../libfwps/libfwps.la

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

fwps_test_support_SOURCES = \
	fwps_test_support.c \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_unused.h

fwps_test_support_LDADD = \
	../libfwps/libfwps.la

fwps_test_value_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_memory.c fwps_test_memory.h \
	fwps_test_unused.h \
	fwps_test_value.c

fwps_test_value_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

