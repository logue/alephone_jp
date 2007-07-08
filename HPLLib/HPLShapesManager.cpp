#include "HPLShapesManager.h"
#include "HPLError.h"
#include "HPLSurfaceModifier.h"
#include "shapes_sdl.h"

hpl::shapes::HPLShapesManager::HPLShapesManager()
{
    this->isLoadedShapesFile_ = false;
}
hpl::shapes::HPLShapesManager::~HPLShapesManager()
{
}
bool hpl::shapes::HPLShapesManager::isLoadedShapesFile()
{
    return this->isLoadedShapesFile_;
}
void hpl::shapes::HPLShapesManager::setLoadedShapesFile(bool loaded)
{
	this->isLoadedShapesFile_ = loaded;
}

static SDL_Surface* createSurface(int flags, int w, int h, int bpp)
{
    Uint32 rmask, gmask, bmask, amask;
	//��̃T�[�t�F�C�X�f�[�^�̍쐬
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    SDL_Surface* surface = SDL_CreateRGBSurface(flags,
		w, h, bpp,
		rmask, gmask, bmask, amask);
    return surface;
}

void hpl::shapes::initScreen()
{
    screenSurface = createSurface(SDL_SWSURFACE,
		640, 480, 8);

	struct screen_mode_data scr;
	scr.acceleration = 0;
	scr.bit_depth = screenSurface->format->BitsPerPixel;
	scr.draw_every_other_line = 0;
	scr.fullscreen = 0;
	scr.gamma_level = 0;
	scr.high_resolution = 1;
	scr.size = 2;
	initialize_screen(&scr, false);
}

/**
    Shapes�t�@�C����ǂݍ��݂܂�
    <en> load Shapes file
    @param path Shapes�t�@�C���p�X <en> Shapes file's path
*/
void hpl::shapes::loadShapesFile(const char* path)
{

    initialize_shape_handler();

	FileSpecifier ShapesFile(path);
	if(!ShapesFile.Exists()){
        hpl::error::caution("no shapes file");
	}else{
		open_shapes_file(ShapesFile);

		for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
			mark_collection_for_loading(i);
		}
		load_collections(false, false);
	}
}
/**
    �w�肵��Shapes�f�[�^���擾���܂��B
    @return ���s����NULL
*/
SDL_Surface* hpl::shapes::getSurface(int collection, int clut, int index,
													   double illumination)
{
    //TODO
	SDL_Color palette[256];

	//�R���N�V������ʎw��B�w�肷��K�v���Ȃ��̂�NONE
	int excol = NONE;
	byte **outp = (byte**)malloc(sizeof(byte*));
	int col = BUILD_COLLECTION(collection, clut);
	int shape = BUILD_DESCRIPTOR(col, index);
	SDL_Surface* surface = get_shape_surface(shape, excol, outp,
		illumination, false, palette);
#ifdef __WXDEBUG__
	wxASSERT(surface);
#endif
	SDL_Surface* newSurface = createSurface(surface->flags,
		surface->w, surface->h, 8);
#ifdef __WXDEBUG__
	wxASSERT(newSurface);
#endif
	SDL_LockSurface(surface);
	SDL_LockSurface(newSurface);
	for(int y = 0; y < surface->h; y ++){
	    for(int x = 0; x < surface->w; x ++){
			Uint32 pixel = hpl::surface::getpixel(surface, x, y);
			hpl::surface::setpixel(newSurface, x, y,
				SDL_MapRGB(newSurface->format, palette[pixel].r,
					palette[pixel].g, palette[pixel].b));
		}
	}
	SDL_UnlockSurface(newSurface);
	SDL_UnlockSurface(surface);
    free(outp);

    return newSurface;
}
