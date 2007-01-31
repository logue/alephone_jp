# -*- Makefile -*- Time-stamp: <05/06/03 21:38:08 ptr>
# $Id: mwccnlm.mak,v 1.1 2007-01-31 09:10:01 hogepiyo Exp $

SRCROOT := ..
COMPILER_NAME := mwccnlm

STLPORT_INCLUDE_DIR = ../../stlport
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I$(STLPORT_INCLUDE_DIR)

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

