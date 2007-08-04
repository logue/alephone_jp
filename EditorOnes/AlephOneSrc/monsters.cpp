/*
MONSTERS.C

	Copyright (C) 1991-2001 and beyond by Bungie Studios, Inc.
	and the "Aleph One" developers.
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	This license is contained in the file "COPYING",
	which is included with this source code; it is available online at
	http://www.gnu.org/licenses/gpl.html

Tuesday, November 10, 1992 1:10:20 PM

Friday, May 27, 1994 11:21:07 AM
	split into MONSTERS.C, PROJECTILES.C and EFFECTS.C; unified active_monster and monster array.
Friday, September 30, 1994 5:48:25 PM (Jason)
	started adding comments again.  damage_monsters_in_radius() is less forgiving in z now.
Monday, December 5, 1994 9:07:37 PM  (Jason)
	rebellion environment function (all _clients hate all _pfhor).
Wednesday, February 1, 1995 2:29:01 AM  (Jason')
	kill_sounds; invisible monsters don’t move
Wednesday, June 14, 1995 10:14:24 AM  (Jason)
	rewrite for marathon2 (halfway done).
Monday, July 10, 1995 11:49:06 AM  (Jason)
	rewrite for marathon2 done.  my bobs won’t listen to your fucking whining.

Jan 30, 2000 (Loren Petrich):
	Added some typecasts
	Removed some "static" declarations that conflict with "extern"

Feb 3, 2000 (Loren Petrich):
	Treating Jjaro goo like sewage

Feb. 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 6, 2000 (Loren Petrich):
	Added access to size of monster-definition structure

Feb 12, 2000 (Loren Petrich):
	Suppressed an exposed "dprintf" as an unnecessary interrupt.

Feb 16, 2000 (Loren Petrich):
	Added a check on the polygon index after a line-transparency check;
	this is in case there is no polygon on the other side.

Feb 17, 2000 (Loren Petrich):
	Fixed stuff near GUESS_HYPOTENUSE() to be long-distance-friendly

Feb 19, 2000 (Loren Petrich):
	Added growable lists of indices of objects to be checked for collisions

Feb 24, 2000 (Loren Petrich):
	Suppressed some asserts about monster speeds

Apr 27, 2000 (Loren Petrich):
	Added some behavior in the case of a monster both floating and flying
	to handle the map "Aqualung" correctly.

May 29, 2000 (Loren Petirch):
	Fixed side effect of fixing keyframe-never-zero bug:
	if the keyframe is zero, then a sequence never triggers shrapnel damage.
	Thus, Hunters die a soft death more harmlessly.

Jun 11, 2000 (Loren Petrich):
	Pegging health and oxygen to maximum values when damaged;
	takes into account negative damage from healing projectiles.

Jul 1, 2000 (Loren Petrich):
	Inlined the accessors

Aug 30, 2000 (Loren Petrich):
	Added stuff for unpacking and packing
	
Oct 13, 2000 (Loren Petrich)
	Converted the intersected-objects list into a Standard Template Library vector

Oct 26, 2000 (Mark Levin)
	Revealed a few functions needed by Pfhortran

Jan 12, 2003 (Loren Petrich)
	Added controllable damage kicks
*/

#include <string.h>
#include <limits.h>

//#include "cseries.h"
#include "header.h"
#include "map.h"
#include "render.h"
#include "interface.h"
#include "flood_map.h"
#include "effects.h"
#include "monsters.h"
#include "projectiles.h"
#include "player.h"
#include "platforms.h"
#include "scenery.h"
#include "mysound.h"
#include "fades.h"
#include "items.h"
#include "media.h"
#include "Packing.h"
//#include "lua_script.h"


#ifdef env68k
#pragma segment objects
#endif

/*
//explosive deaths should cause damage during their key frame
*/

/* ---------- sounds */

/* ---------- constants */

#define OBSTRUCTION_DEACTIVATION_MASK 0x7

#define EVASIVE_MANOUVER_DISTANCE WORLD_ONE_HALF

#define MONSTER_EXTERNAL_DECELERATION (WORLD_ONE/200)
#define MONSTER_MINIMUM_EXTERNAL_VELOCITY (10*MONSTER_EXTERNAL_DECELERATION)
#define MONSTER_MAXIMUM_EXTERNAL_VELOCITY (TICKS_PER_SECOND*MONSTER_EXTERNAL_DECELERATION)

/* the height below which we don’t bother to float up a ledge (we just run right over it) */
#define MINIMUM_FLOATING_HEIGHT WORLD_ONE_FOURTH

#define MINIMUM_ACTIVATION_SEPARATION TICKS_PER_SECOND

/* when looking for things under or at this light intensity the monster must use his dark visual range */
#define LOW_LIGHT_INTENSITY 0

/* maximum area we will search out to find a new target */
#define MAXIMUM_TARGET_SEARCH_AREA (7*WORLD_ONE*WORLD_ONE)

#define MONSTER_PLATFORM_BUFFER_DISTANCE (WORLD_ONE/8)

#define GLUE_TRIGGER_ACTIVATION_RANGE (8*WORLD_ONE)
#define MONSTER_ALERT_ACTIVATION_RANGE (5*WORLD_ONE)

#define MONSTER_PATHFINDING_OBSTRUCTION_COST (2*WORLD_ONE*WORLD_ONE)
#define MONSTER_PATHFINDING_PLATFORM_COST (4*WORLD_ONE*WORLD_ONE)
#define MINIMUM_MONSTER_PATHFINDING_POLYGON_AREA (WORLD_ONE)

#define TERMINAL_VERTICAL_MONSTER_VELOCITY (WORLD_ONE/5)

#define MINIMUM_DYING_EXTERNAL_VELOCITY (WORLD_ONE/8)

#define CIVILIANS_KILLED_BY_PLAYER_THRESHHOLD 3
#define CIVILIANS_KILLED_DECREMENT_MASK 0x1ff

enum /* monster attitudes, extracted from enemies and friends bitfields by get_monster_attitude() */
{
	_neutral,
	_friendly,
	_hostile
};

enum /* returned by find_obstructing_terrain_feature() */
{
	_standing_on_sniper_ledge,
	_entering_platform_polygon,
	_leaving_platform_polygon,
	_flying_or_floating_transition
};

#define MINIMUM_SNIPER_ELEVATION WORLD_ONE_HALF

/* ---------- structures */

struct monster_pathfinding_data
{
	struct monster_definition *definition;
	struct monster_data *monster;
	
	bool cross_zone_boundaries;
};

// How much external velocity is imparted by some damage?
struct damage_kick_definition
{
	short base_value;
	float delta_vitality_multiplier;
	bool is_also_vertical;
};

/* ---------- definitions */

// LP: implements commented-out damage-kick code
struct damage_kick_definition damage_kick_definitions[NUMBER_OF_DAMAGE_TYPES] = 
{
	{0, 1, true}, // _damage_explosion,
	{0, 3, true}, // _damage_electrical_staff,
	{0, 1, false}, // _damage_projectile,
	{0, 1, false}, // _damage_absorbed,
	{0, 1, false}, // _damage_flame,
	{0, 1, false}, // _damage_hound_claws,
	{0, 1, false}, // _damage_alien_projectile,
	{0, 1, false}, // _damage_hulk_slap,
	{0, 3, true}, // _damage_compiler_bolt,
	{0, 0, false}, // _damage_fusion_bolt,
	{0, 1, false}, // _damage_hunter_bolt,
	{0, 1, false}, // _damage_fist,
	{250, 0, false}, // _damage_teleporter,
	{0, 1, false}, // _damage_defender,
	{0, 3, true}, // _damage_yeti_claws,
	{0, 1, false}, // _damage_yeti_projectile,
	{0, 1, false}, // _damage_crushing,
	{0, 1, false}, // _damage_lava,
	{0, 1, false}, // _damage_suffocation,
	{0, 1, false}, // _damage_goo,
	{0, 1, false}, // _damage_energy_drain,
	{0, 1, false}, // _damage_oxygen_drain,
	{0, 1, false}, // _damage_hummer_bolt,
	{0, 0, true} // _damage_shotgun_projectile,
};

/* ---------- globals */

/* import monster definition constants, structures and globals */
#include "monster_definitions.h"

// LP addition: growable list of intersected objects
static vector<short> IntersectedObjects;

/* ---------- private prototypes */

static monster_definition *get_monster_definition(
	const short type);

//static void monster_needs_path(short monster_index, bool immediately);
static void generate_new_path_for_monster(short monster_index);
void advance_monster_path(short monster_index);

static short get_monster_attitude(short monster_index, short target_index);
void change_monster_target(short monster_index, short target_index);
//static bool switch_target_check(short monster_index, short attacker_index, short delta_vitality);
static bool clear_line_of_sight(short viewer_index, short target_index, bool full_circle);

static void handle_moving_or_stationary_monster(short monster_index);
static void execute_monster_attack(short monster_index);
static void kill_monster(short monster_index);
//static bool translate_monster(short monster_index, world_distance distance);
//static bool try_monster_attack(short monster_index);
			
long monster_pathfinding_cost_function(short source_polygon_index, short line_index,
	short destination_polygon_index, void *data);

void set_monster_action(short monster_index, short action);
void set_monster_mode(short monster_index, short new_mode, short target_index);

static short find_obstructing_terrain_feature(short monster_index, short *feature_index, short *relevant_polygon_index);

static short position_monster_projectile(short aggressor_index, short target_index, struct attack_definition *attack,
	world_point3d *origin, world_point3d *destination, world_point3d *_vector, angle theta);

static void update_monster_vertical_physics_model(short monster_index);
static void update_monster_physics_model(short monster_index);

//static long monster_activation_flood_proc(short source_polygon_index, short line_index,
//	short destination_polygon_index, void *data);

static bool attempt_evasive_manouvers(short monster_index);

static short nearest_goal_polygon_index(short polygon_index);
static long nearest_goal_cost_function(short source_polygon_index, short line_index,
	short destination_polygon_index, void *unused);

static void cause_shrapnel_damage(short monster_index);

// For external use
monster_definition *get_monster_definition_external(const short type);

/* ---------- code */

monster_data *get_monster_data(
	short monster_index)
{
	struct monster_data *monster = GetMemberWithBounds(monsters,monster_index,MAXIMUM_MONSTERS_PER_MAP);
	
	vassert(monster, csprintf(temporary, "monster index #%d is out of range", monster_index));
	vassert(SLOT_IS_USED(monster), csprintf(temporary, "monster index #%d (%p) is unused", monster_index, monster));
	
	return monster;
}

monster_definition *get_monster_definition(
	const short type)
{
	monster_definition *definition = GetMemberWithBounds(monster_definitions,type,NUMBER_OF_MONSTER_TYPES);
	assert(definition);
	
	return definition;
}

//a non-inlined version for external use
monster_definition *get_monster_definition_external(
	const short type)
{
	return get_monster_definition(type);
}


