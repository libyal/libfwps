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
	@LIBFWPS_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyfwps_test_record.py \
	pyfwps_test_set.py \
	pyfwps_test_store.py \
	pyfwps_test_support.py

check_PROGRAMS = \
	fwps_test_error \
	fwps_test_notify \
	fwps_test_property_identifier \
	fwps_test_record \
	fwps_test_set \
	fwps_test_store \
	fwps_test_support

fwps_test_error_SOURCES = \
	fwps_test_error.c \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_unused.h

fwps_test_error_LDADD = \
	../libfwps/libfwps.la

fwps_test_notify_SOURCES = \
	fwps_test_libcerror.h \
	fwps_test_libfwps.h \
	fwps_test_macros.h \
	fwps_test_notify.c \
	fwps_test_unused.h

fwps_test_notify_LDADD = \
	../libfwps/libfwps.la \
	@LIBCERROR_LIBADD@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_library: \
	package.m4 \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_python_module.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

