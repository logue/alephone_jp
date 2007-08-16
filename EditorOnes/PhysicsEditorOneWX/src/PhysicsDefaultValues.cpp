#include "PhysicsDefaultValues.h"

PhysicsDefaultValues::PhysicsDefaultValues()
{
    memcpy(monster_default_definitions, monster_definitions,
        sizeof(struct monster_definition) * NUMBER_OF_MONSTER_TYPES);
    memcpy(effect_default_definitions, effect_definitions,
        sizeof(struct effect_definition) * NUMBER_OF_EFFECT_TYPES);
    memcpy(projectile_default_definitions, projectile_definitions,
        sizeof(struct projectile_definition) * NUMBER_OF_PROJECTILE_TYPES);
    memcpy(physics_default_models, physics_models,
        sizeof(struct physics_constants) * NUMBER_OF_PHYSICS_MODELS);
    memcpy(weapon_default_definitions, weapon_definitions,
        sizeof(struct weapon_definition) * MAXIMUM_NUMBER_OF_WEAPONS);
}

PhysicsDefaultValues::~PhysicsDefaultValues()
{
}

monster_definition* PhysicsDefaultValues::getMonsterDefinition(int index)
{
	wxASSERT(index >= 0 && index < NUMBER_OF_MONSTER_TYPES);
	return &monster_default_definitions[index];
}
effect_definition* PhysicsDefaultValues::getEffectDefinition(int index)
{
	wxASSERT(index >= 0 && index < NUMBER_OF_EFFECT_TYPES);
	return &effect_default_definitions[index];
}
projectile_definition* PhysicsDefaultValues::getProjectileDefinition(int index)
{
	wxASSERT(index >= 0 && index < NUMBER_OF_PROJECTILE_TYPES);
	return &projectile_default_definitions[index];
}
physics_constants* PhysicsDefaultValues::getPhysicsConstant(int index)
{
	wxASSERT(index >= 0 && index < NUMBER_OF_PHYSICS_MODELS);
	return &physics_default_models[index];
}
weapon_definition* PhysicsDefaultValues::getWeaponDefinition(int index)
{
	wxASSERT(index >= 0 && index < MAXIMUM_NUMBER_OF_WEAPONS);
	return &weapon_default_definitions[index];
}