/* returns new monster index if successful, NONE otherwise */
short new_monster(
	struct object_location *location,
	short monster_type)
{
	struct monster_definition *definition= get_monster_definition(monster_type);
	short original_monster_type= monster_type;
	struct monster_data *monster;
	short drop_mask= NONE;
	short monster_index= NONE;
	short flags= _monster_has_never_been_activated;

	switch (dynamic_world->game_information.difficulty_level)
	{
		case _wuss_level: drop_mask= 3; break; /* drop every fourth monster */
		case _easy_level: drop_mask= 7; break; /* drop every eighth monster */
		/* otherwise, drop no monsters */
	}
	
	if ((definition->flags&_monster_cannot_be_dropped) || !(definition->flags&_monster_is_alien) || drop_mask==NONE || (++dynamic_world->new_monster_vanishing_cookie&drop_mask))
	{
		/* check to see if we should promote or demote this monster based on difficulty level */
		if (definition->flags&_monster_major)
		{
			short demote_mask= NONE;
			
			switch (dynamic_world->game_information.difficulty_level)
			{
				case _wuss_level: demote_mask= 1; break; /* demote every other major */
				case _easy_level: demote_mask= 3; break; /* demote every fourth major */
				/* otherwise, demote no monsters */
			}
			
			if (demote_mask!=NONE && !(++dynamic_world->new_monster_mangler_cookie&demote_mask)) definition= get_monster_definition(monster_type-= 1), flags|= _monster_was_demoted;
		}
		else
		{
			if (definition->flags&_monster_minor)
			{
				short promote_mask= NONE;
				
				switch (dynamic_world->game_information.difficulty_level)
				{
					case _major_damage_level: promote_mask= 1; break; /* promote every other minor */
					case _total_carnage_level: promote_mask= 0; break; /* promote every minor */
					/* otherwise, promote no monsters */ 
				}
				if (promote_mask!=NONE && !(++dynamic_world->new_monster_mangler_cookie&promote_mask)) definition= get_monster_definition(monster_type+= 1), flags|= _monster_was_promoted;
			}
		}
		
		for (monster_index=0,monster=monsters;monster_index<MAXIMUM_MONSTERS_PER_MAP;++monster_index,++monster)
		{
			if (SLOT_IS_FREE(monster))
			{
				short object_index= new_map_object(location, BUILD_DESCRIPTOR(definition->collection, definition->stationary_shape));
				
				if (object_index!=NONE)
				{
					struct object_data *object= get_object_data(object_index);

					/* not doing this in !DEBUG resulted in sync errors; mmm... random data, so tasty */
					obj_set(*monster, 0x80);
	
					if (location->flags&_map_object_is_blind) flags|= _monster_is_blind;
					if (location->flags&_map_object_is_deaf) flags|= _monster_is_deaf;
					if (location->flags&_map_object_floats) flags|= _monster_teleports_out_when_deactivated;
				
					/* initialize the monster_data structure; we don’t touch most of the fields here
						because the monster is initially inactive (and they will be initialized when the
						monster is activated) */
					monster->type= monster_type;
					monster->activation_bias= DECODE_ACTIVATION_BIAS(location->flags);
					monster->vitality= NONE; /* if a monster is activated with vitality==NONE, it will be properly initialized */
					monster->object_index= object_index;
					monster->flags= flags;
					monster->goal_polygon_index= monster->activation_bias==_activate_on_goal ?
						nearest_goal_polygon_index(location->polygon_index) : NONE;
					monster->sound_polygon_index= object->polygon;
					monster->sound_location= object->location;
					MARK_SLOT_AS_USED(monster);
					
					/* initialize the monster’s object */
					if (definition->flags&_monster_is_invisible) object->transfer_mode= _xfer_invisibility;
					if (definition->flags&_monster_is_subtly_invisible) object->transfer_mode= _xfer_subtle_invisibility;
					if (definition->flags&_monster_is_enlarged) object->flags|= _object_is_enlarged;
					if (definition->flags&_monster_is_tiny) object->flags|= _object_is_tiny;
					SET_OBJECT_SOLIDITY(object, true);
					SET_OBJECT_OWNER(object, _object_is_monster);
					object->permutation= monster_index;
					object->sound_pitch= definition->sound_pitch;

					/* make sure the object frequency stuff keeps track of how many monsters are
						on the map */
					object_was_just_added(_object_is_monster, original_monster_type);
				}
				else
				{
					monster_index= NONE;
				}
				
				break;
			}
		}
		if (monster_index==MAXIMUM_MONSTERS_PER_MAP) monster_index= NONE;
	}

	/* keep track of how many civilians we drop on this level */
//	if (monster_index!=NONE && (definition->_class&_class_human_civilian)) dynamic_world->current_civilian_count+= 1;

	return monster_index;
}

/* assumes ∂t==1 tick *
void move_monsters(
	void)
    */

/* when a monster dies, all monsters locked on it need to find something better to do; this
	function should be called before the given target is expunged from the monster list but
	after it is marked as dying *
void monster_died(
	short target_index)
    */

void initialize_monsters(
	void)
{
	/* initialize our globals to be the same thing on all machines */
	dynamic_world->civilians_killed_by_players= 0;
	dynamic_world->last_monster_index_to_get_time= -1;
	dynamic_world->last_monster_index_to_build_path= -1;
	dynamic_world->new_monster_mangler_cookie= global_random();
	dynamic_world->new_monster_vanishing_cookie= global_random();
}

/* call this when a new level is loaded from disk so the monsters can cope with their new world */
void initialize_monsters_for_new_level(
	void)
{
	struct monster_data *monster;
	short monster_index;

	/* when a level is loaded after being saved all of an active monster’s data is still intact,
		but it’s path no longer exists.  this function resets all monsters so that they recalculate
		their paths, first thing. */
	for (monster_index=0,monster=monsters;monster_index<MAXIMUM_MONSTERS_PER_MAP;++monster_index,++monster)
	{
		if (SLOT_IS_USED(monster)&&MONSTER_IS_ACTIVE(monster))
		{
			SET_MONSTER_NEEDS_PATH_STATUS(monster, true);
			monster->path= NONE;
		}
	}
}
/*
void load_monster_sounds(
	short monster_type)
{
	if (monster_type!=NONE)
	{
		struct monster_definition *definition= get_monster_definition(monster_type);
		
		process_collection_sounds(definition->collection, load_sound);
		
		load_projectile_sounds(definition->ranged_attack.type);
		load_projectile_sounds(definition->melee_attack.type);
		
		load_sounds(&definition->activation_sound, 8);
	}
}
/*
void mark_monster_collections(
	short monster_type,
	bool loading)
{
	if (monster_type!=NONE)
	{
		struct monster_definition *definition= get_monster_definition(monster_type);

		/* mark the monster collection *
		mark_collection(definition->collection, loading);
		
		/* mark the monster’s projectile’s collection *
		mark_projectile_collections(definition->ranged_attack.type, loading);
		mark_projectile_collections(definition->melee_attack.type, loading);
	}
}
*/
enum
{
	MAXIMUM_NEED_TARGET_INDEXES= 32
};
/*
void activate_nearby_monsters(
	short target_index, /* activate with lock on this target (or NONE for lock-less activation) *
	short caller_index, /* start the flood from here *
	short flags)

static long monster_activation_flood_proc(
	short source_polygon_index,
	short line_index,
	short destination_polygon_index,
	void *data)
*/
#define LIVE_ALIEN_THRESHHOLD 8

bool live_aliens_on_map(
	void)
{
	bool found_alien_which_must_be_killed= false;
	struct monster_data *monster;
	short live_alien_count= 0;
	short threshhold= LIVE_ALIEN_THRESHHOLD;
	short monster_index;
	
	for (monster_index= 0, monster= monsters; monster_index<MAXIMUM_MONSTERS_PER_MAP; ++monster_index, ++monster)
	{
		if (SLOT_IS_USED(monster))
		{
			struct monster_definition *definition= get_monster_definition(monster->type);

#if 0			
			switch (monster->type)
			{
				case _monster_juggernaut_minor:
				case _monster_juggernaut_major:
				case _monster_alien_leader:
					found_alien_which_must_be_killed= true;
					break;
			}
#endif
			
			if ((definition->flags&_monster_is_alien) ||
				((static_world->environment_flags&_environment_rebellion) && !MONSTER_IS_PLAYER(monster)))
			{
				live_alien_count+= 1;
			}
		}
	}
	
	if (static_world->environment_flags&_environment_rebellion) threshhold= 0;
	
	return live_alien_count<=threshhold ? found_alien_which_must_be_killed : true;
}

/* activate the given monster (initially unlocked) *
void activate_monster(
	short monster_index)
    */
/*
void deactivate_monster(
	short monster_index)*/

/* returns a list of object indexes of all monsters in or adjacent to the given polygon,
	up to maximum_object_count. */
// LP change: called with growable list
bool possible_intersecting_monsters(
	vector<short> *IntersectedObjectsPtr,
	unsigned maximum_object_count,
	short polygon_index,
	bool include_scenery)
{
	struct polygon_data *polygon= get_polygon_data(polygon_index);
	short *neighbor_indexes= get_map_indexes(polygon->first_neighbor_index, polygon->neighbor_count);
	bool found_solid_object= false;

	// Skip this step if neighbor indexes were not found
	if (!neighbor_indexes) return found_solid_object;

	for (short i=0;i<polygon->neighbor_count;++i)
	{
		struct polygon_data *neighboring_polygon= get_polygon_data(*neighbor_indexes++);
		
		if (!POLYGON_IS_DETACHED(neighboring_polygon))
		{
			short object_index= neighboring_polygon->first_object;
			
			while (object_index!=NONE)
			{
				struct object_data *object= get_object_data(object_index);
				bool solid_object= false;
				
				if (!OBJECT_IS_INVISIBLE(object))
				{
					switch (GET_OBJECT_OWNER(object))
					{
						case _object_is_monster:
						{
							struct monster_data *monster= get_monster_data(object->permutation);
						
							if (!MONSTER_IS_DYING(monster) && !MONSTER_IS_TELEPORTING(monster))
							{
								solid_object= true;
							}
							
							break;
						}
						
						case _object_is_scenery:
							if (include_scenery && OBJECT_IS_SOLID(object)) solid_object= true;
							break;
					}
					
					if (solid_object)
					{
						found_solid_object= true;
						
						// LP change:
						if (IntersectedObjectsPtr && IntersectedObjectsPtr->size()<maximum_object_count) /* do we have enough space to add it? */
						{
							unsigned j;
							
							/* only add this object_index if it's not already in the list */
							vector<short>& IntersectedObjects = *IntersectedObjectsPtr;
							for (j=0; j<IntersectedObjects.size() && IntersectedObjects[j]!=object_index; ++j)
								;
							if (j==IntersectedObjects.size())
								IntersectedObjects.push_back(object_index);
						}
					}
				}
				
				object_index= object->next_object;
			}
		}
	}

	return found_solid_object;
}

