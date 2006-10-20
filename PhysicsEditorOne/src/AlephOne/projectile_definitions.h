#ifndef __PROJECTILE_DEFINITIONS_H
#define __PROJECTILE_DEFINITIONS_H
#include "stdafx.h"

#include "map.h"
#include "effects.h"
#include "media.h"
#include "projectiles.h"

/*
PROJECTILE_DEFINITIONS.H

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

Tuesday, May 31, 1994 5:19:56 PM

Feb 4, 2000 (Loren Petrich):
	Added SMG bullet and its ability to enter/exit liquids
*/

/* ---------- constants */

enum /* projectile flags */
{
	_guided= 0x0001,
	_stop_when_animation_loops= 0x0002,
	_persistent= 0x0004, /* does stops doing damage and stops moving against a target, but doesn't vanish */
	_alien_projectile= 0x0008, /* does less damage and moves slower on lower levels */
	_affected_by_gravity= 0x0010,
	_no_horizontal_error= 0x0020,
	_no_vertical_error= 0x0040,
	_can_toggle_control_panels= 0x0080,
	_positive_vertical_error= 0x0100,
	_melee_projectile= 0x0200, /* can use a monster’s custom melee detonation */
	_persistent_and_virulent= 0x0400, /* keeps moving and doing damage after a successful hit */
	_usually_pass_transparent_side= 0x0800,
	_sometimes_pass_transparent_side= 0x1000,
	_doubly_affected_by_gravity= 0x2000,
	_rebounds_from_floor= 0x4000, /* unless v.z<kvzMIN */
	_penetrates_media= 0x8000, /* huh uh huh ... i said penetrate */
	_becomes_item_on_detonation= 0x10000, /* item type in .permutation field of projectile */
	_bleeding_projectile= 0x20000, /* can use a monster’s custom bleeding detonation */
	_horizontal_wander= 0x40000, /* random horizontal error perpendicular to direction of movement */
	_vertical_wander= 0x80000, /* random vertical movement perpendicular to direction of movement */
	_affected_by_half_gravity= 0x100000,
	_penetrates_media_boundary=0x200000 // Can enter/exit liquids
};

/* ---------- structures */

struct projectile_definition
{
	int16 collection, shape; /* collection can be NONE (invisible) */
	int16 detonation_effect, media_detonation_effect;
	int16 contrail_effect, ticks_between_contrails, maximum_contrails; /* maximum of NONE is infinite */
	int16 media_projectile_promotion;

	world_distance radius; /* can be zero and will still hit */
	world_distance area_of_effect; /* one target if ==0 */
	struct damage_definition damage;

	uint32 flags;

	world_distance speed;
	world_distance maximum_range;

	_fixed sound_pitch;	
	int16 flyby_sound, rebound_sound;
};

#ifndef DONT_REPEAT_DEFINITIONS

/* ---------- projectile definitions */

extern struct projectile_definition projectile_definitions[NUMBER_OF_PROJECTILE_TYPES];

// Added for the convenience of the 1-2-3 Converter
uint8 *unpack_projectile_definition(uint8 *Stream, projectile_definition *Objects, size_t Count);
uint8 *pack_projectile_definition(uint8 *Stream, projectile_definition *Objects, size_t Count);

#endif

#endif

