#ifndef _HPL_VISUAL_MODE_MANAGER_
#define _HPL_VISUAL_MODE_MANAGER_

#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "editor.h"
#include "lightsource.h"
#include "media.h"
#include "collection_definition.h"
#include "shape_definitions.h"
#include "shapes_sdl.h"
#include "player.h"

/**
	ビジュアルモードでの操作を全般的に管理します
	<en> managing operation in visual mode
*/

namespace hpl{
namespace shapes{
	class HPLVisualModeManager{
		world_point3d playerPosition;
		int playerIndex;
		int playerIdentifier;
	public:
		HPLVisualModeManager();
		~HPLVisualModeManager();
		void init();
		void setPlayerPosition(world_point3d location);
		void setPlayerPosition(int x, int y, int z);
		world_point3d getPlayerPosition();
	};
};
};

#endif