/* when a target changes polygons, all monsters locked on it must recalculate their paths.
	target is an index into the monster list. *
void monster_moved(
	short target_index,
	short old_polygon_index)
{

/* returns NONE or a monster_index that prevented us from moving */
short legal_player_move(
	short monster_index,
	world_point3d *new_location,
	world_distance *object_floor) /* must be set on entry */
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct object_data *object= get_object_data(monster->object_index);
	world_point3d *old_location= &object->location;
	size_t monster_count;
	world_distance radius, height;
	short obstacle_index= NONE;

	get_monster_dimensions(monster_index, &radius, &height);	
	
	IntersectedObjects.clear();
	possible_intersecting_monsters(&IntersectedObjects, LOCAL_INTERSECTING_MONSTER_BUFFER_SIZE, object->polygon, true);
	monster_count = IntersectedObjects.size();
	for (size_t i=0;i<monster_count;++i)
	{
		struct object_data *obstacle= get_object_data(IntersectedObjects[i]);
		world_distance obstacle_radius, obstacle_height;
		
		switch (GET_OBJECT_OWNER(obstacle))
		{
			case _object_is_monster: get_monster_dimensions(obstacle->permutation, &obstacle_radius, &obstacle_height); break;
			case _object_is_scenery: get_scenery_dimensions(obstacle->permutation, &obstacle_radius, &obstacle_height); break;
			default:
				assert(false);
				break;
		}
		
		if (IntersectedObjects[i]!=monster->object_index) /* no self-intersection */
		{
			world_point3d *obstacle_location= &obstacle->location;

			world_distance separation= radius+obstacle_radius;
			int32 separation_squared= separation*separation;

			world_distance new_dx= obstacle_location->x-new_location->x;
			world_distance new_dy= obstacle_location->y-new_location->y;
			int32 new_distance_squared= new_dx*new_dx+new_dy*new_dy;
			
			if (new_distance_squared<separation_squared)
			{
				world_distance old_dx= obstacle_location->x-old_location->x;
				world_distance old_dy= obstacle_location->y-old_location->y;
				int32 old_distance_squared= old_dx*old_dx+old_dy*old_dy;

				if (old_distance_squared>new_distance_squared)
				{
					world_distance this_object_floor= obstacle_location->z+obstacle_height;
					
					/* it’s possible we don’t intersect in z */
					if (new_location->z+height<obstacle_location->z) continue; 
					if (new_location->z>this_object_floor)
					{
						if (this_object_floor>*object_floor) *object_floor= this_object_floor;
						continue;
					}
					
//					dprintf("#%d (%d,%d) hit #%d (%d,%d) moving to (%d,%d)", monster_index, old_location->x, old_location->y, obstacle->permutation, obstacle_location->x, obstacle_location->y, new_location->x, new_location->y);
					obstacle_index= IntersectedObjects[i];
					break;
				}
			}
		}
	}
	
	return obstacle_index;
}

/* returns NONE or a monster_index that prevented us from moving */
short legal_monster_move(
	short monster_index,
	angle facing, /* could be different than object->facing for players and ‘flying’ (heh heh) monsters */
	world_point3d *new_location)
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct object_data *object= get_object_data(monster->object_index);
//	world_point2d *old_location= (world_point2d *) &object->location;
	size_t monster_count;
	world_distance radius, height;
	short obstacle_index= NONE;

	get_monster_dimensions(monster_index, &radius, &height);	
	
	IntersectedObjects.clear();
	possible_intersecting_monsters(&IntersectedObjects, LOCAL_INTERSECTING_MONSTER_BUFFER_SIZE, object->polygon, true);
	monster_count= IntersectedObjects.size();
	for (size_t i=0;i<monster_count;++i)
	{
		struct object_data *obstacle= get_object_data(IntersectedObjects[i]);
		world_distance obstacle_radius, obstacle_height;
			
		switch (GET_OBJECT_OWNER(obstacle))
		{
			case _object_is_monster: get_monster_dimensions(obstacle->permutation, &obstacle_radius, &obstacle_height); break;
			case _object_is_scenery: get_scenery_dimensions(obstacle->permutation, &obstacle_radius, &obstacle_height); break;
			default:
				assert(false);
				break;
		}
			
		// LP change:
		if (IntersectedObjects[i]!=monster->object_index) /* no self-intersection */
		{
			world_point3d *obstacle_location= &obstacle->location;
			
			if (obstacle_location->z<new_location->z+height && obstacle_location->z+obstacle_height>new_location->z)
			{
				world_distance separation= radius+obstacle_radius;
				world_distance dx= obstacle_location->x-new_location->x;
				world_distance dy= obstacle_location->y-new_location->y;
				
				if (GET_OBJECT_OWNER(obstacle)!=_object_is_scenery && obstacle->permutation>monster_index && !MONSTER_IS_PLAYER(get_monster_data(obstacle->permutation))) separation= (separation>>1) + (separation>>2);
				if (dx>-separation && dx<separation && dy>-separation && dy<separation)
				{
					/* we intersect sloppily; get arctan to be sure */
					angle theta= NORMALIZE_ANGLE(arctangent(dx, dy)-facing);
					
					if (theta<EIGHTH_CIRCLE||theta>FULL_CIRCLE-EIGHTH_CIRCLE)
					{
//						dprintf("#%d (%d,%d) hit #%d (%d,%d) moving to (%d,%d)", monster_index, old_location->x, old_location->y, obstacle->permutation, obstacle_location->x, obstacle_location->y, new_location->x, new_location->y);
						obstacle_index= IntersectedObjects[i];
						break;
					}
				}
			}
		}
	}
	
	return obstacle_index;
}

void get_monster_dimensions(
	short monster_index,
	world_distance *radius,
	world_distance *height)
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct monster_definition *definition= get_monster_definition(monster->type);

	*radius= definition->radius;
	*height= definition->height;
}
/*
void damage_monsters_in_radius(
	short primary_target_index,
	short aggressor_index,
	short aggressor_type,
	world_point3d *epicenter,
	short epicenter_polygon_index,
	world_distance radius,
	struct damage_definition *damage,
	short projectile_index)
/*
void damage_monster(
	short target_index,
	short aggressor_index,
	short aggressor_type,
	world_point3d *epicenter,
	struct damage_definition *damage,
	short projectile_index)
bool bump_monster(
	short aggressor_index,
	short monster_index)

bool legal_polygon_height_change(
	short polygon_index,
	world_distance new_floor_height,
	world_distance new_ceiling_height,
	struct damage_definition *damage)
{
/* we’ve already checked and this monster is not obstructing the polygon from changing heights *
void adjust_monster_for_polygon_height_change(
	short monster_index,
	short polygon_index,
	world_distance new_floor_height,
	world_distance new_ceiling_height)
{
	struct polygon_data *polygon= get_polygon_data(polygon_index);
	struct monster_data *monster= get_monster_data(monster_index);
	world_distance radius, height;
	
	get_monster_dimensions(monster_index, &radius, &height);
	
	if (MONSTER_IS_PLAYER(monster))
	{
		adjust_player_for_polygon_height_change(monster_index, polygon_index, new_floor_height, new_ceiling_height);
	}
	else
	{
		struct object_data *object= get_object_data(monster->object_index);
		
		if (object->location.z==polygon->floor_height) object->location.z= new_floor_height;
	}
}

void accelerate_monster(
	short monster_index,
	world_distance vertical_velocity,
	angle direction,
	world_distance velocity)
{
	struct monster_data *monster= get_monster_data(monster_index);
	
	if (MONSTER_IS_PLAYER(monster))
	{
		accelerate_player(monster_index, vertical_velocity, direction, velocity);
	}
	else
	{
		struct object_data *object= get_object_data(monster->object_index);
		
		object->facing= NORMALIZE_ANGLE(direction+HALF_CIRCLE);
		monster->external_velocity+= velocity;
		monster->vertical_velocity+= PIN(monster->vertical_velocity+vertical_velocity, -TERMINAL_VERTICAL_MONSTER_VELOCITY, TERMINAL_VERTICAL_MONSTER_VELOCITY);
	}
}
*/
short get_monster_impact_effect(
	short monster_index)
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct monster_definition *definition= get_monster_definition(monster->type);
	short impact_effect_index= definition->impact_effect;
	
	if (MONSTER_IS_PLAYER(monster))
	{
		struct object_data *object= get_object_data(monster->object_index);
		
		switch (object->transfer_mode)
		{
			case _xfer_static:
				impact_effect_index= NONE;
				break;
		}
	}
	
	return impact_effect_index;
}

short get_monster_melee_impact_effect(
	short monster_index)
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct monster_definition *definition= get_monster_definition(monster->type);
	
	return definition->melee_impact_effect;
}

#if 0
/* pick a random player; flood out from that player until we find a polygon legal for a monster
	drop whose center is not player visible. */
void pick_nearby_random_monster_position(
	world_point2d *p,
	short *polygon_index)
{
	short player_index= global_random()%dynamic_world->player_count;
	short flood_polygon_index= get_player_data(player_index)->camera_polygon_index;
	
	polygon_index= flood_map(polygon_index, area, monster_activation_flood_proc, _breadth_first, &flood_flags);
	while (polygon_index!=NONE)
	{
		short object_index;
		struct object_data *object;
		struct polygon_data *polygon= get_polygon_data(polygon_index);
		
		polygon_index= flood_map(NONE, area, monster_activation_flood_proc, _breadth_first, &flood_flags);
	}
}
#endif

/* ---------- private code */
/*
static void cause_shrapnel_damage(
	short monster_index)
{
	struct monster_data *monster= get_monster_data(monster_index);
	struct object_data *object= get_object_data(monster->object_index);
	struct monster_definition *definition= get_monster_definition(monster->type);

	if (definition->shrapnel_radius!=NONE)
	{
		damage_monsters_in_radius(NONE, NONE, NONE, &object->location, object->polygon,
			definition->shrapnel_radius, &definition->shrapnel_damage, NONE);
	}
}
/*
static void update_monster_vertical_physics_model(
	short monster_index)
static void update_monster_physics_model(
	short monster_index)

static void monster_needs_path(
	short monster_index,
	bool immediately)
{
	struct monster_data *monster= get_monster_data(monster_index);
	
	if (monster->path!=NONE && immediately) delete_path(monster->path), monster->path= NONE;
	if (monster->action==_monster_is_moving && immediately) set_monster_action(monster_index, _monster_is_stationary);
	SET_MONSTER_NEEDS_PATH_STATUS(monster, true);
}
*/
void set_monster_mode(
	short monster_index,
	short new_mode,
	short target_index)
{
}
/* this function decides what the given monster actually wants to do, and then generates a path
	to get him there; if a monster who has lost lock calls this function, he will be forced to
	wander randomly or follow a guard path. */
static void generate_new_path_for_monster(
	short monster_index)
{}


/* somebody just did damage to us; see if we should start attacking them or not.  berserk
	monsters always switch targets.  this is where we check to see if we go berserk, right?
	monster->vitality has already been changed (a monster who just bumped into another monster
	also calls this, with a delta_vitality of zero).  returns true if an attack was started. *
static bool switch_target_check(
	short monster_index,
	short attacker_index,
	short delta_vitality)*/
static short get_monster_attitude(
	short monster_index,
	short target_index)
{
	short attitude = 0;
	return attitude;
}

/* find_closest_appropriate_target() tries to do just that.  it is a little broken in that it
	treats all monsters in a given polygon as if they were the same distance away, which could
	result in strange behavior.  the assumption is that if there is a more accessable hostile monster
	nearby, that monster will attack and thus end a possible wild goose chase.  if there is a
	closer hostile target which the aggressor subsequently attempts to move through, he will
	change lock and attack the obstruction instead, which will help minimize weirdness.
	full_circle is passed directly to clear_line_of_sight(). *
short find_closest_appropriate_target(
	short aggressor_index,
	bool full_circle)
{
/* if ‘full_circle’ is true, the monster can see in all directions.  if ‘full_circle’ is false
	the monster respects his visual_arc and current facing.  clear_line_of_sight() is implemented
	wholly in 2D and only attempts to connect the centers of the two monsters by a line. */
static bool clear_line_of_sight(
	short viewer_index,
	short target_index,
	bool full_circle)
{return false;
}

/* lock the given monster onto the given target, playing a locking sound if the monster
	previously didn’t have a lock *
void change_monster_target(
	short monster_index,
	short target_index)
*/
static void handle_moving_or_stationary_monster(
  short monster_index){}
  
void set_monster_action(
	short monster_index,
	short action)
{}

