# -*- Makefile -*- Time-stamp: <03/10/12 20:35:49 ptr>
# $Id: gcc.mak,v 1.1 2007-01-31 09:11:06 hogepiyo Exp $

SRCROOT := ../..
COMPILER_NAME := gcc

include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I$(STLPORT_INCLUDE_DIR)

ifeq ($(OSNAME),linux)
DEFS += -D_GNU_SOURCE
endif
