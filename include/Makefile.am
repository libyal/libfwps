include_HEADERS = \
	libfwps.h

pkginclude_HEADERS = \
	libfwps/codepage.h \
	libfwps/definitions.h \
	libfwps/error.h \
	libfwps/extern.h \
	libfwps/features.h \
	libfwps/types.h

EXTRA_DIST = \
	libfwps.h.in \
	libfwps/definitions.h.in \
	libfwps/features.h.in \
	libfwps/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libfwps.h
	/bin/rm -f libfwps/definitions.h
	/bin/rm -f libfwps/features.h
	/bin/rm -f libfwps/types.h
	/bin/rm -f Makefile

