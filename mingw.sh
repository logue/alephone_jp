#!/bin/sh
LDFLAGS="-Wl,-S" LIBS="-lIPHlpApi -lsmpeg -lsndfile -lfreetype -lvorbis -logg -ltiff -ljpeg -lpng -lwebp -lz -lstdc++ -lws2_32 -Ic:/mingw32/lib" ./configure
