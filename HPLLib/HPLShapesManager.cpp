#include "HPLShapesManager.h"
#include "HPLError.h"
#include "HPLSurfaceModifier.h"

const int SCREEN_BPP = 32;
const int NEW_SURFACE_BPP = SCREEN_BPP;

hpl::shapes::HPLShapesManager::HPLShapesManager()
{
    this->isLoadedShapesFile_ = false;
	isInitialized = false;
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
    Uint32 rmask, gmask, bmask, amask = 0;
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

void hpl::shapes::HPLShapesManager::initScreen()
{
    screenSurface = createSurface(SDL_SWSURFACE,
		640, 480, SCREEN_BPP);
	bit_depth = SCREEN_BPP;

	struct screen_mode_data scr;
	scr.acceleration = 0;
	scr.bit_depth = screenSurface->format->BitsPerPixel;
	scr.draw_every_other_line = 0;
	scr.fullscreen = 0;
	scr.gamma_level = 0;
	scr.high_resolution = 1;
	scr.size = 2;
	initialize_screen(&scr, false);

	isInitialized = true;
}

/**
    Shapes�t�@�C����ǂݍ��݂܂�
    <en> load Shapes file
    @param path Shapes�t�@�C���p�X <en> Shapes file's path
*/
bool hpl::shapes::HPLShapesManager::loadShapesFile(const char* path)
{
	if(!isInitialized){
		hpl::error::caution("Shapes Manager is not initialized yet");
		return false;
	}
    initialize_shape_handler();

	FileSpecifier ShapesFile(path);
	if(!ShapesFile.Exists()){
        hpl::error::caution("cannot load shapes file[%s]", path);
		return false;
	}else{
		open_shapes_file(ShapesFile);

		for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
			mark_collection_for_loading(i);
		}
		load_collections(false, false);
		this->setLoadedShapesFile(true);
	}
	return true;
}

/**
    �ǂݍ��񂾃f�[�^�����̂܂܎擾���܂��B
    �p���b�g�̐F�ԍ����������Ȃ����߁A�p���b�g���K�v
    @param palette �J���[�p���b�g�B�O���ŗp�ӂ���
    @param outp ���f�[�^�B�O���ŗp�ӂ���
*/
SDL_Surface* hpl::shapes::HPLShapesManager::getRawSurface(
    int collection, int clut, int index, double illumination,
    SDL_Color palette[256], byte **outp)
{
	//�R���N�V������ʎw��B�w�肷��K�v���Ȃ��̂�NONE
	int excol = NONE;
	int col = BUILD_COLLECTION(collection, clut);
	int shape = BUILD_DESCRIPTOR(col, index);
	if(screenSurface->format->BitsPerPixel == 8 && illumination >= 0){
		illumination = -1.0;
	}
	SDL_Surface* surface = get_shape_surface(shape, excol, outp,
		illumination, false, palette);
    return surface;
}
/**
    �w�肵��Shapes�f�[�^���擾���܂��B
    @return ���s����NULL
*/
SDL_Surface* hpl::shapes::HPLShapesManager::getSurface(int collection, int clut, int index,
													   double illumination)
{
	if(!isInitialized){
		hpl::error::halt("Shapes Manager is not initialized yet");
	}
	if(!this->isLoadedShapesFile()){
		hpl::error::halt("Shapes Manager doesn't load Shapes file yet");
	}
    //TODO
	SDL_Color palette[256];
	byte **outp = (byte**)malloc(sizeof(byte*));
    SDL_Surface* surface = this->getRawSurface(collection, clut, index, illumination,
        palette, outp);
#ifdef __WXDEBUG__
	wxASSERT(surface);
#endif
	SDL_Surface* newSurface = createSurface(screenSurface->flags,
		surface->w, surface->h, NEW_SURFACE_BPP);
#ifdef __WXDEBUG__
	wxASSERT(newSurface);
#endif
	SDL_LockSurface(surface);
	SDL_LockSurface(newSurface);
	struct collection_header* header = get_collection_header(collection);
	int numColors = 0;
    struct rgb_color_value* palette1 = get_collection_colors(collection, clut, numColors);
//	int colorPaletteOffset = header->collection->color_table_offset;
	for(int y = 0; y < surface->h; y ++){
	    for(int x = 0; x < surface->w; x ++){
			Uint32 pixel = hpl::surface::getpixel(surface, x, y);
			hpl::surface::setpixel(newSurface, x, y,
				SDL_MapRGB(screenSurface->format, 
/*				surface->format->palette->colors[pixel].r,
				surface->format->palette->colors[pixel].g,
				surface->format->palette->colors[pixel].b));
				*/
				palette1[pixel].red,
				palette1[pixel].green,
				palette1[pixel].blue));
		}
	}
	SDL_UnlockSurface(newSurface);
	SDL_UnlockSurface(surface);
    free(outp);

    return newSurface;
}
/**
	walls/landscapes are inversed between X and Y
	get surface inversed
*/
SDL_Surface* hpl::shapes::HPLShapesManager::getYXSurface(int collection, int clut, int index, double illumination)
{
	SDL_Surface* surface = getSurface(collection, clut, index, illumination);

	SDL_Surface* newSurface = createSurface(screenSurface->flags,
		surface->h, surface->w, NEW_SURFACE_BPP);
	SDL_LockSurface(surface);
	SDL_LockSurface(newSurface);
//	int colorPaletteOffset = header->collection->color_table_offset;
	for(int y = 0; y < surface->h; y ++){
	    for(int x = 0; x < surface->w; x ++){
			Uint32 pixel = hpl::surface::getpixel(surface, x, y);
			hpl::surface::setpixel(newSurface, y, x, pixel);
		}
	}
	SDL_UnlockSurface(newSurface);
	SDL_UnlockSurface(surface);

	SDL_FreeSurface(surface);
    return newSurface;
}
