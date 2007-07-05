#include "HPLShapesManager.h"

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
    Shapes�t�@�C����ǂݍ��݂܂�
    <en> load Shapes file
    @param path Shapes�t�@�C���p�X <en> Shapes file's path
*/
void hpl::shapes::HPLShapesManager::loadShapesFile(const char* path)
{
	initialize_shape_handler();

	FileSpecifier ShapesFile(path);
	if(!ShapesFile.Exists()){
		MessageBox(L"no shapes file");
	}else{
		isLoadedShapesFile_ = true;
		open_shapes_file(ShapesFile);
		for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
			mark_collection_for_loading(i);
		}
		load_collections(false, false);
	}
}
