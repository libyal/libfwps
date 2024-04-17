if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common

bin_PROGRAMS = \
	record_fuzzer \
	set_fuzzer \
	store_fuzzer

record_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	record_fuzzer.cc

record_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la

set_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	set_fuzzer.cc

set_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la

store_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	store_fuzzer.cc

store_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	../libfwps/libfwps.la
endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on record_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(record_fuzzer_SOURCES)
	@echo "Running splint on set_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(set_fuzzer_SOURCES)
	@echo "Running splint on store_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(store_fuzzer_SOURCES)

