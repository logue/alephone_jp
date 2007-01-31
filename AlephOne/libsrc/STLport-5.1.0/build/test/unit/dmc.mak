# -*- Makefile -*- Time-stamp: <03/10/12 20:35:49 ptr>
# $Id: dmc.mak,v 1.1 2007-01-31 09:11:18 hogepiyo Exp $

SRCROOT := ../..
COMPILER_NAME := dmc
OBJ_EXT := obj

STLPORT_DIR := ../../..

include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I$(STLPORT_INCLUDE_DIR)

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

