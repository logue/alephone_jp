#ifndef __MONSTER_DEFINITIONS_H
#define __MONSTER_DEFINITIONS_H
//#include "stdafx.h"
#include "header.h"

#include "monsters.h"

/*
MONSTER_DEFINITIONS.H

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

Monday, May 30, 1994 9:04:01 PM

Jan 30, 2000 (Loren Petrich):
	Changed "class" to "_class" to make data structures more C++-friendly

Feb 3, 2000 (Loren Petrich):
	Added VacBobs and their physics
	
Oct 26, 2000 (Mark Levin)
	Added some includes that this file depends on
*/

//New includes
#include "effects.h"
#include "projectiles.h"
#include "map.h"
#include "mysound.h"
#include "items.h"

/* ---------- macros */

#define TYPE_IS_NEUTRAL(definition,type) (!((definition->friends|definition->enemies)&monster_definitions[type]._class))
#define TYPE_IS_ENEMY(definition,type) (definition->enemies&monster_definitions[type]._class)
#define TYPE_IS_FRIEND(definition,type) (definition->friends&monster_definitions[type]._class)

/* ---------- constants */

enum /* monster classes */
{
	_class_player_bit,
	_class_human_civilian_bit,
	_class_madd_bit,
	_class_possessed_hummer_bit,
		
	_class_defender_bit,

	_class_fighter_bit,
	_class_trooper_bit,
	_class_hunter_bit,
	_class_enforcer_bit,
	_class_juggernaut_bit,
	_class_hummer_bit,
	
	_class_compiler_bit,
	_class_cyborg_bit,
	_class_assimilated_civilian_bit,

	_class_tick_bit,
	_class_yeti_bit,

	_class_player= 1<<_class_player_bit,
	_class_human_civilian= 1<<_class_human_civilian_bit,
	_class_madd= 1<<_class_madd_bit,
	_class_possessed_hummer= 1<<_class_possessed_hummer_bit,
	_class_human= _class_player|_class_human_civilian|_class_madd|_class_possessed_hummer,
	
	_class_defender= 1<<_class_defender_bit,

	_class_fighter= 1<<_class_fighter_bit,
	_class_trooper= 1<<_class_trooper_bit,
	_class_hunter= 1<<_class_hunter_bit,
	_class_enforcer= 1<<_class_enforcer_bit,
	_class_juggernaut= 1<<_class_juggernaut_bit,
	_class_pfhor= _class_fighter|_class_trooper|_class_hunter|_class_enforcer|_class_juggernaut,
	
	_class_compiler= 1<<_class_compiler_bit,
	_class_cyborg= 1<<_class_cyborg_bit,
	_class_assimilated_civilian= 1<<_class_assimilated_civilian_bit,
	_class_hummer= 1<<_class_hummer_bit,
	_class_client= _class_compiler|_class_assimilated_civilian|_class_cyborg|_class_hummer,
	
	_class_tick= 1<<_class_tick_bit,
	_class_yeti= 1<<_class_yeti_bit,
	_class_native= _class_tick|_class_yeti,

	_class_hostile_alien= _class_pfhor|_class_client,
	_class_neutral_alien= _class_native
};

enum /* intelligence: maximum polygon switches before losing lock */
{
	_intelligence_low= 2,
	_intelligence_average= 3,
	_intelligence_high= 8
};

enum /* door retry masks */
{
	_slow_door_retry_mask= 63,
	_normal_door_retry_mask= 31,
	_fast_door_retry_mask= 15,
	_vidmaster_door_retry_mask= 3
};

enum /* flags */
{
	_monster_is_omniscent= 0x1, /* ignores line-of-sight during find_closest_appropriate_target() */
	_monster_flys= 0x2,
	_monster_is_alien= 0x4, /* moves slower on slower levels, etc. */
	_monster_major= 0x8, /* type -1 is minor */
	_monster_minor= 0x10, /* type +1 is major */
	_monster_cannot_be_dropped= 0x20, /* low levels cannot skip this monster */
	_monster_floats= 0x40, /* exclusive from flys; forces the monster to take +¶h gradually */
	_monster_cannot_attack= 0x80, /* monster has no weapons and cannot attack (runs constantly to safety) */
	_monster_uses_sniper_ledges= 0x100, /* sit on ledges and hurl shit at the player (ranged attack monsters only) */
	_monster_is_invisible= 0x200, /* this monster uses _xfer_invisibility */
	_monster_is_subtly_invisible= 0x400, /* this monster uses _xfer_subtle_invisibility */
	_monster_is_kamakazi= 0x800, /* monster does shrapnel damage and will suicide if close enough to target */
	_monster_is_berserker= 0x1000, /* below 1/4 vitality this monster goes berserk */
	_monster_is_enlarged= 0x2000, /* monster is 1.25 times normal height */
	_monster_has_delayed_hard_death= 0x4000, /* always dies soft, then switches to hard */
	_monster_fires_symmetrically= 0x8000, /* fires at ±dy, simultaneously */
	_monster_has_nuclear_hard_death= 0x10000, /* playerÕs screen whites out and slowly recovers */
	_monster_cant_fire_backwards= 0x20000, /* monster canÕt turn more than 135¡ to fire */
	_monster_can_die_in_flames= 0x40000, /* uses humanoid flaming body shape */
	_monster_waits_with_clear_shot= 0x80000, /* will sit and fire (slowly) if we have a clear shot */
	_monster_is_tiny= 0x100000, /* 0.25-size normal height */
	_monster_attacks_immediately= 0x200000, /* monster will try an attack immediately */
	_monster_is_not_afraid_of_water= 0x400000,
	_monster_is_not_afraid_of_sewage= 0x800000,
	_monster_is_not_afraid_of_lava= 0x1000000,
	_monster_is_not_afraid_of_goo= 0x2000000,
	_monster_can_teleport_under_media= 0x4000000,
	_monster_chooses_weapons_randomly= 0x8000000
	/* monsters unable to open doors have door retry masks of NONE */
	/* monsters unable to switch levels have min,max ledge deltas of 0 */
	/* monsters unstopped by bullets have hit frames of NONE */
};

