#include "HPLEventManager.h"

//ƒ}ƒbƒv‚ÌŽŸŒ³”
const int MAP_DIMENSION = 2;

hpl::aleph::HPLEventManager::HPLEventManager()
{
    this->setToolType(ToolType::TI_ARROW);
    this->setEditModeType(EditModeType::EM_DRAW);
    this->setSelectingGroup(false);
	this->setGrabItems(false);
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
void hpl::aleph::HPLEventManager::exitSelectingGroup()
{
	this->setSelectingGroup(false);
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
void hpl::aleph::HPLEventManager::setLastMouseSelectPoint(int px, int py)
{
	this->lastMouseSelectPoint[0] = px;
	this->lastMouseSelectPoint[1] = py;
}
void hpl::aleph::HPLEventManager::getLastMouseSelectPoint(int point[2])
{
	point[0] = lastMouseSelectPoint[0];
	point[1] = lastMouseSelectPoint[1];
}

void hpl::aleph::HPLEventManager::setGrabItems(bool grab)
{
	this->isGrabItems_ = grab;
}
bool hpl::aleph::HPLEventManager::isGrabItems()
{
	return this->isGrabItems_;
}
