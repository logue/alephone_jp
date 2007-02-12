#ifndef _GENERAL_
#define _GENERAL_

#include <string>

#include "monsters.h"
#include "effects.h"
#include "physics_models.h"
#include "projectiles.h"
#include "items.h"
#include "mysound.h"
#include "weapons.h"
#include "monster_definitions.h"
#include "effect_definitions.h"
#include "projectile_definitions.h"
#include "weapon_definitions.h"
#include <WSCbase.h>

namespace Windows{
	enum{
		None,
		Monster,
		Effect,
		Projectile,
		Physics,
		Weapon,
		
		NUMBER_OF_WINDOWS
	};
};

struct stockName{
	std::string name;
//	int index;
};

const int NUMBER_OF_CLASS_INFORMATIONS = 16;
const int NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS = 4;
const int NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS = 3;
const int NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS = 4;
const int NUMBER_OF_MONSTER_FLAG_INFORMATIONS = 28;
const int NUMBER_OF_SPEED_INFORMATIONS = 11;
const int NUMBER_OF_EFFECT_FLAG_INFORMATIONS = 5;
const int NUMBER_OF_WEAPON_CLASS_INFORMATIONS = 5;
const int NUMBER_OF_WEAPON_FLAG_INFORMATIONS = 11;
const int NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS = 22;
const int NUMBER_OF_ERROR_MESSAGE_INFORMATIONS = 3;

extern int windowType;
extern int selectedMonsterType;
extern int selectedEffectType;
extern int selectedProjectileType;
extern int selectedPhysicsType;
extern int selectedWeaponType;

extern struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];
extern struct effect_definition effect_default_definitions[NUMBER_OF_EFFECT_TYPES];
extern struct projectile_definition projectile_default_definitions[NUMBER_OF_PROJECTILE_TYPES];
extern struct physics_constants physics_default_models[NUMBER_OF_PHYSICS_MODELS];
extern struct weapon_definition weapon_default_definitions[MAXIMUM_NUMBER_OF_WEAPONS];

void setDefinitionsToDefault();
void setupDialog(WSCbase* object);

WSCbase* getObject(const char* class_name, const char* obj_name);

#endif
