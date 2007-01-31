# Time-stamp: <04/02/04 14:15:31 ptr>
# $Id: vc-common.mak,v 1.1 2007-01-31 09:10:24 hogepiyo Exp $

#INCLUDES = -I$(SRCROOT)/include
#INCLUDES =

!ifndef CXX
CXX = cl
!endif
!ifndef CC
CC = cl
!endif
!ifndef LINK
LINK = link /fixed:no
!endif
!ifndef RC
RC = rc
!endif

!if "$(COMPILER_NAME)" == "vc6"
MSVC_VERSION=1200
!else if "$(COMPILER_NAME)" == "vc70"
MSVC_VERSION=1300
!else if "$(COMPILER_NAME)" == "vc71"
MSVC_VERSION=1310
!else
MSVC_VERSION=1400
!endif

!ifdef STLP_BUILD_FORCE_STATIC_RUNTIME
!if defined (STLP_BUILD_NO_THREAD) && ($(MSVC_VERSION) < 1400)
OPT_DBG = $(OPT_DBG) /MLd
OPT_STLDBG = $(OPT_STLDBG) /MLd
OPT_REL = $(OPT_REL) /ML
!else
OPT_DBG = $(OPT_DBG) /MTd
OPT_STLDBG = $(OPT_STLDBG) /MTd
OPT_REL = $(OPT_REL) /MT
!endif
DEFS_REL = $(DEFS_REL) /D_STLP_USE_DYNAMIC_LIB
DEFS_DBG = $(DEFS_DBG) /D_STLP_USE_DYNAMIC_LIB
DEFS_STLDBG = $(DEFS_STLDBG) /D_STLP_USE_DYNAMIC_LIB
!else
OPT_DBG = $(OPT_DBG) /MDd
OPT_STLDBG = $(OPT_STLDBG) /MDd
OPT_REL = $(OPT_REL) /MD
!endif

!ifdef STLP_BUILD_FORCE_DYNAMIC_RUNTIME
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MDd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MDd
OPT_STATIC_REL = $(OPT_STATIC_REL) /MD
DEFS_STATIC_REL = $(DEFS_STATIC_REL) /D_STLP_USE_STATIC_LIB
DEFS_STATIC_DBG = $(DEFS_STATIC_DBG) /D_STLP_USE_STATIC_LIB
DEFS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) /D_STLP_USE_STATIC_LIB
!else
!if defined (STLP_BUILD_NO_THREAD) && ($(MSVC_VERSION) < 1400)
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MLd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MLd
OPT_STATIC_REL = $(OPT_STATIC_REL) /ML
!else
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /MTd
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /MTd
OPT_STATIC_REL = $(OPT_STATIC_REL) /MT
!endif
!endif

!ifdef STLP_BUILD_NO_THREAD
#Sometimes thread support activation is detected by STLport depending on the
#native runtime version option (/ML /MLd); but as there is no equivalent for
#dll runtime or there is single threaded runtime after VC.Net2003 we simply
#always define _STLP_NO_THREADS
DEFS_REL = $(DEFS_REL) /D_STLP_NO_THREADS
DEFS_DBG = $(DEFS_DBG) /D_STLP_NO_THREADS
DEFS_STLDBG = $(DEFS_STLDBG) /D_STLP_NO_THREADS
DEFS_STATIC_REL = $(DEFS_STATIC_REL) /D_STLP_NO_THREADS
DEFS_STATIC_DBG = $(DEFS_STATIC_DBG) /D_STLP_NO_THREADS
DEFS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) /D_STLP_NO_THREADS
!endif

!ifdef STLP_BUILD_NO_RTTI
!if $(MSVC_VERSION) >= 1400
CXXFLAGS_COMMON = $(CXXFLAGS_COMMON) /GR-
CFLAGS_COMMON = $(CFLAGS_COMMON) /GR-
!endif
!else
!if $(MSVC_VERSION) < 1400
CXXFLAGS_COMMON = $(CXXFLAGS_COMMON) /GR
CFLAGS_COMMON = $(CFLAGS_COMMON) /GR
!endif
!endif

!ifdef STLP_BUILD_BOOST_PATH
CXXFLAGS_COMMON = $(CXXFLAGS_COMMON) /D_STLP_USE_BOOST_SUPPORT
CFLAGS_COMMON = $(CFLAGS_COMMON) /D_STLP_USE_BOOST_SUPPORT
!endif

!ifdef DEFS
DEFS_REL = $(DEFS) $(DEFS_REL)
DEFS_DBG = $(DEFS) $(DEFS_DBG)
DEFS_STLDBG = $(DEFS) $(DEFS_STLDBG)
DEFS_STATIC_REL = $(DEFS) $(DEFS_STATIC_REL)
DEFS_STATIC_DBG = $(DEFS) $(DEFS_STATIC_DBG)
DEFS_STATIC_STLDBG = $(DEFS) $(DEFS_STATIC_STLDBG)
!endif
!ifdef OPT
OPT_REL = $(OPT) $(OPT_REL)
OPT_DBG = $(OPT) $(OPT_DBG)
OPT_STLDBG = $(OPT) $(OPT_STLDBG)
OPT_STATIC_REL = $(OPT) $(OPT_STATIC_REL)
OPT_STATIC_DBG = $(OPT) $(OPT_STATIC_DBG)
OPT_STATIC_STLDBG = $(OPT) $(OPT_STATIC_STLDBG)
!endif