/* do whatever needs to be done when this monster dies and remove it from the monster list *
static void kill_monster(
	short monster_index)


/* move the monster along his current heading; if he reaches the center of his destination square,
	then point him at the next square and send him off.  this used to chuck if the monster moved
	too far during a certain turn (which was completely possible when the player was wearing the
	red cloak in Pathways), but that was fixed.  i just recoded this for marathon and it looks
	a hell of a lot better now. *
static bool translate_monster(
	short monster_index,
	world_distance distance)

    */
static bool attempt_evasive_manouvers(
	short monster_index)
{
	return false;
}

void advance_monster_path(
	short monster_index)
{}
  /*
static bool try_monster_attack(
	short monster_index)

static void execute_monster_attack(
	short monster_index)
{
  */

long monster_pathfinding_cost_function(
	short source_polygon_index,
	short line_index,
	short destination_polygon_index,
  void *vdata){return 0;}
/* returns the type and index of any interesting terrain feature (platform or door) in front
	of the given monster in his current direction; this lets us open doors and wait for
	platforms.  relevant_polygon_index is the polygon_index we have to pass to platform_is_accessable *
static short find_obstructing_terrain_feature(
	short monster_index,
	short *feature_index,
	short *relevant_polygon_index)

/* returns new polygon index; if destination is NULL then we fire along the monster’s facing
	and elevation, if destination is not NULL then we set it correctly and save the elevation angle */
static short position_monster_projectile(
	short aggressor_index,
	short target_index,
	struct attack_definition *attack,
	world_point3d *origin,
	world_point3d *destination,
	world_point3d *_vector,
	angle theta)
{
  return 0;
}

short nearest_goal_polygon_index(
	short polygon_index)
{
  return 0;
}

static long nearest_goal_cost_function(
	short source_polygon_index,
	short line_index,
	short destination_polygon_index,
	void *unused)
{
  return 0;
}


// LP: will set player view attributes when trying to shoot a guided projectile.
void SetPlayerViewAttribs(int16 half_visual_arc, int16 half_vertical_visual_arc,
	world_distance visual_range, world_distance dark_visual_range)
{/*
	// Added a modified version of AlexJS's changes: change only if necessary
	// Restoring AlexJLS's changes
	monster_definition& PlayerAsMonster = monster_definitions[_monster_marine];
	if (half_visual_arc > 0 || PlayerAsMonster.half_visual_arc > 0)
		PlayerAsMonster.half_visual_arc = half_visual_arc;
	if (half_vertical_visual_arc > 0 || PlayerAsMonster.half_vertical_visual_arc > 0)
		PlayerAsMonster.half_vertical_visual_arc = half_vertical_visual_arc;
	if (visual_range > 0 || PlayerAsMonster.visual_range > 0)
		PlayerAsMonster.visual_range = visual_range;
	if (dark_visual_range > 0 || PlayerAsMonster.dark_visual_range > 0)
		PlayerAsMonster.dark_visual_range = dark_visual_range;*/
}


uint8 *unpack_monster_data(uint8 *Stream, monster_data *Objects, size_t Count)
{
	uint8* S = Stream;
	monster_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		StreamToValue(S,ObjPtr->vitality);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->path);
		StreamToValue(S,ObjPtr->path_segment_length);
		StreamToValue(S,ObjPtr->desired_height);
		
		StreamToValue(S,ObjPtr->mode);
		StreamToValue(S,ObjPtr->action);
		StreamToValue(S,ObjPtr->target_index);
		StreamToValue(S,ObjPtr->external_velocity);
		StreamToValue(S,ObjPtr->vertical_velocity);
		StreamToValue(S,ObjPtr->ticks_since_attack);
		StreamToValue(S,ObjPtr->attack_repetitions);
		StreamToValue(S,ObjPtr->changes_until_lock_lost);
		
		StreamToValue(S,ObjPtr->elevation);
		
		StreamToValue(S,ObjPtr->object_index);
		
		StreamToValue(S,ObjPtr->ticks_since_last_activation);
		
		StreamToValue(S,ObjPtr->activation_bias);
		
		StreamToValue(S,ObjPtr->goal_polygon_index);
		
		StreamToValue(S,ObjPtr->sound_location.x);
		StreamToValue(S,ObjPtr->sound_location.y);
		StreamToValue(S,ObjPtr->sound_location.z);
		StreamToValue(S,ObjPtr->sound_polygon_index);
		
		StreamToValue(S,ObjPtr->random_desired_height);
		
		S += 7*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_monster_data));
	return S;
}

uint8 *pack_monster_data(uint8 *Stream, monster_data *Objects, size_t Count)
{
	uint8* S = Stream;
	monster_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		ValueToStream(S,ObjPtr->vitality);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->path);
		ValueToStream(S,ObjPtr->path_segment_length);
		ValueToStream(S,ObjPtr->desired_height);
		
		ValueToStream(S,ObjPtr->mode);
		ValueToStream(S,ObjPtr->action);
		ValueToStream(S,ObjPtr->target_index);
		ValueToStream(S,ObjPtr->external_velocity);
		ValueToStream(S,ObjPtr->vertical_velocity);
		ValueToStream(S,ObjPtr->ticks_since_attack);
		ValueToStream(S,ObjPtr->attack_repetitions);
		ValueToStream(S,ObjPtr->changes_until_lock_lost);
		
		ValueToStream(S,ObjPtr->elevation);
		
		ValueToStream(S,ObjPtr->object_index);
		
		ValueToStream(S,ObjPtr->ticks_since_last_activation);
		
		ValueToStream(S,ObjPtr->activation_bias);
		
		ValueToStream(S,ObjPtr->goal_polygon_index);
		
		ValueToStream(S,ObjPtr->sound_location.x);
		ValueToStream(S,ObjPtr->sound_location.y);
		ValueToStream(S,ObjPtr->sound_location.z);
		ValueToStream(S,ObjPtr->sound_polygon_index);
		
		ValueToStream(S,ObjPtr->random_desired_height);
		
		S += 7*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_monster_data));
	return S;
}


inline void StreamToAttackDef(uint8* &S, attack_definition& Object)
{
	StreamToValue(S,Object.type);
	StreamToValue(S,Object.repetitions);
	StreamToValue(S,Object.error);
	StreamToValue(S,Object.range);
	StreamToValue(S,Object.attack_shape);
	
	StreamToValue(S,Object.dx);
	StreamToValue(S,Object.dy);
	StreamToValue(S,Object.dz);
}

inline void AttackDefToStream(uint8* &S, attack_definition& Object)
{
	ValueToStream(S,Object.type);
	ValueToStream(S,Object.repetitions);
	ValueToStream(S,Object.error);
	ValueToStream(S,Object.range);
	ValueToStream(S,Object.attack_shape);
	
	ValueToStream(S,Object.dx);
	ValueToStream(S,Object.dy);
	ValueToStream(S,Object.dz);
}


uint8 *unpack_monster_definition(uint8 *Stream, size_t Count)
{
	return unpack_monster_definition(Stream,monster_definitions,Count);
}

uint8 *unpack_monster_definition(uint8 *Stream, monster_definition* Objects, size_t Count)
{
	uint8* S = Stream;
	monster_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->collection);
		
		StreamToValue(S,ObjPtr->vitality);
		StreamToValue(S,ObjPtr->immunities);
		StreamToValue(S,ObjPtr->weaknesses);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->_class);
		StreamToValue(S,ObjPtr->friends);
		StreamToValue(S,ObjPtr->enemies);
		
		StreamToValue(S,ObjPtr->sound_pitch);
		StreamToValue(S,ObjPtr->activation_sound);
		StreamToValue(S,ObjPtr->friendly_activation_sound);
		StreamToValue(S,ObjPtr->clear_sound);
		StreamToValue(S,ObjPtr->kill_sound);
		StreamToValue(S,ObjPtr->apology_sound);
		StreamToValue(S,ObjPtr->friendly_fire_sound);
		StreamToValue(S,ObjPtr->flaming_sound);
		StreamToValue(S,ObjPtr->random_sound);
		StreamToValue(S,ObjPtr->random_sound_mask);
		
		StreamToValue(S,ObjPtr->carrying_item_type);
		
		StreamToValue(S,ObjPtr->radius);
		StreamToValue(S,ObjPtr->height);
		StreamToValue(S,ObjPtr->preferred_hover_height);	
		StreamToValue(S,ObjPtr->minimum_ledge_delta);
		StreamToValue(S,ObjPtr->maximum_ledge_delta);
		StreamToValue(S,ObjPtr->external_velocity_scale);
		StreamToValue(S,ObjPtr->impact_effect);
		StreamToValue(S,ObjPtr->melee_impact_effect);
		StreamToValue(S,ObjPtr->contrail_effect);
		
		StreamToValue(S,ObjPtr->half_visual_arc);
		StreamToValue(S,ObjPtr->half_vertical_visual_arc);
		StreamToValue(S,ObjPtr->visual_range);	
		StreamToValue(S,ObjPtr->dark_visual_range);
		StreamToValue(S,ObjPtr->intelligence);
		StreamToValue(S,ObjPtr->speed);
		StreamToValue(S,ObjPtr->gravity);
		StreamToValue(S,ObjPtr->terminal_velocity);
		StreamToValue(S,ObjPtr->door_retry_mask);
		StreamToValue(S,ObjPtr->shrapnel_radius);
		S = unpack_damage_definition(S,&ObjPtr->shrapnel_damage,1);
		
		StreamToValue(S,ObjPtr->hit_shapes);
		StreamToValue(S,ObjPtr->hard_dying_shape);
		StreamToValue(S,ObjPtr->soft_dying_shape);
		StreamToValue(S,ObjPtr->hard_dead_shapes);
		StreamToValue(S,ObjPtr->soft_dead_shapes);
		StreamToValue(S,ObjPtr->stationary_shape);
		StreamToValue(S,ObjPtr->moving_shape);
		StreamToValue(S,ObjPtr->teleport_in_shape);
		StreamToValue(S,ObjPtr->teleport_out_shape);
		
		StreamToValue(S,ObjPtr->attack_frequency);
		StreamToAttackDef(S,ObjPtr->melee_attack);
		StreamToAttackDef(S,ObjPtr->ranged_attack);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_monster_definition));
	return S;
}


uint8 *pack_monster_definition(uint8 *Stream, size_t Count)
{
	return pack_monster_definition(Stream,monster_definitions,Count);
}

