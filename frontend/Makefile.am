##  Makefile.am -- an automake template for Makefile.in file
##  Copyright (C) 2009 Chris Bagwell and Sane Developers.
##
##  This file is part of the "Sane" build infra-structure.  See
##  included LICENSE file for license information.

EXTRA_PROGRAMS = test tstbackend

bin_PROGRAMS = scanimage

if COMPILE_SANED
sbin_PROGRAMS = saned
else
EXTRA_PROGRAMS += saned
endif

AM_CPPFLAGS = -I. -I$(srcdir) -I$(top_builddir)/include -I$(top_srcdir)/include

scanimage_SOURCES = scanimage.c stiff.c stiff.h
scanimage_LDADD = ../lib/liblib.la ../lib/libfelib.la ../backend/libsane.la

saned_SOURCES = saned.c
saned_LDADD = ../sanei/libsanei.la ../lib/liblib.la ../lib/libfelib.la \
  ../backend/libsane.la @SYSLOG_LIBS@

test_SOURCES = test.c
test_LDADD = ../lib/liblib.la ../lib/libfelib.la ../backend/libsane.la

tstbackend_SOURCES = tstbackend.c
tstbackend_LDADD = ../lib/liblib.la ../lib/libfelib.la ../backend/libsane.la

clean-local:
	rm -f test tstbackend
