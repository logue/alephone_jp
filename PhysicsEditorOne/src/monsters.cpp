#include "stdafx.h"
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

/*#include "cseries.h"
#include "render.h"
#include "flood_map.h"
*/
#include "interface.h"
#include "map.h"
#include "effects.h"
#include "monsters.h"
#include "projectiles.h"
#include "player.h"
#include "mysound.h"
#include "fades.h"
#include "items.h"
#include "media.h"
#include "monster_definitions.h"

/*#include "platforms.h"
#include "scenery.h"
*/
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
