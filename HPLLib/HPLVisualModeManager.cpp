#include "HPLVisualModeManager.h"

hpl::shapes::HPLVisualModeManager::HPLVisualModeManager()
{
}
hpl::shapes::HPLVisualModeManager::~HPLVisualModeManager()
{
}
void hpl::shapes::HPLVisualModeManager::setPlayerPosition(world_point3d location)
{
	memcpy(&this->playerPosition, &location, sizeof(world_point3d));
}
void hpl::shapes::HPLVisualModeManager::setPlayerPosition(int x, int y, int z)
{
	this->playerPosition.x = x;
	this->playerPosition.y = y;
	this->playerPosition.z = z;
}
world_point3d hpl::shapes::HPLVisualModeManager::getPlayerPosition()
{
	return this->playerPosition;
}
