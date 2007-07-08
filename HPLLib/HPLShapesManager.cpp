#include "HPLShapesManager.h"
#include "HPLError.h"
#include "HPLSurfaceModifier.h"
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

/**
    Shapesファイルを読み込みます
    <en> load Shapes file
    @param path Shapesファイルパス <en> Shapes file's path
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
    指定したShapesデータを取得します。
    @return 失敗時にNULL
*/
SDL_Surface* hpl::shapes::getSurface(int collection, int clut, int index,
													   double illumination)
{
    //TODO
	SDL_Color palette[256];

	//コレクションを別指定。指定する必要がないのでNONE
	int excol = NONE;
	byte **outp = (byte**)malloc(siezof(byte*));
	int col = BUILD_COLLECTION(collection, clut);
	int shape = BUILD_DESCRIPTOR(col, index);
	SDL_Surface* surface = get_shape_surface(shape, excol, outp,
		illumination, false, palette);
#ifdef __WXDEBUG__
	wxASSERT(surface);
#endif
    Uint32 rmask, gmask, bmask, amask;
	//空のサーフェイスデータの作成
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
	SDL_Surface* newSurface = SDL_CreateSurface(surface->flags,
		surface->w, surface->h, surface->format->BitsPerPixel,
		rmask, gmask, bmask, amask);
#ifdef __WXDEBUG__
	wxASSERT(newSurface);
#endif
	SDL_LockSurface(surface);
	SDL_LockSurface(newSurface);
	for(int x = 0; x < surface->w; x ++){
		for(int y = 0; y < surface->h; y ++){
			Uint32 pixel = hpl::surface::getpixel(surface, x, y);
			hpl::surface::setpixel(newSurface, x, y,
				SDL_MapRGB(newSurface->format, palette[pixel].r,
					palette[pixel].g, palette[pixel].b);
		}
	}
	SDL_UnlockSurface(newSurface);
	SDL_UnlockSurface(surface);
    return newSurface;
}
