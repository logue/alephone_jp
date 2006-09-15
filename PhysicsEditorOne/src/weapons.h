#ifndef __WEAPONS_H
#define __WEAPONS_H
#include "stdafx.h"
#include "world.h"

/*
	weapons2.h

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

	Saturday, May 13, 1995 4:41:42 PM- rdm created.

Feb 4, 2000 (Loren Petrich):
	Added SMG stuff

Feb 6, 2000 (Loren Petrich):
	Added access to size of weapon-definition structure and to the number of weapon types

May 26, 2000 (Loren Petrich):
	Added XML support for configuring various weapon features

Aug 31, 2000 (Loren Petrich):
	Added stuff for unpacking and packing
*/




/* enums for player.c */
enum { /* Weapons */
	_weapon_fist,
	_weapon_pistol,
	_weapon_plasma_pistol,
	_weapon_assault_rifle,
	_weapon_missile_launcher,
	_weapon_flamethrower,
	_weapon_alien_shotgun,
	_weapon_shotgun,
	_weapon_ball, // or something
	// LP addition:
	_weapon_smg,
	MAXIMUM_NUMBER_OF_WEAPONS,
	
	_weapon_doublefisted_pistols= MAXIMUM_NUMBER_OF_WEAPONS, /* This is a pseudo-weapon */
	_weapon_doublefisted_shotguns,
	PLAYER_TORSO_SHAPE_COUNT
};

enum {
	_shape_weapon_idle,
	_shape_weapon_charging,
	_shape_weapon_firing,
        PLAYER_TORSO_WEAPON_ACTION_COUNT	// ZZZ: added this one
};

enum {
	_primary_weapon,
	_secondary_weapon,
	NUMBER_OF_TRIGGERS
};

enum /* weapon display positioning modes */
{
	_position_low, /* position==0 is invisible, position==FIXED_ONE is sticking out from left/bottom */
	_position_center, /* position==0 is off left/bottom, position==FIXED_ONE is off top/right */
	_position_high /* position==0 is invisible, position==FIXED_ONE is sticking out from right/top
		(mirrored, whether you like it or not) */
};

/* ----------------- structures */

struct weapon_display_information
{
	// Has sequence info for 3D-model weapon display
	short collection, shape_index, low_level_shape_index;
	
	_fixed vertical_position, horizontal_position;
	short vertical_positioning_mode, horizontal_positioning_mode;
	short transfer_mode;
	_fixed transfer_phase;
	
	bool flip_horizontal, flip_vertical;
	
	// Needed for animated models: which frame in an individual sequence (0, 1, 2, ...)
	short Frame, NextFrame;
	
	// Needed for animated models: which tick in a frame, and total ticks per frame
	short Phase, Ticks;
};

// SB: This needs to be accessed in lua_script.cpp

enum
{
	MAXIMUM_SHELL_CASINGS= 4
};

struct trigger_data {
    short state, phase;
    short rounds_loaded;
    short shots_fired, shots_hit;
    short ticks_since_last_shot; /* used to play shell casing sound, and to calculate arc for shell casing drawing... */
    short ticks_firing; /* How long have we been firing? (only valid for automatics) */
    uint16 sequence; /* what step of the animation are we in? (NOT guaranteed to be in sync!) */
};

struct weapon_data {
	short weapon_type; /* stored here to make life easier.. */
	uint16 flags;
	uint16 unused; /* non zero-> weapon is powered up */
	struct trigger_data triggers[NUMBER_OF_TRIGGERS];
};

struct shell_casing_data
{
	short type;
	short frame;
  
	uint16 flags;
  
	_fixed x, y;
	_fixed vx, vy;
};

struct player_weapon_data {
	short current_weapon;
	short desired_weapon;
	struct weapon_data weapons[MAXIMUM_NUMBER_OF_WEAPONS];
	struct shell_casing_data shell_casings[MAXIMUM_SHELL_CASINGS];
};

struct trigger_definition {
	int16 rounds_per_magazine;
	int16 ammunition_type;
	int16 ticks_per_round;
	int16 recovery_ticks;
	int16 charging_ticks;
	world_distance recoil_magnitude;
	int16 firing_sound;
	int16 click_sound;
	int16 charging_sound;
	int16 shell_casing_sound;
	int16 reloading_sound;
	int16 charged_sound;
	int16 projectile_type;
	int16 theta_error;
	int16 dx, dz;
	int16 shell_casing_type;
	int16 burst_count;
};

struct weapon_definition {
	int16 item_type;
	int16 powerup_type;
	int16 weapon_class;
	int16 flags;

	_fixed firing_light_intensity;
	int16 firing_intensity_decay_ticks;

	/* weapon will come up to FIXED_ONE when fired; idle_height±bob_amplitude should be in
		the range [0,FIXED_ONE] */
	_fixed idle_height, bob_amplitude, kick_height, reload_height;
	_fixed idle_width, horizontal_amplitude;

	/* each weapon has three basic animations: idle, firing and reloading.  sounds and frames
		are pulled from the shape collection.  for automatic weapons the firing animation loops
		until the trigger is released or the gun is empty and the gun begins rising as soon as
		the trigger is depressed and is not lowered until the firing animation stops.  for single
		shot weapons the animation loops once; the weapon is raised and lowered as soon as the
		firing animation terminates */
	int16 collection;
	int16 idle_shape, firing_shape, reloading_shape;
	int16 unused;
	int16 charging_shape, charged_shape;

	/* How long does it take to ready the weapon? */
	/* load_rounds_tick is the point which you actually load them. */
	int16 ready_ticks, await_reload_ticks, loading_ticks, finish_loading_ticks, powerup_ticks;

	struct trigger_definition weapons_by_trigger[NUMBER_OF_TRIGGERS];
};

// For external access:
const int SIZEOF_weapon_definition = 134;

const int SIZEOF_player_weapon_data = 472;

/* ----------------- prototypes */

// LP: to pack and unpack this data;
// these do not make the definitions visible to the outside world

uint8 *unpack_player_weapon_data(uint8 *Stream, size_t Count);
uint8 *pack_player_weapon_data(uint8 *Stream, size_t Count);
uint8 *unpack_weapon_definition(uint8 *Stream, size_t Count);
uint8 *pack_weapon_definition(uint8 *Stream, size_t Count);

// LP additions: get number of weapon types;
size_t get_number_of_weapon_types();

// LP addition: XML-parser support
//XML_ElementParser *Weapons_GetParser();

#endif

