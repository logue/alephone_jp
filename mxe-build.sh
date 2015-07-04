#!/bin/sh
PREFIX=/home/logue/mxe/usr
BUILD=i686-linux
TARGET=i686-w64-mingw32.static
PATH="$PREFIX/bin:$PREFIX/$TARGET/bin:$PATH"

if [ -f "$PREFIX/$TARGET/bin/$TARGET-sdl-config" ]; then
    SDL_CONFIG="$PREFIX/$TARGET/bin/$TARGET-sdl-config"
    export SDL_CONFIG
fi
PKG_CONFIG_LIBDIR=$PREFIX/$TARGET/lib/pkgconfig
export PKG_CONFIG_LIBDIR
export PATH
LIBS="-lvorbis -logg -lFLAC -lvorbisenc -lSDL -lharfbuzz -lfreetype -lSDL_ttf -ljpeg -lpng -lSDL_image -lsmpeg -lsndfile -lz -lbz2 -lstdc++ -liconv -ltiff -liphlpapi -lws2_32 -lwsock32 -mwindows" LDFLAGS="-L$PREFIX/$TARGET/lib -Wl,-S" ./configure --host=$TARGET --build=$BUILD CPPFLAGS="-I$PREFIX/$TARGET/include -I$PREFIX/include"
