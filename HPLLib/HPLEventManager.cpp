#include "HPLEventManager.h"

//ƒ}ƒbƒv‚ÌŽŸŒ³”
const int MAP_DIMENSION = 2;

hpl::aleph::HPLEventManager::HPLEventManager()
{
    this->setToolType(ToolType::TI_ARROW);
    this->setEditModeType(EditModeType::EM_DRAW);
    this->setSelectingGroup(false);
}
hpl::aleph::HPLEventManager::~HPLEventManager()
{
}

void hpl::aleph::HPLEventManager::getSelectGroupStartPoint(int point[2])
{
    for(int i = 0; i < MAP_DIMENSION; i ++){
        point[i] = this->selGroupStartPoint[i];
    }
}
void hpl::aleph::HPLEventManager::setSelectGroupStartPoint(int px, int py)
{
    this->selGroupStartPoint[0] = px;
    this->selGroupStartPoint[1] = py;
    this->setSelectingGroup(true);
}
bool hpl::aleph::HPLEventManager::isSelectingGroup()
{
    return this->isSelGrp;
}
void hpl::aleph::HPLEventManager::setSelectingGroup(bool flag)
{
    this->isSelGrp = flag;
}
void hpl::aleph::HPLEventManager::setToolType(int type)
{
    this->toolType = type;
}
int hpl::aleph::HPLEventManager::getToolType()
{
    return this->toolType;
}
void hpl::aleph::HPLEventManager::setEditModeType(int type)
{
    this->editModeType = type;
}
int hpl::aleph::HPLEventManager::getEditModeType()
{
    return this->editModeType;
}
