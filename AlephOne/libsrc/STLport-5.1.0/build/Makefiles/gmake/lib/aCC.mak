# -*- makefile -*- Time-stamp: <05/03/24 11:33:35 ptr>
# $Id: aCC.mak,v 1.1 2007-01-31 09:10:40 hogepiyo Exp $

dbg-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -b +nostl -Wl,+h$(SO_NAMExx) ${LDSEARCH}
