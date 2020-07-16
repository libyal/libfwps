if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common

bin_PROGRAMS = \
	storage_fuzzer

storage_fuzzer_SOURCES = \
	ossfuzz_libfwps.h \
	storage_fuzzer.cc

storage_fuzzer_LDADD = \
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