enum /* monster speeds (world_distance per tick); also used for projectiles */
{
	_speed_slow= WORLD_ONE/120,
	_speed_medium= WORLD_ONE/80,
	_speed_almost_fast= WORLD_ONE/70,
	_speed_fast= WORLD_ONE/40,
	_speed_superfast1= WORLD_ONE/30,
	_speed_superfast2= WORLD_ONE/28,
	_speed_superfast3= WORLD_ONE/26,
	_speed_superfast4= WORLD_ONE/24,
	_speed_superfast5= WORLD_ONE/22,
	_speed_blinding= WORLD_ONE/20,
	_speed_insane= WORLD_ONE/10
};

#define NORMAL_MONSTER_GRAVITY (WORLD_ONE/120)
#define NORMAL_MONSTER_TERMINAL_VELOCITY (WORLD_ONE/14)

/* ---------- monster definition structures */

struct attack_definition
{
	int16 type;
	int16 repetitions;
	angle error; /* ±error is added to the firing angle */
	world_distance range; /* beyond which we cannot attack */
	int16 attack_shape; /* attack occurs when keyframe is displayed */
	
	world_distance dx, dy, dz; /* +dy is right, +dx is out, +dz is up */
};

struct monster_definition /* <128 bytes */
{
	int16 collection;
	
	int16 vitality;
	uint32 immunities, weaknesses;
	uint32 flags;

	int32 _class; /* our class */
	int32 friends, enemies; /* bit fields of what classes we consider friendly and what types we donÕt like */

	_fixed sound_pitch;
	int16 activation_sound, friendly_activation_sound, clear_sound;
	int16 kill_sound, apology_sound, friendly_fire_sound;
	int16 flaming_sound; /* the scream we play when we go down in flames */
	int16 random_sound, random_sound_mask; /* if moving and locked play this sound if we get time and our mask comes up */

	int16 carrying_item_type; /* an item type we might drop if we donÕt explode */

	world_distance radius, height;
	world_distance preferred_hover_height;
	world_distance minimum_ledge_delta, maximum_ledge_delta;
	_fixed external_velocity_scale;
	int16 impact_effect, melee_impact_effect, contrail_effect;

	int16 half_visual_arc, half_vertical_visual_arc;
	world_distance visual_range, dark_visual_range;
	int16 intelligence;
	int16 speed, gravity, terminal_velocity;
	int16 door_retry_mask;
	int16 shrapnel_radius; /* no shrapnel if NONE */
	struct damage_definition shrapnel_damage;

	shape_descriptor hit_shapes;
	shape_descriptor hard_dying_shape, soft_dying_shape; /* minus dead frame */
	shape_descriptor hard_dead_shapes, soft_dead_shapes; /* NONE for vanishing */
	shape_descriptor stationary_shape, moving_shape;
	shape_descriptor teleport_in_shape, teleport_out_shape;
	
	/* which type of attack the monster actually uses is determined at attack time; typically
		melee attacks will occur twice as often as ranged attacks because the monster will be
		stopped (and stationary monsters attack twice as often as moving ones) */
	int16 attack_frequency;
	struct attack_definition melee_attack;
	struct attack_definition ranged_attack;
};

// So as not to repeat in script_instructions.cpp (Pfhortran)
//#ifndef DONT_REPEAT_DEFINITIONS

/* ---------- monster definitions */

extern struct monster_definition monster_definitions[NUMBER_OF_MONSTER_TYPES];

// Added for the convenience of the 1-2-3 Converter
uint8 *unpack_monster_definition(uint8 *Stream, monster_definition *Objects, size_t Count);
uint8 *pack_monster_definition(uint8 *Stream, monster_definition *Objects, size_t Count);

//#endif

#endif

