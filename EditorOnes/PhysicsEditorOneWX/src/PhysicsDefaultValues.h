#ifndef _PHYSICS_DEFAULT_VALUES_
#define _PHYSICS_DEFAULT_VALUES_

#include "Common.h"

/**
	デフォルト設定を管理するクラス
	インデックス外部へのアクセスなどをブロックするのが目的
*/
class PhysicsDefaultValues{
public:
private:
    struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];
    struct effect_definition effect_default_definitions[NUMBER_OF_EFFECT_TYPES];
    struct projectile_definition projectile_default_definitions[NUMBER_OF_PROJECTILE_TYPES];
    struct physics_constants physics_default_models[NUMBER_OF_PHYSICS_MODELS];
    struct weapon_definition weapon_default_definitions[MAXIMUM_NUMBER_OF_WEAPONS];
public:
	PhysicsDefaultValues();
	~PhysicsDefaultValues();
private:
public:
	monster_definition* getMonsterDefinition(int index);
	effect_definition* getEffectDefinition(int index);
	projectile_definition* getProjectileDefinition(int index);
	physics_constants* getPhysicsConstant(int index);
	weapon_definition* getWeaponDefinition(int index);
};

#endif