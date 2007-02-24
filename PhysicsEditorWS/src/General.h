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
#include "extensions.h"
#include <WSCbase.h>
#include <WSCoption.h>
#include <WSCbaseList.h>
#include <WSCwindow.h>
#include <WSCindexForm.h>
#include <WSCvifield.h>
#include <WSCmessageDialog.h>
#include <WSClist.h>
#include <WSCvradio.h>
#include <WSCcheckGroup.h>
#include <WSCvtoggle.h>
#include <WSCdialog.h>
#include <WSCfileSelect.h>

#include <HPLLib/HPLAlephLib.h>

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

extern int selectIndex;

extern struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];
extern struct effect_definition effect_default_definitions[NUMBER_OF_EFFECT_TYPES];
extern struct projectile_definition projectile_default_definitions[NUMBER_OF_PROJECTILE_TYPES];
extern struct physics_constants physics_default_models[NUMBER_OF_PHYSICS_MODELS];
extern struct weapon_definition weapon_default_definitions[MAXIMUM_NUMBER_OF_WEAPONS];

//stock names
extern std::vector<std::string> stockCollections;
extern std::vector<std::string> stockMonsterClasses;
extern std::vector<std::string> stockMonsterTypes;
extern std::vector<std::string> stockSpeeds;
extern std::vector<std::string> stockItemTypes;
extern std::vector<std::string> stockEffects;
extern std::vector<std::string> stockProjectiles;
extern std::vector<std::string> stockSounds;
extern std::vector<std::string> stockDamages;
extern std::vector<std::string> stockMonsterActivates;
extern std::vector<std::string> stockMonsterDoorRetryMasks;
extern std::vector<std::string> stockWeaponClasses;
extern std::vector<std::string> stockShellCasingTypes;
extern std::vector<std::string> stockPhysicsTypes;
extern std::vector<std::string> stockMonsterFlags;
extern std::vector<std::string> stockProjectileFlags;
extern std::vector<std::string> stockWeaponFlags;

//index-value
extern int valueSpeed[NUMBER_OF_SPEED_INFORMATIONS];
extern int valueMonsterClasses[NUMBER_OF_CLASS_INFORMATIONS];
extern int valueIntelligences[NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS];
extern int valueMonsterDoorRetryMask[NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS];
extern int valueMonsterFlags[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];
extern int valueEffectFlags[NUMBER_OF_EFFECT_FLAG_INFORMATIONS];
extern int valueWeaponFlags[NUMBER_OF_WEAPON_FLAG_INFORMATIONS];
extern int valueProjectileFlags[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS];

void setDefinitionsToDefault();
void setupDialog();
long getInteger(WSCbase* obj);

//int getSelectedValue(WSCoption *opt);

WSCbase* getObject(const char* class_name, const char* obj_name);
WSCbase* getChild(WSCbase* parent, const char* obj_name);
void messageBox(const char* format, ...);
void changeForm(int wtype);
void setValueByName(WSCbase* object);
long selectFromDialog(int* value, WSCbase* object,
	std::vector<std::string>& stock,
	bool isMaxNONE);
void importPhysicsFile(const char *filename);

#endif
