#include "EventManager.h"

//ƒ}ƒbƒv‚ÌŽŸŒ³”
const int MAP_DIMENSION = 2;

mapeditorone::EventManager::EventManager()
{
    this->setToolType(ToolType::TI_ARROW);
    this->setEditModeType(EditModeType::EM_DRAW);
    this->setSelectingGroup(false);
}
mapeditorone::EventManager::~EventManager()
{
}

bool mapeditorone::EventManager::isSelectingGroup()
{
    return this->isSelectingGroup_;
}
void mapeditorone::EventManager::setSelectingGroup(bool flag)
{
    this->isSelectingGroup_ = flag;
}
void mapeditorone::EventManager::getSelectGroupStartPoint(int point[2])
{
    for(int i = 0; i < MAP_DIMENSION; i ++){
        point[i] = this->selectGroupStartPoint[i];
    }
}
void mapeditorone::EventManager::setSelectGroupStartPoint(int px, int py)
{
    this->selectGroupStartPoint[0] = px;
    this->selectGroupStartPoint[1] = py;
    this->setSelectingGroup(true);
}

void mapeditorone::EventManager::setToolType(int type)
{
    this->toolType = type;
}
int mapeditorone::EventManager::getToolType()
{
    return this->toolType;
}
void mapeditorone::EventManager::setEditModeType(int type)
{
    this->editModeType = type;
}
int mapeditorone::EventManager::getEditModeType()
{
    return this->editModeType;
}
