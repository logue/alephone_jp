#ifndef _HPL_SURFACEE_MODIFIER_
#define _HPL_SURFACEE_MODIFIER_

#include "SDL.h"

namespace hpl{
namespace surface{
    Uint32 getpixel(SDL_Surface *surface, int x, int y);

    Uint32 getpixel(Uint8* pixels, int pitch, int bpp, int x, int y);

    /** 
        �T�[�t�F�C�X�Ɏw�肵���s�N�Z����ł��܂�
    */
    void setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
};
};
#endif