!if "$(COMPILER_NAME)" != "icl"
OUTPUT_OPTION = /Fo$@ /Fd$(PDB_NAME_OUT)
OUTPUT_OPTION_DBG = /Fo$@ /Fd$(PDB_NAME_OUT_DBG)
OUTPUT_OPTION_STLDBG = /Fo$@ /Fd$(PDB_NAME_OUT_STLDBG)
OUTPUT_OPTION_STATIC = /Fo$@ /Fd$(A_PDB_NAME_OUT)
OUTPUT_OPTION_STATIC_DBG = /Fo$@ /Fd$(A_PDB_NAME_OUT_DBG)
OUTPUT_OPTION_STATIC_STLDBG = /Fo$@ /Fd$(A_PDB_NAME_OUT_STLDBG)
!else
OUTPUT_OPTION = /Fo$@
OUTPUT_OPTION_DBG = /Fo$@
OUTPUT_OPTION_STLDBG = /Fo$@
OUTPUT_OPTION_STATIC = /Fo$@
OUTPUT_OPTION_STATIC_DBG = /Fo$@
OUTPUT_OPTION_STATIC_STLDBG = /Fo$@
!endif

LINK_OUTPUT_OPTION = /out:$@
RC_OUTPUT_OPTION = /fo $@
RC_OUTPUT_OPTION_DBG = /fo $@
RC_OUTPUT_OPTION_STLDBG = /fo $@
DEFS_REL = $(DEFS_REL) /DWIN32 /D_WINDOWS
DEFS_STATIC_REL = $(DEFS_STATIC_REL) /DWIN32 /D_WINDOWS
DEFS_DBG = $(DEFS_DBG) /DWIN32 /D_WINDOWS
DEFS_STATIC_DBG = $(DEFS_STATIC_DBG) /DWIN32 /D_WINDOWS
DEFS_STLDBG = $(DEFS_STLDBG) /DWIN32 /D_WINDOWS
DEFS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) /DWIN32 /D_WINDOWS
CPPFLAGS_REL = $(DEFS_REL) $(INCLUDES)
CPPFLAGS_STATIC_REL = $(DEFS_STATIC_REL) $(INCLUDES)
CPPFLAGS_DBG = $(DEFS_DBG) $(INCLUDES)
CPPFLAGS_STATIC_DBG = $(DEFS_STATIC_DBG) $(INCLUDES)
CPPFLAGS_STLDBG = $(DEFS_STLDBG) $(INCLUDES)
CPPFLAGS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) $(INCLUDES)


