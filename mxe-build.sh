#!/bin/sh
PREFIX=/home/logue/mxe/usr
TARGET=i686-pc-mingw32
PATH="$PREFIX/bin:$PREFIX/$TARGET/bin:$PATH"

if [ -f "$PREFIX/$TARGET/bin/$TARGET-sdl-config" ]; then
    SDL_CONFIG="$PREFIX/$TARGET/bin/$TARGET-sdl-config"
    export SDL_CONFIG
fi
PKG_CONFIG_LIBDIR=$PREFIX/$TARGET/lib/pkgconfig
export PKG_CONFIG_LIBDIR
export PATH
LIBS="-lvorbis -logg -lFLAC -lvorbisenc -lSDL -lfreetype -ljpeg -lpng -lz -lbz2 -lstdc++ -liconv -ltiff -liphlpapi -lws2_32 -lwsock32" LDFLAGS="-L$PREFIX/i686-pc/mingw32/lib -Wl,-S" ./configure --host=$TARGET --build=i386-linux CPPFLAGS="-I$PREFIX/i686-pc-mingw32/include -I$PREFIX/include"
