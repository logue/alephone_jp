#include "HPLSurfaceModifier.h"


/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

Uint32 hpl::surface::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    return getpixel((Uint8*)surface->pixels, (int)surface->pitch, bpp, x, y);
}

Uint32 hpl::surface::getpixel(Uint8* pixels, int pitch, int bpp, int x, int y)
{
    /* この p は取得したいピクセルを指すアドレス */
    Uint8 *p = (Uint8 *)pixels + y * pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* 起こるはずがないが、ワーニングを回避 */
    }
}

void hpl::surface::setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* この p は取得したいピクセルを指すアドレス */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