CFLAGS_REL = $(CFLAGS_COMMON) $(OPT_REL)
CFLAGS_STATIC_REL = $(CFLAGS_COMMON) $(OPT_STATIC_REL)
CFLAGS_DBG = $(CFLAGS_COMMON) $(OPT_DBG)
CFLAGS_STATIC_DBG = $(CFLAGS_COMMON) $(OPT_STATIC_DBG)
CFLAGS_STLDBG = $(CFLAGS_COMMON) $(OPT_STLDBG)
CFLAGS_STATIC_STLDBG = $(CFLAGS_COMMON) $(OPT_STATIC_STLDBG)
CXXFLAGS_REL = $(CXXFLAGS_COMMON) $(OPT_REL)
CXXFLAGS_STATIC_REL = $(CXXFLAGS_COMMON) $(OPT_STATIC_REL)
CXXFLAGS_DBG = $(CXXFLAGS_COMMON) $(OPT_DBG)
CXXFLAGS_STATIC_DBG = $(CXXFLAGS_COMMON) $(OPT_STATIC_DBG)
CXXFLAGS_STLDBG = $(CXXFLAGS_COMMON) $(OPT_STLDBG)
CXXFLAGS_STATIC_STLDBG = $(CXXFLAGS_COMMON) $(OPT_STATIC_STLDBG)
COMPILE_c_REL = $(CC) $(CFLAGS_REL) $(CPPFLAGS_REL) $(TARGET_ARCH) /c
COMPILE_c_STATIC_REL = $(CC) $(CFLAGS_STATIC_REL) $(CPPFLAGS_STATIC_REL) $(TARGET_ARCH) /c
COMPILE_c_DBG = $(CC) $(CFLAGS_DBG) $(CPPFLAGS_DBG) $(TARGET_ARCH) /c
COMPILE_c_STATIC_DBG = $(CC) $(CFLAGS_STATIC_DBG) $(CPPFLAGS_STATIC_DBG) $(TARGET_ARCH) /c
COMPILE_c_STLDBG = $(CC) $(CFLAGS_STLDBG) $(CPPFLAGS_STLDBG) $(TARGET_ARCH) /c
COMPILE_c_STATIC_STLDBG = $(CC) $(CFLAGS_STATIC_STLDBG) $(CPPFLAGS_STATIC_STLDBG) $(TARGET_ARCH) /c
COMPILE_cc_REL = $(CXX) $(CXXFLAGS_REL) $(CPPFLAGS_REL) $(TARGET_ARCH) /c
COMPILE_cc_STATIC_REL = $(CXX) $(CXXFLAGS_STATIC_REL) $(CPPFLAGS_STATIC_REL) $(TARGET_ARCH) /c
COMPILE_cc_DBG = $(CXX) $(CXXFLAGS_DBG) $(CPPFLAGS_DBG) $(TARGET_ARCH) /c
COMPILE_cc_STATIC_DBG = $(CXX) $(CXXFLAGS_STATIC_DBG) $(CPPFLAGS_STATIC_DBG) $(TARGET_ARCH) /c
COMPILE_cc_STLDBG = $(CXX) $(CXXFLAGS_STLDBG) $(CPPFLAGS_STLDBG) $(TARGET_ARCH) /c
COMPILE_cc_STATIC_STLDBG = $(CXX) $(CXXFLAGS_STATIC_STLDBG) $(CPPFLAGS_STATIC_STLDBG) $(TARGET_ARCH) /c
COMPILE_rc_REL = $(RC) $(RC_FLAGS_REL) /D "BUILD_INFOS=$(CXXFLAGS_REL)"
COMPILE_rc_STATIC_REL = $(RC) $(RC_FLAGS_REL) /D "BUILD_INFOS=$(CXXFLAGS_STATIC_REL)"
COMPILE_rc_DBG = $(RC) $(RC_FLAGS_DBG) /DBUILD=d /D "BUILD_INFOS=$(CXXFLAGS_DBG)"
COMPILE_rc_STATIC_DBG = $(RC) $(RC_FLAGS_DBG) /DBUILD=d /D "BUILD_INFOS=$(CXXFLAGS_STATIC_DBG)"
COMPILE_rc_STLDBG = $(RC) $(RC_FLAGS_STLDBG) /DBUILD=stld /D "BUILD_INFOS=$(CXXFLAGS_STLDBG) /D_STLP_DEBUG"
COMPILE_rc_STATIC_STLDBG = $(RC) $(RC_FLAGS_STLDBG) /DBUILD=stld /D "BUILD_INFOS=$(CXXFLAGS_STATIC_STLDBG) /D_STLP_DEBUG"
LINK_cc_REL = $(LINK) /nologo /incremental:no /debug /pdb:$(PDB_NAME_OUT) $(LDFLAGS_REL)
LINK_cc_DBG = $(LINK) /nologo /incremental:no /debug /pdb:$(PDB_NAME_OUT_DBG) $(LDFLAGS_DBG)
LINK_cc_STLDBG = $(LINK) /nologo /incremental:no /debug /pdb:$(PDB_NAME_OUT_STLDBG) $(LDFLAGS_STLDBG)
LINK_cc_A_REL = $(LINK) /nologo /incremental:no /debug /pdb:$(A_PDB_NAME_OUT) $(LDFLAGS_A_REL)
LINK_cc_A_DBG = $(LINK) /nologo /incremental:no /debug /pdb:$(A_PDB_NAME_OUT_DBG) $(LDFLAGS_DBG)
LINK_cc_A_STLDBG = $(LINK) /nologo /incremental:no /debug /pdb:$(A_PDB_NAME_OUT_STLDBG) $(LDFLAGS_STLDBG)

CDEPFLAGS = /FD /E
CCDEPFLAGS = /FD /E

# STLport DEBUG mode specific defines
DEFS_STLDBG = $(DEFS_STLDBG) /D_DEBUG /D_STLP_DEBUG
DEFS_DBG = $(DEFS_DBG) /D_DEBUG
DEFS_REL = $(DEFS_REL) /DNDEBUG
DEFS_STATIC_STLDBG = $(DEFS_STATIC_STLDBG) /D_DEBUG /D_STLP_DEBUG
DEFS_STATIC_DBG = $(DEFS_STATIC_DBG) /D_DEBUG
DEFS_STATIC_REL = $(DEFS_STATIC_REL) /DNDEBUG

# optimization and debug compiler flags
OPT_REL = $(OPT_REL) /Zi /O2
OPT_DBG = $(OPT_DBG) /Zi
OPT_STLDBG = $(OPT_STLDBG) /Zi
OPT_STATIC_REL = $(OPT_STATIC_REL) /Zi /O2
OPT_STATIC_DBG = $(OPT_STATIC_DBG) /Zi
OPT_STATIC_STLDBG = $(OPT_STATIC_STLDBG) /Zi
