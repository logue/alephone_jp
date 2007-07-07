#include "HPLShapesManager.h"
#include "HPLError.h"

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
/**
    Shapesファイルを読み込みます
    <en> load Shapes file
    @param path Shapesファイルパス <en> Shapes file's path
*/
void hpl::shapes::HPLShapesManager::loadShapesFile(const char* path)
{
	initialize_shape_handler();

	FileSpecifier ShapesFile(path);
	if(!ShapesFile.Exists()){
        hpl::error::caution("no shapes file");
	}else{
		isLoadedShapesFile_ = true;
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
SDL_Surface* hpl::shapes::HPLShapesManager::getSurface(int collection, int clut, int index)
{
    //TODO
    return NULL;
}
