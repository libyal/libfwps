if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common

bin_PROGRAMS = \
	set_fuzzer \
	storage_fuzzer \
	store_fuzzer

set_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	set_fuzzer.cc

set_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la

storage_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	storage_fuzzer.cc

storage_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la

store_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	store_fuzzer.cc

store_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la
endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on storage_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(storage_fuzzer_SOURCES)
	@echo "Running splint on store_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(store_fuzzer_SOURCES)

