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
void hpl::shapes::HPLVisualModeManager::init()
{
	allocate_player_memory();
	initialize_players();
	playerIdentifier = 0;
	short team = 0;
	short color = 0;
	playerIndex = new_player(team, color, playerIdentifier);
	//recreate_players_for_new_level();
	set_current_player_index(playerIndex);

}