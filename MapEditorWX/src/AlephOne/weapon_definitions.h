#ifndef __WEAPON_DEFINITIONS_H
#define __WEAPON_DEFINITIONS_H
//#include "stdafx.h"
#include "map.h"
#include "items.h"
#include "mysound.h"
#include "weapons.h"

/*
	WEAPON_DEFINITIONS2.H

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

	Saturday, May 13, 1995 8:28:14 PM

	Sunday, May 14, 1995 3:11:52 AM- converted the piece of shit...

4 Feb 2000 (Loren Petrich):
	Added SMG stuff
*/

#include "weapons.h"

/* TEMPORARY!!! */
enum {
	_projectile_ball_dropped= 1000
};

/* ---------- constants */
#define NORMAL_WEAPON_DZ (20)

/* This is the amount of ammo that charging weapons use at one time.. */
#define CHARGING_WEAPON_AMMO_COUNT 4

enum /* weapon classes */
{
	_melee_class, /* normal weapon, no ammunition, both triggers do the same thing */
	_normal_class, /* normal weapon, one ammunition type, both triggers do the same thing */
	_dual_function_class, /* normal weapon, one ammunition type, trigger does something different */
	_twofisted_pistol_class, /* two can be held at once (differnet triggers), same ammunition */
	_multipurpose_class /* two weapons in one (assault rifle, grenade launcher), two different
		ammunition types with two separate triggers; secondary ammunition is discrete (i.e., it
		is never loaded explicitly but appears in the weapon) */
};

enum /* weapon flags */
{
	_no_flags= 0x0,
	_weapon_is_automatic= 0x01,
	_weapon_disappears_after_use= 0x02,
	_weapon_plays_instant_shell_casing_sound= 0x04,
	_weapon_overloads= 0x08,
	_weapon_has_random_ammo_on_pickup= 0x10,
	_powerup_is_temporary= 0x20,
	_weapon_reloads_in_one_hand= 0x40,
	_weapon_fires_out_of_phase= 0x80,
	_weapon_fires_under_media= 0x100,
	_weapon_triggers_share_ammo= 0x200,
	_weapon_secondary_has_angular_flipping= 0x400
};

enum {
	_weapon_in_hand_collection= 1,
	_fist_idle= 0,
	_fist_punching,
	_pistol_idle,
	_pistol_firing,
	_pistol_reloading,
	_shotgun_idle,
	_shotgun_firing,
	_shotgun_reloading,
	_assault_rifle_idle,
	_assault_rifle_firing,
	_assault_rifle_reloading,
	_fusion_idle,
	_fusion_firing,
	_missile_launcher_idle,
	_missile_launcher_firing,
	_flamethrower_idle,
	_flamethrower_transit,
	_flamethrower_firing,
	_assault_rifle_shell_casing,
	_pistol_shell_casing,
	_fusion_charged,
	_alien_weapon_idle,
	_alien_weapon_firing,
	// LP additions:
	_smg_idle,
	_smg_firing,
	_smg_reloading,
	_smg_shell_casing
};

/* ---------- shell casings */

enum // shell casing types
{
	_shell_casing_assault_rifle,
	_shell_casing_pistol,
	_shell_casing_pistol_left,
	_shell_casing_pistol_right,
	// LP additions:
	_shell_casing_smg,
	
	NUMBER_OF_SHELL_CASING_TYPES
};

struct shell_casing_definition
{
	int16 collection, shape;
	
	_fixed x0, y0;
	_fixed vx0, vy0;
	_fixed dvx, dvy;
};

extern struct shell_casing_definition shell_casing_definitions[NUMBER_OF_SHELL_CASING_TYPES];

extern struct weapon_definition weapon_definitions[MAXIMUM_NUMBER_OF_WEAPONS];
#define NUMBER_OF_WEAPONS static_cast<int>(sizeof(weapon_definitions)/sizeof(struct weapon_definition))

// Added for the convenience of the 1-2-3 Converter
uint8 *unpack_weapon_definition(uint8 *Stream, weapon_definition *Objects, size_t Count);
uint8 *pack_weapon_definition(uint8 *Stream, weapon_definition *Objects, size_t Count);

#endif