uint8 *pack_monster_definition(uint8 *Stream, monster_definition *Objects, size_t Count)
{
	uint8* S = Stream;
	monster_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->collection);
		
		ValueToStream(S,ObjPtr->vitality);
		ValueToStream(S,ObjPtr->immunities);
		ValueToStream(S,ObjPtr->weaknesses);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->_class);
		ValueToStream(S,ObjPtr->friends);
		ValueToStream(S,ObjPtr->enemies);
		
		ValueToStream(S,ObjPtr->sound_pitch);
		ValueToStream(S,ObjPtr->activation_sound);
		ValueToStream(S,ObjPtr->friendly_activation_sound);
		ValueToStream(S,ObjPtr->clear_sound);
		ValueToStream(S,ObjPtr->kill_sound);
		ValueToStream(S,ObjPtr->apology_sound);
		ValueToStream(S,ObjPtr->friendly_fire_sound);
		ValueToStream(S,ObjPtr->flaming_sound);
		ValueToStream(S,ObjPtr->random_sound);
		ValueToStream(S,ObjPtr->random_sound_mask);
		
		ValueToStream(S,ObjPtr->carrying_item_type);
		
		ValueToStream(S,ObjPtr->radius);
		ValueToStream(S,ObjPtr->height);
		ValueToStream(S,ObjPtr->preferred_hover_height);	
		ValueToStream(S,ObjPtr->minimum_ledge_delta);
		ValueToStream(S,ObjPtr->maximum_ledge_delta);
		ValueToStream(S,ObjPtr->external_velocity_scale);
		ValueToStream(S,ObjPtr->impact_effect);
		ValueToStream(S,ObjPtr->melee_impact_effect);
		ValueToStream(S,ObjPtr->contrail_effect);
		
		ValueToStream(S,ObjPtr->half_visual_arc);
		ValueToStream(S,ObjPtr->half_vertical_visual_arc);
		ValueToStream(S,ObjPtr->visual_range);	
		ValueToStream(S,ObjPtr->dark_visual_range);
		ValueToStream(S,ObjPtr->intelligence);
		ValueToStream(S,ObjPtr->speed);
		ValueToStream(S,ObjPtr->gravity);
		ValueToStream(S,ObjPtr->terminal_velocity);
		ValueToStream(S,ObjPtr->door_retry_mask);
		ValueToStream(S,ObjPtr->shrapnel_radius);
		S = pack_damage_definition(S,&ObjPtr->shrapnel_damage,1);
		
		ValueToStream(S,ObjPtr->hit_shapes);
		ValueToStream(S,ObjPtr->hard_dying_shape);
		ValueToStream(S,ObjPtr->soft_dying_shape);
		ValueToStream(S,ObjPtr->hard_dead_shapes);
		ValueToStream(S,ObjPtr->soft_dead_shapes);
		ValueToStream(S,ObjPtr->stationary_shape);
		ValueToStream(S,ObjPtr->moving_shape);
		ValueToStream(S,ObjPtr->teleport_in_shape);
		ValueToStream(S,ObjPtr->teleport_out_shape);
		
		ValueToStream(S,ObjPtr->attack_frequency);
		AttackDefToStream(S,ObjPtr->melee_attack);
		AttackDefToStream(S,ObjPtr->ranged_attack);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_monster_definition));
	return S;
}

struct damage_kick_definition *original_damage_kick_definitions = NULL;
/*
class XML_DamageKickParser: public XML_ElementParser
{
	short Index;
	damage_kick_definition Data;
	
	// What is present?
	bool IndexPresent;
	enum {NumberOfValues = 3};
	bool IsPresent[NumberOfValues];
	
public:
	bool Start();
	bool HandleAttribute(const char *Tag, const char *Value);
	bool AttributesDone();
	bool ResetValues();

	XML_DamageKickParser(): XML_ElementParser("kick") {}
};

bool XML_DamageKickParser::Start()
{
	// back up old values first
	if (!original_damage_kick_definitions) {
		original_damage_kick_definitions = (struct damage_kick_definition *) malloc(sizeof(struct damage_kick_definition) * NUMBER_OF_DAMAGE_TYPES);
		assert(original_damage_kick_definitions);
		for (unsigned i = 0; i < NUMBER_OF_DAMAGE_TYPES; i++)
			original_damage_kick_definitions[i] = damage_kick_definitions[i];
	}

	IndexPresent = false;
	for (int k=0; k<NumberOfValues; k++)
		IsPresent[k] = false;
	
	return true;
}

bool XML_DamageKickParser::HandleAttribute(const char *Tag, const char *Value)
{
	if (StringsEqual(Tag,"index"))
	{
		if (ReadBoundedInt16Value(Value,Index,0,NUMBER_OF_DAMAGE_TYPES-1))
		{
			IndexPresent = true;
			return true;
		}
		else return false;
	}
	else if (StringsEqual(Tag,"base"))
	{
		if (ReadInt16Value(Value,Data.base_value))
		{
			IsPresent[0] = true;
			return true;
		}
		else return false;
	}
	else if (StringsEqual(Tag,"mult"))
	{
		if (ReadFloatValue(Value,Data.delta_vitality_multiplier))
		{
			IsPresent[1] = true;
			return true;
		}
		else return false;
	}
	else if (StringsEqual(Tag,"vertical"))
	{
		if (ReadBooleanValue(Value,Data.is_also_vertical))
		{
			IsPresent[2] = true;
			return true;
		}
		else return false;
	}
	UnrecognizedTag();
	return false;
}

bool XML_DamageKickParser::AttributesDone()
{
	// Verify...
	if (!IndexPresent)
	{
		AttribsMissing();
		return false;
	}
	damage_kick_definition& OrigData = damage_kick_definitions[Index];
	
	if (IsPresent[0]) OrigData.base_value = Data.base_value;
	if (IsPresent[1]) OrigData.delta_vitality_multiplier = Data.delta_vitality_multiplier;
	if (IsPresent[2]) OrigData.is_also_vertical = Data.is_also_vertical;
	
	return true;
}

bool XML_DamageKickParser::ResetValues()
{
	if (original_damage_kick_definitions) {
		for (unsigned i = 0; i < NUMBER_OF_DAMAGE_TYPES; i++)
			damage_kick_definitions[i] = original_damage_kick_definitions[i];
		free(original_damage_kick_definitions);
		original_damage_kick_definitions = NULL;
	}
	return true;
}

static XML_DamageKickParser DamageKickParser;


static XML_ElementParser DamageKicksParser("damage_kicks");


// XML-parser support
XML_ElementParser *DamageKicks_GetParser()
{
	DamageKicksParser.AddChild(&DamageKickParser);
	
	return &DamageKicksParser;
}
*/

struct monster_definition monster_definitions[NUMBER_OF_MONSTER_TYPES]=
{
	{ /* _monster_marine (can’t be used as a regular monster) */
		_collection_player, /* shape collection */
		20, 0, 0, /* vitality, immunities, weaknesses */
		_monster_cannot_be_dropped|_monster_can_die_in_flames, /* flags */

		_class_player,	
		_class_human, /* friends */
		-1, /* enemies */

		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */
		
		NONE, /* carrying item type */

		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		0, 0,
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_player_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */

		0, 0, /* half visual arc, half vertical visual arc */
		0, 0, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_almost_fast, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		0, 0, /* dying hard (popping), dying soft (falling) */
		0, 0, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
	},
	
	{ /* _monster_tick_minor */
		BUILD_COLLECTION(_collection_tick, 0), /* shape collection */
		0, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_flys|_monster_has_delayed_hard_death|_monster_cannot_attack, /* flags */
		
		_class_tick, /* class */
		-1, /* friends */
		0, /* enemies */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		_snd_tick_chatter, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE_HALF, WORLD_ONE_HALF, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		NONE, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		6, 3, /* dying hard (popping), dying soft (falling) */
		5, 5, /* hard dead frames, soft dead frames */
		1, 1, /* stationary shape, moving shape (no permutations) */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},

	{ /* _monster_tick_major */
		BUILD_COLLECTION(_collection_tick, 0), /* shape collection */
		0, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_flys|_monster_has_delayed_hard_death|_monster_cannot_attack, /* flags */
		
		_class_tick, /* class */
		-1, /* friends */
		0, /* enemies */
		
		_higher_frequency, /* sound pitch */
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		_snd_tick_chatter, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE_FOURTH, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		NONE, /* door retry mask */
		2*WORLD_ONE, {_damage_explosion, _alien_damage, 40, 20, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		4, 3, /* dying hard (popping), dying soft (falling) */
		5, 5, /* hard dead frames, soft dead frames */
		1, 1, /* stationary shape, moving shape (no permutations) */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},

	{ /* _monster_tick_kamakazi */
		BUILD_COLLECTION(_collection_tick, 0), /* shape collection */
		0, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_flys|_monster_is_kamakazi|_monster_has_delayed_hard_death, /* flags */
		
		_class_tick, /* class */
		0, /* friends */
		-1, /* enemies */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE_FOURTH, /* radius, height */
		0, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		NONE, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		6, 4, /* dying hard (popping), dying soft (falling) */
		5, 5, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape (no permutations) */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_minor_energy_drain, /* melee attack type */
			5000, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			0, 0, WORLD_ONE_HALF, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},

	{ /* _monster_compiler_minor */
		BUILD_COLLECTION(_collection_compiler, 0), /* shape collection */
		160, FLAG(_damage_flame)|FLAG(_damage_lava), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_floats|_monster_can_teleport_under_media, /* flags */

		_class_compiler, /* class */
		_class_compiler, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast2, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		UNONE, 2, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 3, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_compiler_bolt_minor, /* ranged attack type */
			0, /* repetitions */
			NUMBER_OF_ANGLES/200, /* error angle */
			20*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},

	{ /* _monster_compiler_major */
		BUILD_COLLECTION(_collection_compiler, 1), /* shape collection */
		200, FLAG(_damage_flame)|FLAG(_damage_lava), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_floats|_monster_can_teleport_under_media, /* flags */
	
		_class_compiler, /* class */
		_class_compiler, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast3, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		UNONE, 2, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 3, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_compiler_bolt_major, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			20*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_compiler_minor_invisible */
		BUILD_COLLECTION(_collection_compiler, 0), /* shape collection */
		160, FLAG(_damage_flame)|FLAG(_damage_lava), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_floats|_monster_is_invisible|_monster_can_teleport_under_media, /* flags */
	
		_class_compiler, /* class */
		_class_compiler, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		UNONE, 2, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 3, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_compiler_bolt_minor, /* ranged attack type */
			0, /* repetitions */
			NUMBER_OF_ANGLES/200, /* error angle */
			20*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_compiler_major_invisible */
		BUILD_COLLECTION(_collection_compiler, 1), /* shape collection */
		200, FLAG(_damage_flame)|FLAG(_damage_lava), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_floats|_monster_is_subtly_invisible|_monster_can_teleport_under_media, /* flags */
	
		_class_compiler, /* class */
		_class_compiler, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		0, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast5, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		UNONE, 2, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 3, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_compiler_bolt_major, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			20*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_fighter (minor) */
		BUILD_COLLECTION(_collection_fighter, 0), /* shape collection */
		40, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_can_die_in_flames, /* flags */
		
		_class_fighter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_fighter_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 2*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast1, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		1, 3, /* dying hard (popping), dying soft (falling) */
		6, 5, /* hard dead frames, soft dead frames */
		7, 0, /* stationary shape, moving shape */
		12, 12, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_staff, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			0, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			12*WORLD_ONE, /* range */
			3, /* ranged attack shape */
			
			0, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},

	{ /* _monster_fighter (major) */
		BUILD_COLLECTION(_collection_fighter, 1), /* shape collection */
		80, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_is_berserker|_monster_can_die_in_flames, /* flags */
	
		_class_fighter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_fighter_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast2, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		1, 3, /* dying hard (popping), dying soft (falling) */
		6, 5, /* hard dead frames, soft dead frames */
		7, 0, /* stationary shape, moving shape */
		12, 12, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_staff, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			0, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			12*WORLD_ONE, /* range */
			3, /* ranged attack shape */
			
			0, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},

	{ /* _monster_fighter (minor projectile) */
		BUILD_COLLECTION(_collection_fighter, 2), /* shape collection */
		80, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_uses_sniper_ledges|_monster_can_die_in_flames, /* flags */
	
		_class_fighter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_fighter_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast3, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		1, 3, /* dying hard (popping), dying soft (falling) */
		6, 5, /* hard dead frames, soft dead frames */
		7, 0, /* stationary shape, moving shape */
		12, 12, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_staff, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			WORLD_ONE/16, 0, WORLD_ONE_FOURTH, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_staff_bolt, /* ranged attack type */
			0, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},

	{ /* _monster_fighter (major projectile) */
		BUILD_COLLECTION(_collection_fighter, 3), /* shape collection */
		80, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_uses_sniper_ledges|_monster_is_berserker|_monster_can_die_in_flames, /* flags */
	
		_class_fighter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_fighter_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 5*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		1, 3, /* dying hard (popping), dying soft (falling) */
		6, 5, /* hard dead frames, soft dead frames */
		7, 0, /* stationary shape, moving shape */
		12, 12, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_staff, /* melee attack type */
			1, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			WORLD_ONE/16, 0, WORLD_ONE_FOURTH, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_staff_bolt, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},

	{ /* _civilian_crew "bob" */
		BUILD_COLLECTION(_collection_civilian, 0), /* shape collection */
		20, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_human_activation, _snd_kill_the_player, _snd_human_clear, _snd_human_trash_talk, _snd_human_apology, _snd_human_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_human_wail, /* dying flaming */
		_snd_human_chatter, 0x1f, /* random sound, random sound mask */

		_i_magnum_magazine, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_pistol_bullet, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			10*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_science "fred" */
		BUILD_COLLECTION(_collection_civilian, 1), /* shape collection */
		25, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human|_class_assimilated_civilian, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_human_activation, _snd_kill_the_player, _snd_human_clear, _snd_human_trash_talk, _snd_human_apology, _snd_human_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_human_wail, /* dying flaming */
		_snd_human_chatter, 0x1f, /* random sound, random sound mask */

		_i_magnum_magazine, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_pistol_bullet, /* ranged attack type */
			2, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			13*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_security "steve" */
		BUILD_COLLECTION(_collection_civilian, 2), /* shape collection */
		30, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human|_class_assimilated_civilian, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_human_activation, _snd_kill_the_player, _snd_human_clear, _snd_human_trash_talk, _snd_human_apology, _snd_human_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_human_wail, /* dying flaming */
		_snd_human_chatter, 0x1f, /* random sound, random sound mask */

		_i_magnum, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_pistol_bullet, /* ranged attack type */
			5, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			17*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_assimilated "evil bob" */
		BUILD_COLLECTION(_collection_civilian, 3), /* shape collection */
		30, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_is_kamakazi|_monster_can_die_in_flames, /* flags */
		
		_class_assimilated_civilian,
		_class_pfhor, /* friends */
		_class_player|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, _snd_human_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_human_wail, /* dying flaming */
		_snd_assimilated_human_chatter, 0xf, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_assimilated_civilian_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		15*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 80, 40, FIXED_ONE}, /* shrapnel radius, shrapnel damage  */
		
		10, /* being hit */
		11, UNONE, /* dying hard (popping), dying soft (falling) */
		4, 0, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		8, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},

