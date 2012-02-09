#!/bin/sh
LDFLAGS="-Wl,-S" LIBS="-lfreetype -lvorbis -logg -ltiff -ljpeg -lpng -lz -lstdc++ -lws2_32 -Ic:/mingw32/lib" ./configure