	{ /* _monster_hummer_minor (small hummer) */
		BUILD_COLLECTION(_collection_hummer, 0), /* shape collection */
		40, 0, FLAG(_damage_fusion_bolt)|FLAG(_damage_compiler_bolt)|FLAG(_damage_electrical_staff), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_flys|_monster_minor|_monster_has_delayed_hard_death, /* flags */
		
		_class_hummer, /* class */
		_class_pfhor|_class_client, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
		
		_normal_frequency, /* sound pitch */
		_snd_hummer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE_HALF, /* radius, height */
		WORLD_ONE_FOURTH, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_hummer_spark, _effect_metallic_clang, _effect_rocket_contrail, /* impact effect, melee impact effect, contrail effect */
	
		HALF_CIRCLE, QUARTER_CIRCLE, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, 2, /* dying hard (popping), dying soft (falling) */
		4, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_minor_hummer, /* ranged attack type */
			0, /* repetitions */
			3, /* error angle */
			12*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			0, 0, 0, /* dx, dy, dz */
		}
	},

	{ /* _monster_hummer_major (big hummer) */
		BUILD_COLLECTION(_collection_hummer, 1), /* shape collection */
		60, 0, FLAG(_damage_fusion_bolt)|FLAG(_damage_compiler_bolt)|FLAG(_damage_electrical_staff), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_flys|_monster_major|_monster_has_delayed_hard_death, /* flags */
		
		_class_hummer, /* class */
		_class_pfhor|_class_client, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
		
		_normal_frequency, /* sound pitch */
		_snd_hummer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE_HALF, /* radius, height */
		WORLD_ONE_FOURTH, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_hummer_spark, _effect_metallic_clang, _effect_rocket_contrail, /* impact effect, melee impact effect, contrail effect */
	
		HALF_CIRCLE, QUARTER_CIRCLE, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, 2, /* dying hard (popping), dying soft (falling) */
		4, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_minor_hummer, /* ranged attack type */
			2, /* repetitions */
			5, /* error angle */
			12*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			0, 0, 0, /* dx, dy, dz */
		}
	},

	{ /* _monster_hummer_big_minor (big hummer) */
		BUILD_COLLECTION(_collection_hummer, 2), /* shape collection */
		40, 0, FLAG(_damage_fusion_bolt)|FLAG(_damage_compiler_bolt)|FLAG(_damage_electrical_staff), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_flys|_monster_minor|_monster_has_delayed_hard_death, /* flags */
		
		_class_hummer, /* class */
		_class_pfhor|_class_client, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
		
		_higher_frequency, /* sound pitch */
		_snd_hummer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE_HALF, /* radius, height */
		WORLD_ONE_FOURTH, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_hummer_spark, _effect_metallic_clang, _effect_rocket_contrail, /* impact effect, melee impact effect, contrail effect */
	
		HALF_CIRCLE, QUARTER_CIRCLE, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, 2, /* dying hard (popping), dying soft (falling) */
		4, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_minor_hummer, /* ranged attack type */
			0, /* repetitions */
			3, /* error angle */
			12*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			0, 0, 0, /* dx, dy, dz */
		}
	},

	{ /* _monster_hummer_big_major (angry hummer) */
		BUILD_COLLECTION(_collection_hummer, 3), /* shape collection */
		60, 0, FLAG(_damage_fusion_bolt)|FLAG(_damage_compiler_bolt)|FLAG(_damage_electrical_staff), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_flys|_monster_major|_monster_has_delayed_hard_death, /* flags */
		
		_class_hummer, /* class */
		_class_pfhor|_class_client, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
		
		_higher_frequency, /* sound pitch */
		_snd_hummer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE_HALF, /* radius, height */
		WORLD_ONE_FOURTH, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_hummer_spark, _effect_metallic_clang, _effect_rocket_contrail, /* impact effect, melee impact effect, contrail effect */
	
		HALF_CIRCLE, QUARTER_CIRCLE, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, 2, /* dying hard (popping), dying soft (falling) */
		4, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_minor_hummer, /* ranged attack type */
			2, /* repetitions */
			5, /* error angle */
			12*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			0, 0, 0, /* dx, dy, dz */
		}
	},

	{ /* _monster_hummer_possessed (hummer from durandal) */
		BUILD_COLLECTION(_collection_hummer, 4), /* shape collection */
		60, 0, FLAG(_damage_fusion_bolt)|FLAG(_damage_compiler_bolt)|FLAG(_damage_electrical_staff), /* vitality, immunities, weaknesses */
		_monster_flys|_monster_has_delayed_hard_death|_monster_attacks_immediately, /* flags */
		
		_class_possessed_hummer, /* class */
		_class_human, /* friends */
		_class_pfhor|_class_client|_class_native, /* enemies */
		
		_lower_frequency, /* sound pitch */
		_snd_hummer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE_HALF, /* radius, height */
		WORLD_ONE_FOURTH, /* preferred hover height */
		-5*WORLD_ONE, 5*WORLD_ONE, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_hummer_spark, _effect_metallic_clang, _effect_rocket_contrail, /* impact effect, melee impact effect, contrail effect */
	
		HALF_CIRCLE, QUARTER_CIRCLE, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 15*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, _alien_damage, 30, 10, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, 2, /* dying hard (popping), dying soft (falling) */
		4, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape (no permutations) */
		0, 0, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_durandal_hummer, /* ranged attack type */
			1, /* repetitions */
			5, /* error angle */
			12*WORLD_ONE, /* range */
			1, /* ranged attack shape */
			
			0, 0, 0, /* dx, dy, dz */
		}
	},

	{ /* _monster_cyborg_minor */
		BUILD_COLLECTION(_collection_cyborg, 0), /* shape collection */
		300, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_uses_sniper_ledges, /* flags */
		
		_class_cyborg, /* class */
		_class_cyborg, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/4, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/4, /* external velocity scale */
		_effect_cyborg_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast5, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 60, 0, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		5, UNONE, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE,
		},
		
		/* ranged attack */
		{
			_projectile_minor_cyborg_ball, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			10*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_cyborg_major */
		BUILD_COLLECTION(_collection_cyborg, 1), /* shape collection */
		450, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_uses_sniper_ledges, /* flags */
		
		_class_cyborg, /* class */
		_class_cyborg, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/4, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/4, /* external velocity scale */
		_effect_cyborg_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 60, 0, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		5, UNONE, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE,
		},
		
		/* ranged attack */
		{
			_projectile_minor_cyborg_ball, /* ranged attack type */
			1, /* repetitions */
			0, /* error angle */
			10*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_cyborg_flame_minor */
		BUILD_COLLECTION(_collection_cyborg, 0), /* shape collection */
		300, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_uses_sniper_ledges, /* flags */
		
		_class_cyborg, /* class */
		_class_cyborg, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/4, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/4, /* external velocity scale */
		_effect_cyborg_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 60, 0, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		5, UNONE, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			_projectile_flamethrower_burst, /* ranged attack type */
			15, /* repetitions */
			0, /* error angle */
			2*WORLD_ONE, /* range */
			4, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_major_cyborg_ball, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			10*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_cyborg_flame_major */
		BUILD_COLLECTION(_collection_cyborg, 0), /* shape collection */
		450, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_uses_sniper_ledges, /* flags */
		
		_class_cyborg, /* class */
		_class_cyborg, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/4, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/4, /* external velocity scale */
		_effect_cyborg_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 60, 0, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		5, UNONE, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			_projectile_flamethrower_burst, /* ranged attack type */
			15, /* repetitions */
			0, /* error angle */
			2*WORLD_ONE, /* range */
			4, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_major_cyborg_ball, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			10*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_enforcer_minor */
		BUILD_COLLECTION(_collection_enforcer, 0), /* shape collection */
		120, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_uses_sniper_ledges|_monster_can_die_in_flames|_monster_waits_with_clear_shot, /* flags */
		
		_class_enforcer, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_enforcer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		_i_alien_shotgun, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_enforcer_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		6, 3, /* dying hard (popping), dying soft (falling) */
		7, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_alien_weapon, /* ranged attack type */
			8, /* repetitions */
			2, /* error angle */
			15*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_enforcer_major */
		BUILD_COLLECTION(_collection_enforcer, 1), /* shape collection */
		160, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_uses_sniper_ledges|_monster_can_die_in_flames|_monster_waits_with_clear_shot, /* flags */
	
		_class_enforcer, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		_snd_enforcer_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		_i_alien_shotgun, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_enforcer_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		6, 3, /* dying hard (popping), dying soft (falling) */
		7, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_alien_weapon, /* ranged attack type */
			12, /* repetitions */
			5, /* error angle */
			20*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH/2, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_hunter_minor */
		BUILD_COLLECTION(_collection_hunter, 0), /* shape collection */
		200, FLAG(_damage_flame), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_uses_sniper_ledges|_monster_minor, /* flags */

		_class_hunter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE_HALF, /* external velocity scale */
		_effect_hunter_spark, _effect_metallic_clang, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 4*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast3, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		2*WORLD_ONE, {_damage_explosion, _alien_damage, 60, 30, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		3, 9, /* dying hard (popping), dying soft (falling) */
		6, 10, /* hard dead frames, soft dead frames */
		1, 0, /* stationary shape, moving shape (no permutations) */
		1, 1, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_hunter, /* ranged attack type */
			2, /* repetitions */
			3, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, WORLD_ONE/8, WORLD_ONE_HALF+WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_hunter_major */
		BUILD_COLLECTION(_collection_hunter, 1), /* shape collection */
		300, FLAG(_damage_flame), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_uses_sniper_ledges|_monster_major, /* flags */

		_class_hunter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE_HALF, /* external velocity scale */
		_effect_hunter_spark, _effect_metallic_clang, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 4*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast5, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		2*WORLD_ONE, {_damage_explosion, _alien_damage, 60, 30, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		3, 9, /* dying hard (popping), dying soft (falling) */
		6, 10, /* hard dead frames, soft dead frames */
		1, 0, /* stationary shape, moving shape (no permutations) */
		1, 1, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_hunter, /* ranged attack type */
			5, /* repetitions */
			3, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, WORLD_ONE/8, WORLD_ONE_HALF+WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},

	{ /* _monster_trooper_minor */
		BUILD_COLLECTION(_collection_trooper, 0), /* shape collection */
		110, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_minor|_monster_uses_sniper_ledges|_monster_is_berserker|_monster_can_die_in_flames, /* flags */
		
		_class_trooper, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_trooper_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast3, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		0, 7, /* hard dead frames, soft dead frames */
		1, 0, /* stationary shape, moving shape */
		1, 1, /* teleport in shape, teleport out shape */
		
		4*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_trooper_bullet, /* melee attack type */
			3, /* repetitions */
			30, /* error */
			3*WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			0, -WORLD_ONE/10, WORLD_ONE_HALF-WORLD_ONE_FOURTH/4, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_trooper_grenade, /* ranged attack type */
			0, /* repetitions */
			10, /* error angle */
			10*WORLD_ONE, /* range */
			9, /* ranged attack shape */
			
			-WORLD_ONE/10, WORLD_ONE/8, WORLD_ONE_HALF-WORLD_ONE_FOURTH/8, /* dx, dy, dz */
		}
	},

	{ /* _monster_trooper_major */
		BUILD_COLLECTION(_collection_trooper, 1), /* shape collection */
		200, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_major|_monster_uses_sniper_ledges|_monster_is_berserker|_monster_can_die_in_flames, /* flags */
		
		_class_trooper, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-4*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		(3*FIXED_ONE)/4, /* external velocity scale */
		_effect_trooper_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast3, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_fast_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		0, 7, /* hard dead frames, soft dead frames */
		1, 0, /* stationary shape, moving shape */
		1, 1, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_trooper_bullet, /* melee attack type */
			8, /* repetitions */
			10, /* error */
			3*WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			-WORLD_ONE/10, WORLD_ONE/8, WORLD_ONE_HALF-WORLD_ONE_FOURTH/8, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_trooper_grenade, /* ranged attack type */
			1, /* repetitions */
			5, /* error angle */
			12*WORLD_ONE, /* range */
			9, /* ranged attack shape */
			
			0, -WORLD_ONE/10, WORLD_ONE_HALF-WORLD_ONE_FOURTH/4, /* dx, dy, dz */
		}
	},

	{ /* _monster_mother_of_all_cyborgs */
		BUILD_COLLECTION(_collection_cyborg, 0), /* shape collection */
		1500, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_enlarged|_monster_is_alien|_monster_cannot_be_dropped|_monster_uses_sniper_ledges, /* flags */
		
		_class_cyborg, /* class */
		0, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/3, WORLD_ONE + WORLD_ONE/5, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/4, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/4, /* external velocity scale */
		_effect_cyborg_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast4, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		3*WORLD_ONE, {_damage_explosion, _alien_damage, 140, 40, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		0, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		5, UNONE, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		0, 0, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			_projectile_flamethrower_burst, /* ranged attack type */
			15, /* repetitions */
			0, /* error angle */
			2*WORLD_ONE, /* range */
			4, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_major_cyborg_ball, /* ranged attack type */
			0, /* repetitions */
			0, /* error angle */
			10*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/16, 0, WORLD_ONE_HALF+WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},
	
	{ /* _monster_mother_of_all_hunters */
		BUILD_COLLECTION(_collection_hunter, 2), /* shape collection */
		1500, FLAG(_damage_flame), FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_is_enlarged|_monster_uses_sniper_ledges|_monster_cannot_be_dropped, /* flags */

		_class_hunter, /* class */
		_class_pfhor, /* friends */
		_class_human|_class_native|_class_defender, /* enemies */
	
		_lower_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming death sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE+WORLD_ONE/6, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE_HALF, /* external velocity scale */
		_effect_hunter_spark, _effect_metallic_clang, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 4*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast1, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		4*WORLD_ONE, {_damage_explosion, _alien_damage, 140, 50, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		7, /* being hit */
		3, UNONE, /* dying hard (popping), dying soft (falling) */
		6, 8, /* hard dead frames, soft dead frames */
		1, 0, /* stationary shape, moving shape (no permutations) */
		1, 1, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_hunter, /* ranged attack type */
			5, /* repetitions */
			3, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, WORLD_ONE/8, WORLD_ONE_HALF+WORLD_ONE_FOURTH, /* dx, dy, dz */
		}
	},

	{ /* _monster_sewage_yeti */
		BUILD_COLLECTION(_collection_yeti, 0), /* shape collection */
		100, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_not_afraid_of_sewage|_monster_is_alien|_monster_is_berserker, /* flags */
		
		_class_yeti, /* class */
		_class_yeti, /* friends */
		_class_pfhor|_class_human|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* dying flaming */
		NONE, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE-1, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		3*FIXED_ONE/4, /* external velocity scale */
		_effect_sewage_yeti_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_superfast5, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_slow_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		12, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		UNONE, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_yeti, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			13, /* melee attack shape */

			0, 0, 4*WORLD_ONE/5, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_sewage_yeti, /* ranged attack type */
			0, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/3, WORLD_ONE/6, 4*WORLD_ONE/5, /* dx, dy, dz */
		}
	},

	{ /* _monster_water_yeti */
		BUILD_COLLECTION(_collection_yeti, 1), /* shape collection */
		250, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_not_afraid_of_water|_monster_is_alien|_monster_is_berserker, /* flags */
		
		_class_yeti, /* class */
		_class_yeti, /* friends */
		_class_pfhor|_class_human|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* dying flaming */
		NONE, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE-1, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		3*FIXED_ONE/4, /* external velocity scale */
		_effect_water_yeti_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_superfast5, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_slow_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		12, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		UNONE, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		TICKS_PER_SECOND/2, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_yeti, /* melee attack type */
			1, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			13, /* melee attack shape */

			0, WORLD_ONE/6, 4*WORLD_ONE/5, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			NONE
		}
	},

	{ /* _monster_lava_yeti */
		BUILD_COLLECTION(_collection_yeti, 2), /* shape collection */
		200, FLAG(_damage_flame)|FLAG(_damage_alien_projectile)|FLAG(_damage_fusion_bolt)|FLAG(_damage_lava), 0, /* vitality, immunities, weaknesses */
		_monster_is_not_afraid_of_lava|_monster_is_alien|_monster_is_berserker, /* flags */
		
		_class_yeti, /* class */
		_class_yeti, /* friends */
		_class_pfhor|_class_human|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* dying flaming */
		NONE, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/4, WORLD_ONE-1, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		3*FIXED_ONE/4, /* external velocity scale */
		_effect_lava_yeti_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_slow_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		12, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		UNONE, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_yeti, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			13, /* melee attack shape */

			0, 0, 4*WORLD_ONE/5, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_lava_yeti, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/3, WORLD_ONE/6, 4*WORLD_ONE/5, /* dx, dy, dz */
		}
	},

	{ /* _monster_defender_minor */
		BUILD_COLLECTION(_collection_defender, 0), /* shape collection */
		160, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_flys|_monster_waits_with_clear_shot, /* flags */

		_class_defender, /* class */
		_class_defender, /* friends */
		_class_pfhor|_class_client|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		WORLD_ONE/4, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		3, /* being hit */
		UNONE, 6, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape */
		8, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_minor_defender, /* ranged attack type */
			2, /* repetitions */
			NUMBER_OF_ANGLES/200, /* error angle */
			20*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/8, -WORLD_ONE/4+WORLD_ONE/10, WORLD_ONE_HALF, /* dx, dy, dz */
		}
	},

	{ /* _monster_defender_major */
		BUILD_COLLECTION(_collection_defender, 1), /* shape collection */
		240, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_flys|_monster_waits_with_clear_shot, /* flags */

		_class_defender, /* class */
		_class_defender, /* friends */
		_class_pfhor|_class_client|_class_native, /* enemies */
	
		_higher_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, WORLD_ONE, /* radius, height */
		WORLD_ONE/4, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		NONE, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		3, /* being hit */
		UNONE, 6, /* dying hard (popping), dying soft (falling) */
		UNONE, UNONE, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape */
		8, 8, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_major_defender, /* ranged attack type */
			4, /* repetitions */
			NUMBER_OF_ANGLES/100, /* error angle */
			20*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			WORLD_ONE/8, -WORLD_ONE/4+WORLD_ONE/10, WORLD_ONE_HALF, /* dx, dy, dz */
		}
	},

	{ /* _monster_juggernaut_minor */
		BUILD_COLLECTION(_collection_juggernaut, 0), /* shape collection */
		2500, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_minor|_monster_is_alien|_monster_cant_fire_backwards|_monster_has_nuclear_hard_death|
			_monster_has_delayed_hard_death|_monster_cannot_be_dropped|_monster_fires_symmetrically|
			_monster_chooses_weapons_randomly|_monster_flys, /* flags */

		_class_juggernaut, /* class */
		_class_juggernaut, /* friends */
		_class_human|_class_client|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE, 2*WORLD_ONE, /* radius, height */
		WORLD_ONE, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		_effect_juggernaut_spark, _effect_metallic_clang, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY/4, NORMAL_MONSTER_TERMINAL_VELOCITY/4, /* gravity, terminal velocity */
		NONE, /* door retry mask */
		5*WORLD_ONE, {_damage_explosion, _alien_damage, 350, 50, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		UNONE, /* being hit */
		6, 5, /* dying hard (popping), dying soft (falling) */
		8, 8, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape */
		7, 7, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			_projectile_alien_weapon, /* melee attack type */
			10, /* repetitions */
			5, /* error */
			15*WORLD_ONE, /* range */
			1, /* melee attack shape */

			WORLD_ONE/4, WORLD_ONE_HALF+WORLD_ONE/8, WORLD_ONE-WORLD_ONE/4-WORLD_ONE/16, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_juggernaut_missile, /* ranged attack type */
			0, /* repetitions */
			40, /* error angle */
			25*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, WORLD_ONE_HALF, WORLD_ONE+WORLD_ONE_HALF, /* dx, dy, dz */
		}
	},

	{ /* _monster_juggernaut_major */
		BUILD_COLLECTION(_collection_juggernaut, 1), /* shape collection */
		5000, 0, FLAG(_damage_fusion_bolt), /* vitality, immunities, weaknesses */
		_monster_major|_monster_is_alien|_monster_cant_fire_backwards|_monster_has_nuclear_hard_death|
			_monster_has_delayed_hard_death|_monster_cannot_be_dropped|_monster_fires_symmetrically|
			_monster_chooses_weapons_randomly|_monster_flys, /* flags */

		_class_juggernaut, /* class */
		_class_juggernaut, /* friends */
		_class_human|_class_client|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* flaming dying sound */
		NONE, 0, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE, 2*WORLD_ONE, /* radius, height */
		WORLD_ONE, /* preferred hover height */
		INT16_MIN, INT16_MAX, /* minimum ledge delta, maximum ledge delta */
		0, /* external velocity scale */
		_effect_juggernaut_spark, _effect_metallic_clang, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY/4, NORMAL_MONSTER_TERMINAL_VELOCITY/4, /* gravity, terminal velocity */
		NONE, /* door retry mask */
		5*WORLD_ONE, {_damage_explosion, _alien_damage, 350, 50, FIXED_ONE}, /* shrapnel radius, shrapnel damage */
		
		UNONE, /* being hit */
		6, 5, /* dying hard (popping), dying soft (falling) */
		8, 8, /* hard dead frames, soft dead frames */
		0, 0, /* stationary shape, moving shape */
		7, 7, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency */
		
		/* melee attack */
		{
			_projectile_alien_weapon, /* melee attack type */
			20, /* repetitions */
			5, /* error */
			15*WORLD_ONE, /* range */
			1, /* melee attack shape */

			WORLD_ONE/4, WORLD_ONE_HALF+WORLD_ONE/8, WORLD_ONE-WORLD_ONE/4-WORLD_ONE/16, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_juggernaut_missile, /* ranged attack type */
			1, /* repetitions */
			40, /* error angle */
			25*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, WORLD_ONE_HALF, WORLD_ONE+WORLD_ONE_HALF, /* dx, dy, dz */
		}
	},

	{ /* _monster_tiny_fighter */
		BUILD_COLLECTION(_collection_fighter, 1), /* shape collection */
		40, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_tiny|_monster_is_berserker|_monster_can_die_in_flames, /* flags */
	
		_class_fighter, /* class */
		_class_pfhor, /* friends */
		(_class_human&~_class_player)|_class_native|_class_defender, /* enemies */
	
		FIXED_ONE+FIXED_ONE_HALF, /* sound pitch */	
		_snd_fighter_activate, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_fighter_wail, /* dying flaming */
		_snd_fighter_chatter, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/12, (4*WORLD_ONE)/12, /* radius, height */
		0, /* preferred hover height */
		-8*WORLD_ONE, WORLD_ONE/6, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/2, /* external velocity scale */
		_effect_fighter_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, 3*WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_fast, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_normal_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		4, /* being hit */
		1, 3, /* dying hard (popping), dying soft (falling) */
		6, 5, /* hard dead frames, soft dead frames */
		7, 0, /* stationary shape, moving shape */
		12, 12, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_staff, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			
			2, /* melee attack shape */

			0, 0, WORLD_ONE/5, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},

	{ /* _monster_tiny_bob */
		BUILD_COLLECTION(_collection_civilian, 0), /* shape collection */
		10, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges|_monster_is_tiny, /* flags */

		_class_human_civilian, /* class */	
		_class_human, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		FIXED_ONE+FIXED_ONE_HALF, /* sound pitch */	
		_snd_human_activation, _snd_kill_the_player, _snd_human_clear, _snd_human_trash_talk, _snd_human_apology, _snd_human_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_human_wail, /* dying flaming */
		_snd_human_chatter, 0x1f, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/12, (4*WORLD_ONE)/12, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/6, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/2, /* external velocity scale */
		_effect_civilian_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_superfast2, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_pistol_bullet, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			10*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE/5, /* dx, dy, dz */
		}
	},

	{ /* _monster_tiny_yeti */
		BUILD_COLLECTION(_collection_yeti, 2), /* shape collection */
		100, FLAG(_damage_flame)|FLAG(_damage_alien_projectile)|FLAG(_damage_fusion_bolt)|FLAG(_damage_lava), 0, /* vitality, immunities, weaknesses */
		_monster_is_not_afraid_of_lava|_monster_is_berserker|_monster_is_tiny, /* flags */
		
		_class_yeti, /* class */
		_class_yeti, /* friends */
		(_class_human&~_class_player)|_class_pfhor, /* enemies */
	
		FIXED_ONE+FIXED_ONE_HALF, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, NONE, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		NONE, /* dying flaming */
		NONE, 15, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/12, (4*WORLD_ONE)/12, /* radius, height */
		0, /* preferred hover height */
		-WORLD_ONE, WORLD_ONE/6, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE/2, /* external velocity scale */
		_effect_lava_yeti_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_low, /* intelligence */
		_speed_superfast2, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_slow_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		12, /* being hit */
		UNONE, 3, /* dying hard (popping), dying soft (falling) */
		UNONE, 4, /* hard dead frames, soft dead frames */
		0, 1, /* stationary shape, moving shape */
		UNONE, UNONE, /* teleport in shape, teleport out shape */
		
		TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			_projectile_yeti, /* melee attack type */
			0, /* repetitions */
			0, /* error */
			WORLD_ONE, /* range */
			13, /* melee attack shape */

			0, 0, WORLD_ONE/5, /* dx, dy, dz */
		},
		
		/* ranged attack */
		{
			_projectile_lava_yeti, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			12*WORLD_ONE, /* range */
			2, /* ranged attack shape */
			
			0, 0, WORLD_ONE/5, /* dx, dy, dz */
		}
	},
	
	// LP addition: the VacBobs:
	// they drop either fusion batteries or fusion guns as appropriate,
	// they shoot "minor" fusion bolts (those that don't flip switches)

	{ /* _civilian_fusion_crew "bob" */
		BUILD_COLLECTION(_collection_civilian_fusion, 0), /* shape collection */
		20, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_civilian_fusion_activation, _snd_civilian_fusion_kill_the_player, _snd_civilian_fusion_clear, _snd_civilian_fusion_trash_talk, _snd_civilian_fusion_apology, _snd_civilian_fusion_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_civilian_fusion_wail, /* dying flaming */
		_snd_civilian_fusion_chatter, 0x1f, /* random sound, random sound mask */

		_i_plasma_magazine, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_fusion_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_fusion_bolt_minor, /* ranged attack type */
			1, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			10*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_fusion_science "fred" */
		BUILD_COLLECTION(_collection_civilian_fusion, 1), /* shape collection */
		25, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human|_class_assimilated_civilian, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_civilian_fusion_activation, _snd_civilian_fusion_kill_the_player, _snd_civilian_fusion_clear, _snd_civilian_fusion_trash_talk, _snd_civilian_fusion_apology, _snd_civilian_fusion_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_civilian_fusion_wail, /* dying flaming */
		_snd_civilian_fusion_chatter, 0x1f, /* random sound, random sound mask */

		_i_plasma_magazine, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_fusion_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		3*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_fusion_bolt_minor, /* ranged attack type */
			2, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			13*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_fusion_security "steve" */
		BUILD_COLLECTION(_collection_civilian_fusion, 2), /* shape collection */
		30, 0, 0, /* vitality, immunities, weaknesses */
		_monster_attacks_immediately|_monster_is_omniscent|_monster_cannot_be_dropped|_monster_waits_with_clear_shot|_monster_can_die_in_flames|_monster_uses_sniper_ledges, /* flags */

		_class_human_civilian, /* class */	
		_class_human|_class_assimilated_civilian, /* friends */
		(_class_hostile_alien^_class_assimilated_civilian)|_class_native, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		_snd_civilian_fusion_activation, _snd_civilian_fusion_kill_the_player, _snd_civilian_fusion_clear, _snd_civilian_fusion_trash_talk, _snd_civilian_fusion_apology, _snd_civilian_fusion_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_civilian_fusion_wail, /* dying flaming */
		_snd_civilian_fusion_chatter, 0x1f, /* random sound, random sound mask */

		_i_plasma_pistol, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_civilian_fusion_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		30*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		NONE, {NONE, 0, 0, 0}, /* shrapnel radius, shrapnel damage */
		
		10, /* being hit */
		2, 1, /* dying hard (popping), dying soft (falling) */
		4, 3, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		9, 8, /* teleport in shape, teleport out shape */
		
		TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			_projectile_fusion_bolt_minor, /* ranged attack type */
			5, /* repetitions */
			NUMBER_OF_ANGLES/150, /* error angle */
			17*WORLD_ONE, /* range */
			5, /* ranged attack shape */
			
			0, 0, WORLD_ONE*3/4, /* dx, dy, dz */
		}
	},

	{ /* _civilian_fusion_assimilated "evil bob" */
		BUILD_COLLECTION(_collection_civilian_fusion, 3), /* shape collection */
		30, 0, 0, /* vitality, immunities, weaknesses */
		_monster_is_alien|_monster_is_kamakazi|_monster_can_die_in_flames, /* flags */
		
		_class_assimilated_civilian,
		_class_pfhor, /* friends */
		_class_player|_class_defender, /* enemies */
	
		_normal_frequency, /* sound pitch */	
		NONE, NONE, NONE, NONE, NONE, _snd_civilian_fusion_stop_shooting_me_you_bastard, /* sounds: activation, friendly activation, clear, kill, apology, friendly-fire */
		_snd_civilian_fusion_wail, /* dying flaming */
		_snd_assimilated_civilian_fusion_chatter, 0xf, /* random sound, random sound mask */

		NONE, /* carrying item type */
	
		WORLD_ONE/5, (4*WORLD_ONE)/5, /* radius, height */
		0, /* preferred hover height */
		-2*WORLD_ONE, WORLD_ONE/3, /* minimum ledge delta, maximum ledge delta */
		FIXED_ONE, /* external velocity scale */
		_effect_assimilated_civilian_fusion_blood_splash, NONE, NONE, /* impact effect, melee impact effect, contrail effect */
	
		QUARTER_CIRCLE, QUARTER_CIRCLE/3, /* half visual arc, half vertical visual arc */
		15*WORLD_ONE, WORLD_ONE, /* visual range, dark visual range */
		_intelligence_high, /* intelligence */
		_speed_blinding, /* speed */
		NORMAL_MONSTER_GRAVITY, NORMAL_MONSTER_TERMINAL_VELOCITY, /* gravity, terminal velocity */
		_vidmaster_door_retry_mask, /* door retry mask */
		WORLD_ONE, {_damage_explosion, _alien_damage, 80, 40, FIXED_ONE}, /* shrapnel radius, shrapnel damage  */
		
		10, /* being hit */
		11, UNONE, /* dying hard (popping), dying soft (falling) */
		4, 0, /* hard dead frames, soft dead frames */
		6, 0, /* stationary shape, moving shape */
		8, UNONE, /* teleport in shape, teleport out shape */
		
		2*TICKS_PER_SECOND, /* attack frequency (for both melee and ranged attacks) */
		
		/* melee attack */
		{
			NONE, /* melee attack type */
		},
		
		/* ranged attack */
		{
			NONE, /* ranged attack type */
		}
	},
};
