#include "stdafx.h"
/*
	weapons.c

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

	Saturday, May 13, 1995 4:41:04 PM- rdm created.
		Recreating to fix all the annoying problems.

Feb. 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 19, 2000 (Loren Petrich):
	Suppressed debug checking of which weapons and triggers
	in get_trigger_definition()
	
March 2, 2000 (Loren Petrich):
	Suppressed player_weapon_has_ammo() assert in should_switch_to_weapon();
	causes problems in "Missed Island"'s first level.
	
March 3, 2000 (Loren Petrich):
	Suppressed complicated assert in fire_weapon();
	 causes problems in the map "Dirt Devil", which turns the flamethrower into a jetpack.

Apr 27, 2000 (Loren Petrich):
	Added Josh Elsasser's "don't switch weapons" patch

May 23, 2000 (Loren Petrich):
	Correct behavior of weapon luminosity; it now adds to miner's light
	rather than substituting for it.

May 26, 2000 (Loren Petrich):
	Added XML configuration of shell casings and weapon order.
	Attempted to add more graceful behavior for some weapons being NONE.
	In Muerte Machine, the weapons are disabled if the fists have weapon type NONE;
	implemented the use of this as a flag.
	
	Added "CannotWieldWeapons()" test; it returns true if the fists have a weapon type of NONE

Jun 14, 2000 (Loren Petrich):
	Suppressed assertion about multiple triggers that follows the Dirt-Devil one

Jun 15, 2000 (Loren Petrich):
	Added support for Chris Pruett's Pfhortran

Jul 1, 2000 (Loren Petrich):
	Made some accessors inline

Jul 1, 2000 (Loren Petrich):
	Added Benad's changes

Aug 31, 2000 (Loren Petrich):
	Added stuff for unpacking and packing

Sep 3, 2000 (Loren Petrich):
	Suppressed "assert(weapon_type!=NUMBER_OF_WEAPONS);" in a search-for-which-weapon loop;
	some physics models get to this without causing other trouble

Oct 19, 2000 (Loren Petrich):
	Weapon-sprite absence in get_weapon_display_information() handled by bugging out instead of
	a failed assertion; having a SMG will not crash if one's using a M2 shapes file.
	Also, added a bug-out in case of no view being found.

Dec 24, 2000 (Loren Petrich):
	Added support for idle-weapon animations

Dec 31, 2000 (Loren Petrich):
	Turned a remaining out-of-range assert into a no-render

Jan 6, 2001 (Loren Petrich):
	Added modification of guided-projectile patch from AlexJLS@aol.com;
	one can now shoot guided missiles.

Feb 1, 2001 (Loren Petrich):
	Added fix for firing-animation wraparound; prevent_wrap is true for those animations also.

Apr 10, 2003 (Woody Zenfell):
        Fixed bug where dropping the skull made two of them (had this really been in there for almost 3 years??)
*/

///#include "cseries.h"
#include "map.h"

#include "projectiles.h"
#include "player.h"
#include "weapons.h"
#include "mysound.h"
#include "interface.h"
#include "items.h"

#include "monsters.h"
//#include "game_window.h"

#include "Packing.h"
//#include "shell.h"

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "weapon_definitions.h"

#ifdef env68k
	#pragma segment weapons
#endif

// To Do:
// lowering second weapon on ammo empty flubs.

/* ------------- enums */
enum /* weapon states */
{
	_weapon_idle, /* if weapon_delay is non-zero, the weapon cannot be fired again yet */
	_weapon_raising, /* weapon is rising to idle position */
	_weapon_lowering, /* weapon is lowering off the screen */
	_weapon_charging, /* Weapon is charging to fire.. */
	_weapon_charged, /* Ready to fire.. */
	_weapon_firing, /* in firing animation */
	_weapon_recovering, /* Weapon is recovering from firing. */
	_weapon_awaiting_reload, /* About to start reload sequence */
	_weapon_waiting_to_load, /* waiting to actually put bullets in */
	_weapon_finishing_reload, /* finishing the reload */

	_weapon_lowering_for_twofisted_reload,	/* lowering so the other weapon can reload */
	_weapon_awaiting_twofisted_reload, /* waiting for other to lower.. */
	_weapon_waiting_for_twofist_to_reload, /* we are offscreen, waiting for the other to finish its load */
	_weapon_sliding_over_to_second_position, /* pistol is going across when the weapon is present */
	_weapon_sliding_over_from_second_position, /* Pistol returning to center of screen.. */
	_weapon_waiting_for_other_idle_to_reload, /* Pistol awaiting friend's idle.. */
	NUMBER_OF_WEAPON_STATES
};

enum {
	_trigger_down= 0x0001,
	_primary_weapon_is_up= 0x0002,
	_secondary_weapon_is_up= 0x0004,
	_wants_twofist= 0x0008,
	_flip_state= 0x0010
};

enum {
	_weapon_type= 0,
	_shell_casing_type,
	NUMBER_OF_DATA_TYPES
};

enum { /* For the flags */ /* [11.unused 1.horizontal 1.vertical 3.unused] */
	_flip_shape_horizontal= 0x08,
	_flip_shape_vertical= 0x10
};

#define PRIMARY_WEAPON_IS_VALID(wd) ((wd)->flags & _primary_weapon_is_up)
#define SECONDARY_WEAPON_IS_VALID(wd) ((wd)->flags & _secondary_weapon_is_up)
#define SET_PRIMARY_WEAPON_IS_VALID(wd, v)  ((void)((v) ? ((wd)->flags |= _primary_weapon_is_up) : ((wd)->flags &= ~_primary_weapon_is_up)))
#define SET_SECONDARY_WEAPON_IS_VALID(wd, v)  ((void)((v) ? ((wd)->flags |= _secondary_weapon_is_up) : ((wd)->flags &= ~_secondary_weapon_is_up)))

#define SET_WEAPON_WANTS_TWOFIST(wd, v)  ((void)((v) ? ((wd)->flags |= _wants_twofist) : ((wd)->flags &= ~_wants_twofist)))
#define WEAPON_WANTS_TWOFIST(wd) ((wd)->flags & _wants_twofist)

#define TRIGGER_IS_DOWN(wd) ((wd)->flags & _trigger_down)
#define SET_TRIGGER_DOWN(wd, v)  ((void)((v) ? ((wd)->flags |= _trigger_down) : ((wd)->flags &= ~_trigger_down)))

#define GET_WEAPON_VARIANCE_SIGN(wd) (((wd)->flags & _flip_state) ? (1) : (-1))
#define FLIP_WEAPON_VARIANCE_SIGN(wd) (((wd)->flags & _flip_state) ? ((wd)->flags &= ~_flip_state) : ((wd)->flags |= _flip_state))

#define PISTOL_SEPARATION_WIDTH (FIXED_ONE/4)
#define AUTOMATIC_STILL_FIRING_DURATION (4)
#define FIRING_BEFORE_SHELL_CASING_SOUND_IS_PLAYED (TICKS_PER_SECOND/2)
#define COST_PER_CHARGED_WEAPON_SHOT 4					
#define ANGULAR_VARIANCE (32)

enum // shell casing flags
{
	_shell_casing_is_reversed= 0x0001
};
#define SHELL_CASING_IS_REVERSED(s) ((s)->flags&_shell_casing_is_reversed)

/* ----------- structures */
/* ...were all moved to weapons.h */

/* ------------- globals */
/* The array of player weapon states */
static struct player_weapon_data *player_weapons_array;

/* ------------- macros */
#define get_maximum_number_of_players() (MAXIMUM_NUMBER_OF_PLAYERS)
#define BUILD_WEAPON_IDENTIFIER(weapon, trigger) (weapon<<1+trigger)
#define GET_WEAPON_FROM_IDENTIFIER(identifier) (identifier>>1)
#define GET_TRIGGER_FROM_IDENTIFIER(identifier) (identifier&1)

/*static*/ player_weapon_data *get_player_weapon_data(
	const short player_index);

static weapon_definition *get_weapon_definition(
	const short weapon_type);

static shell_casing_definition *get_shell_casing_definition(
	const short type);

/* -------------- accessors */

player_weapon_data *get_player_weapon_data(
	const short player_index)
{
	player_weapon_data *data = GetMemberWithBounds(player_weapons_array,player_index,get_maximum_number_of_players());
	assert(data);
	
	return data;
}

weapon_definition *get_weapon_definition(
	const short weapon_type)
{
	weapon_definition *definition = GetMemberWithBounds(weapon_definitions,weapon_type,NUMBER_OF_WEAPONS);
	assert(definition);
	
	return definition;
}

shell_casing_definition *get_shell_casing_definition(
	const short type)
{
	shell_casing_definition *definition = GetMemberWithBounds(shell_casing_definitions,type,NUMBER_OF_SHELL_CASING_TYPES);
	assert(definition);
	
	return definition;
}

inline void StreamToTrigData(uint8* &S, trigger_data& Object)
{
	StreamToValue(S,Object.state);
	StreamToValue(S,Object.phase);
	StreamToValue(S,Object.rounds_loaded);
	StreamToValue(S,Object.shots_fired);
	StreamToValue(S,Object.shots_hit);
	StreamToValue(S,Object.ticks_since_last_shot);
	StreamToValue(S,Object.ticks_firing);
	StreamToValue(S,Object.sequence);
}

inline void TrigDataToStream(uint8* &S, trigger_data& Object)
{
	ValueToStream(S,Object.state);
	ValueToStream(S,Object.phase);
	ValueToStream(S,Object.rounds_loaded);
	ValueToStream(S,Object.shots_fired);
	ValueToStream(S,Object.shots_hit);
	ValueToStream(S,Object.ticks_since_last_shot);
	ValueToStream(S,Object.ticks_firing);
	ValueToStream(S,Object.sequence);
}


inline void StreamToWeapData(uint8* &S, weapon_data& Object)
{
	StreamToValue(S,Object.weapon_type);
	StreamToValue(S,Object.flags);
	StreamToValue(S,Object.unused);
	for (int k=0; k<NUMBER_OF_TRIGGERS; k++)
		StreamToTrigData(S,Object.triggers[k]);
}

inline void WeapDataToStream(uint8* &S, weapon_data& Object)
{
	ValueToStream(S,Object.weapon_type);
	ValueToStream(S,Object.flags);
	ValueToStream(S,Object.unused);
	for (int k=0; k<NUMBER_OF_TRIGGERS; k++)
		TrigDataToStream(S,Object.triggers[k]);
}


inline void StreamToShellData(uint8* &S, shell_casing_data& Object)
{
	StreamToValue(S,Object.type);
	StreamToValue(S,Object.frame);
		
	StreamToValue(S,Object.flags);
	
	StreamToValue(S,Object.x);
	StreamToValue(S,Object.y);
	StreamToValue(S,Object.vx);
	StreamToValue(S,Object.vy);
}

inline void ShellDataToStream(uint8* &S, shell_casing_data& Object)
{
	ValueToStream(S,Object.type);
	ValueToStream(S,Object.frame);
	
	ValueToStream(S,Object.flags);
	
	ValueToStream(S,Object.x);
	ValueToStream(S,Object.y);
	ValueToStream(S,Object.vx);
	ValueToStream(S,Object.vy);
}


uint8 *unpack_player_weapon_data(uint8 *Stream, size_t Count)
{
	uint8* S = Stream;
	player_weapon_data* ObjPtr = player_weapons_array;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->current_weapon);
		StreamToValue(S,ObjPtr->desired_weapon);
		for (unsigned m=0; m<NUMBER_OF_WEAPONS; m++)
			StreamToWeapData(S,ObjPtr->weapons[m]);
		for (unsigned m=0; m<MAXIMUM_SHELL_CASINGS; m++)
			StreamToShellData(S,ObjPtr->shell_casings[m]);
	}
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_weapon_data));
	return S;
}

uint8 *pack_player_weapon_data(uint8 *Stream, size_t Count)
{
	uint8* S = Stream;
	player_weapon_data* ObjPtr = player_weapons_array;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->current_weapon);
		ValueToStream(S,ObjPtr->desired_weapon);
		for (size_t m=0; m<NUMBER_OF_WEAPONS; m++)
			WeapDataToStream(S,ObjPtr->weapons[m]);
		for (size_t m=0; m<MAXIMUM_SHELL_CASINGS; m++)
			ShellDataToStream(S,ObjPtr->shell_casings[m]);
	}
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_weapon_data));
	return S;
}

inline void StreamToTrigDefData(uint8* &S, trigger_definition& Object)
{
	StreamToValue(S,Object.rounds_per_magazine);
	StreamToValue(S,Object.ammunition_type);	
	StreamToValue(S,Object.ticks_per_round);
	StreamToValue(S,Object.recovery_ticks);
	StreamToValue(S,Object.charging_ticks);
	StreamToValue(S,Object.recoil_magnitude);
	StreamToValue(S,Object.firing_sound);
	StreamToValue(S,Object.click_sound);
	StreamToValue(S,Object.charging_sound);	
	StreamToValue(S,Object.shell_casing_sound);
	StreamToValue(S,Object.reloading_sound);
	StreamToValue(S,Object.charged_sound);
	StreamToValue(S,Object.projectile_type);
	StreamToValue(S,Object.theta_error);
	StreamToValue(S,Object.dx);
	StreamToValue(S,Object.dz);
	StreamToValue(S,Object.shell_casing_type);
	StreamToValue(S,Object.burst_count);
}

inline void TrigDefDataToStream(uint8* &S, trigger_definition& Object)
{
	ValueToStream(S,Object.rounds_per_magazine);
	ValueToStream(S,Object.ammunition_type);	
	ValueToStream(S,Object.ticks_per_round);
	ValueToStream(S,Object.recovery_ticks);
	ValueToStream(S,Object.charging_ticks);
	ValueToStream(S,Object.recoil_magnitude);
	ValueToStream(S,Object.firing_sound);
	ValueToStream(S,Object.click_sound);
	ValueToStream(S,Object.charging_sound);	
	ValueToStream(S,Object.shell_casing_sound);
	ValueToStream(S,Object.reloading_sound);
	ValueToStream(S,Object.charged_sound);
	ValueToStream(S,Object.projectile_type);
	ValueToStream(S,Object.theta_error);
	ValueToStream(S,Object.dx);
	ValueToStream(S,Object.dz);
	ValueToStream(S,Object.shell_casing_type);
	ValueToStream(S,Object.burst_count);
}


uint8 *unpack_weapon_definition(uint8 *Stream, size_t Count)
{
	return unpack_weapon_definition(Stream,weapon_definitions,Count);
}

uint8 *unpack_weapon_definition(uint8 *Stream, weapon_definition *Objects, size_t Count)
{
	uint8* S = Stream;
	weapon_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->item_type);
		StreamToValue(S,ObjPtr->powerup_type);	
		StreamToValue(S,ObjPtr->weapon_class);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->firing_light_intensity);
		StreamToValue(S,ObjPtr->firing_intensity_decay_ticks);
		
		StreamToValue(S,ObjPtr->idle_height);
		StreamToValue(S,ObjPtr->bob_amplitude);
		StreamToValue(S,ObjPtr->kick_height);	
		StreamToValue(S,ObjPtr->reload_height);
		StreamToValue(S,ObjPtr->idle_width);
		StreamToValue(S,ObjPtr->horizontal_amplitude);
		
		StreamToValue(S,ObjPtr->collection);
		StreamToValue(S,ObjPtr->idle_shape);
		StreamToValue(S,ObjPtr->firing_shape);
		StreamToValue(S,ObjPtr->reloading_shape);
		StreamToValue(S,ObjPtr->unused);
		StreamToValue(S,ObjPtr->charging_shape);
		StreamToValue(S,ObjPtr->charged_shape);
		
		StreamToValue(S,ObjPtr->ready_ticks);
		StreamToValue(S,ObjPtr->await_reload_ticks);
		StreamToValue(S,ObjPtr->loading_ticks);
		StreamToValue(S,ObjPtr->finish_loading_ticks);
		StreamToValue(S,ObjPtr->powerup_ticks);
		
		for (int m=0; m<NUMBER_OF_TRIGGERS; m++)
			StreamToTrigDefData(S,ObjPtr->weapons_by_trigger[m]);
	}
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_weapon_definition));
	return S;
}


uint8 *pack_weapon_definition(uint8 *Stream, size_t Count)
{
	return pack_weapon_definition(Stream,weapon_definitions,Count);
}

uint8 *pack_weapon_definition(uint8 *Stream, weapon_definition *Objects, size_t Count)
{
	uint8* S = Stream;
	weapon_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->item_type);
		ValueToStream(S,ObjPtr->powerup_type);	
		ValueToStream(S,ObjPtr->weapon_class);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->firing_light_intensity);
		ValueToStream(S,ObjPtr->firing_intensity_decay_ticks);
		
		ValueToStream(S,ObjPtr->idle_height);
		ValueToStream(S,ObjPtr->bob_amplitude);
		ValueToStream(S,ObjPtr->kick_height);	
		ValueToStream(S,ObjPtr->reload_height);
		ValueToStream(S,ObjPtr->idle_width);
		ValueToStream(S,ObjPtr->horizontal_amplitude);
		
		ValueToStream(S,ObjPtr->collection);
		ValueToStream(S,ObjPtr->idle_shape);
		ValueToStream(S,ObjPtr->firing_shape);
		ValueToStream(S,ObjPtr->reloading_shape);
		ValueToStream(S,ObjPtr->unused);
		ValueToStream(S,ObjPtr->charging_shape);
		ValueToStream(S,ObjPtr->charged_shape);
		
		ValueToStream(S,ObjPtr->ready_ticks);
		ValueToStream(S,ObjPtr->await_reload_ticks);
		ValueToStream(S,ObjPtr->loading_ticks);
		ValueToStream(S,ObjPtr->finish_loading_ticks);
		ValueToStream(S,ObjPtr->powerup_ticks);
		
		for (int m=0; m<NUMBER_OF_TRIGGERS; m++)
			TrigDefDataToStream(S,ObjPtr->weapons_by_trigger[m]);
	}
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_weapon_definition));
	return S;
}


// LP additions: get weapon-definition size and number of weapon types
size_t get_number_of_weapon_types() {return NUMBER_OF_WEAPONS;}


struct shell_casing_definition shell_casing_definitions[NUMBER_OF_SHELL_CASING_TYPES]=
{
	{ // _shell_casing_assault_rifle,
		_collection_weapons_in_hand, 19, /* collection, shape */
		
		FIXED_ONE/2 + FIXED_ONE/6, FIXED_ONE/8, /* x0, y0 */
		FIXED_ONE/8, FIXED_ONE/32, /* vx0, vy0 */
		0, -FIXED_ONE/256, /* dvx, dvy */
	},
	
	{ // _shell_casing_pistol_center
		_collection_weapons_in_hand, 18, /* collection, shape */
		
		FIXED_ONE/2 + FIXED_ONE/8, FIXED_ONE/4, /* x0, y0 */
		FIXED_ONE/16, FIXED_ONE/32, /* vx0, vy0 */
		0, -FIXED_ONE/400, /* dvx, dvy */
	},
	
	{ // _shell_casing_pistol_left
		_collection_weapons_in_hand, 18, /* collection, shape */
		
		FIXED_ONE/2 - FIXED_ONE/4, FIXED_ONE/4, /* x0, y0 */
		- FIXED_ONE/16, FIXED_ONE/32, /* vx0, vy0 */
		0, -FIXED_ONE/400, /* dvx, dvy */
	},
	
	{ // _shell_casing_pistol_right
		_collection_weapons_in_hand, 18, /* collection, shape */
		
		FIXED_ONE/2 + FIXED_ONE/4, FIXED_ONE/4, /* x0, y0 */
		FIXED_ONE/16, FIXED_ONE/32, /* vx0, vy0 */
		0, -FIXED_ONE/400, /* dvx, dvy */
	},
	
	// LP addition: clone of assault-rifle casing
	{ // _shell_casing_smg,
		_collection_weapons_in_hand, 26, /* collection, shape */
		
		FIXED_ONE/2 + FIXED_ONE/6, FIXED_ONE/8, /* x0, y0 */
		FIXED_ONE/8, FIXED_ONE/32, /* vx0, vy0 */
		0, -FIXED_ONE/256, /* dvx, dvy */
	},
};

/* ---------- structures */


/* ------------------------ globals */

static int16 weapon_ordering_array[]= {
	_weapon_fist,
	_weapon_pistol,
	_weapon_plasma_pistol,
	_weapon_shotgun,
	_weapon_assault_rifle,
	// LP addition:
	_weapon_smg,
	_weapon_flamethrower,
	_weapon_missile_launcher,
	_weapon_alien_shotgun,
	_weapon_ball
};


struct weapon_definition weapon_definitions[NUMBER_OF_WEAPONS]=
{
	/* Fist*/
	{
		/* item type, powerup type, item class, item flags */
		_i_knife, NONE, _melee_class, _weapon_fires_under_media,

		FIXED_ONE_HALF, 0, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/15, FIXED_ONE/15, FIXED_ONE/16, 0,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_fist_idle, _fist_punching, _fist_idle,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/4, 0, 0, 0, 0,

		{
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing sound, reloading sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_fist,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			},
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing, reload sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_fist,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			}
		}
	},
	
	/* Magnum .45 "mega class"- dual fisted */
	{
		/* item type, powerup type, item class, item flags */
		_i_magnum, NONE, _twofisted_pistol_class, _weapon_fires_out_of_phase,

		3*FIXED_ONE/4, TICKS_PER_SECOND/8, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/15, FIXED_ONE/25, FIXED_ONE/8, FIXED_ONE,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_pistol_idle, _pistol_firing, _pistol_reloading,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/3, 5, 5, 5, 0, // was NONE

		{
			{
				/* rounds per magazine */
				8, 
	
				/* Ammunition type */
				_i_magnum_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				10,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_magnum_firing, _snd_empty_gun, NONE, NONE, _snd_magnum_reloading, NONE,
				
				/* projectile type */
				_projectile_pistol_bullet,
				
				/* theta error */
				1,
				
				/* dx, dz */
				(WORLD_ONE_FOURTH/6), -NORMAL_WEAPON_DZ,		/* Primary */
				
				/* shell casing type */
				_shell_casing_pistol, 

				/* burst count */
				0
			},
			
			/* left weapon (for consistency)... */
			{
				/* rounds per magazine */
				8, 
	
				/* Ammunition type */
				_i_magnum_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				10,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_magnum_firing, _snd_empty_gun, NONE, NONE, _snd_magnum_reloading, NONE,
				
				/* projectile type */
				_projectile_pistol_bullet,
				
				/* theta error */
				1,
				
				/* dx, dz */
				-(WORLD_ONE_FOURTH/6), -NORMAL_WEAPON_DZ,		/* Primary */
				
				/* shell casing type */
				_shell_casing_pistol,

				/* burst count */
				0
			}
		}
	},

	/* Fusion Pistol */
	{
		/* item type, powerup type, item class, item flags */
		_i_plasma_pistol, NONE, _dual_function_class, _weapon_overloads | _weapon_fires_under_media | _weapon_triggers_share_ammo,

		3*FIXED_ONE/4, TICKS_PER_SECOND/3, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE, FIXED_ONE/25, FIXED_ONE/8, FIXED_ONE,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_fusion_idle, _fusion_firing, NONE,
		NONE,
		NONE, _fusion_charged,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/3, TICKS_PER_SECOND/2, TICKS_PER_SECOND/2, TICKS_PER_SECOND/2, 0,

		{
			{
				/* rounds per magazine */
				20, 
	
				/* Ammunition type */
				_i_plasma_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/6, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_fusion_firing, _snd_empty_gun, _snd_fusion_charging, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_fusion_bolt_minor,
				
				/* theta error */
				1,
				
				/* dx, dz */
				0, -4*NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			},
			{
				/* rounds per magazine */
				20,  // this should not be used...
	
				/* Ammunition type */
				_i_plasma_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				5, 4, TICKS_PER_SECOND/2,
				
				/* recoil magnitude */
				20,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_major_fusion_firing, _snd_empty_gun, _snd_fusion_charging, NONE, NONE, _snd_major_fusion_charged,
				
				/* projectile type */
				_projectile_fusion_bolt_major,
				
				/* theta error */
				1,
				
				/* dx, dz */
				0, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			}
		}
	},

	/* Assault Rifle */
	{
		/* item type, powerup type, item class, item flags */
		_i_assault_rifle, NONE, _multipurpose_class, _weapon_is_automatic,

		3*FIXED_ONE/4, TICKS_PER_SECOND/5, /* firing intensity, firing decay */


		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/6, FIXED_ONE/35, FIXED_ONE/16, 3*FIXED_ONE/4,

		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,
		
		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_assault_rifle_idle, _assault_rifle_firing, _assault_rifle_reloading,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/2, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, 0,

		{
			{
				/* rounds per magazine */
				52, 
	
				/* Ammunition type */
				_i_assault_rifle_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, 0, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_assault_rifle_firing, _snd_empty_gun, NONE, _snd_assault_rifle_shell_casings, _snd_assault_rifle_reloading, NONE,
				
				/* projectile type */
				_projectile_rifle_bullet,
				
				/* theta error */
				10,
				
				/* dx, dz */
				0, -NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				_shell_casing_assault_rifle,

				/* burst count */
				0
			},
			{
				/* rounds per magazine */
				7, 
	
				/* Ammunition type */
				_i_assault_grenade_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				TICKS_PER_SECOND/6, (3*TICKS_PER_SECOND)/4 - TICKS_PER_SECOND/6, 0,
				
				/* recoil magnitude */
				40,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_grenade_launcher_firing, _snd_empty_gun, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_grenade,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, -5*NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			}
		}
	},

	/* Rocket Launcher */
	{
		/* item type, powerup_type, item class, item flags */
		_i_missile_launcher, NONE, _normal_class, _no_flags,

		FIXED_ONE, TICKS_PER_SECOND/3, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		(3*FIXED_ONE)/4, FIXED_ONE/50, FIXED_ONE/20, FIXED_ONE,
		
		/* horizontal positioning.. */
		(FIXED_ONE_HALF/4), 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_missile_launcher_idle, _missile_launcher_firing, NONE,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND, TICKS_PER_SECOND, TICKS_PER_SECOND, TICKS_PER_SECOND, 0,

		{
			{
				/* rounds per magazine */
				2, 
	
				/* Ammunition type */
				_i_missile_launcher_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				TICKS_PER_SECOND/2, TICKS_PER_SECOND/10, 0,
				
				/* recoil magnitude */
				100,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_rocket_firing, _snd_empty_gun, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_rocket,
				
				/* theta error */
				0,
				
				/* dx, dz */
				-WORLD_ONE_FOURTH, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			},
			
			/* unused */
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing, reload sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_fist,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			}
		}
	},

	/* flamethrower */
	{
		/* item type, powerup type, item class, item flags */
		_i_flamethrower, NONE, _normal_class, _weapon_is_automatic,

		3*FIXED_ONE/4, TICKS_PER_SECOND/3, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE, FIXED_ONE/35, FIXED_ONE/15, FIXED_ONE/2,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_flamethrower_idle, _flamethrower_firing, NONE,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND, (2*TICKS_PER_SECOND)/3, (2*TICKS_PER_SECOND)/3, (2*TICKS_PER_SECOND)/3, 0,

		{
			{
				/* rounds per magazine */
				7*TICKS_PER_SECOND, 
	
				/* Ammunition type */
				_i_flamethrower_canister, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				2,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_flamethrower, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_flamethrower_burst,
				
				/* theta error */
				0,
				
				/* dx, dz */
				20, -50,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			},
			
			/* unused */
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing, reload sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_fist,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, 0,
				
				/* shell casing type */
				NONE, 

				/* burst count */
				0
			}
		}
	},

	/* alien weapon */
	{
		/* item type, powerup type, item class, item flags */
		_i_alien_shotgun, NONE, _multipurpose_class, _weapon_is_automatic | _weapon_disappears_after_use | _weapon_has_random_ammo_on_pickup | _weapon_triggers_share_ammo | _weapon_secondary_has_angular_flipping,

		3*FIXED_ONE/4, TICKS_PER_SECOND/5, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/6, FIXED_ONE/35, FIXED_ONE/16, 3*FIXED_ONE/4,

		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,
		
		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_alien_weapon_idle, _alien_weapon_firing, NONE,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/2, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, 0,

		{
			{
				/* rounds per magazine */
				2000, 
	
				/* Ammunition type */
				_i_alien_shotgun_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, 0, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_enforcer_attack, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_alien_weapon,
				
				/* theta error */
				1,
				
				/* dx, dz */
				0, -8*NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				NONE,

				/* burst count */
				0
			},

			{
				/* rounds per magazine */
				50, 
	
				/* Ammunition type */
				_i_alien_shotgun_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, 0, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_enforcer_attack, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_alien_weapon,
				
				/* theta error */
				1,
				
				/* dx, dz */
				0, -8*NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				NONE,

				/* burst count */
				0
			}
		}
	},

#define SHOTGUN_BURST_COUNT 10
#define SHOTGUN_SPREAD 5
	/* Shotgun- dual fisted */
	{
		/* item type, powerup type, item class, item flags */
		_i_shotgun, NONE, _twofisted_pistol_class, _weapon_reloads_in_one_hand,

		3*FIXED_ONE/4, TICKS_PER_SECOND/8, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/15, FIXED_ONE/25, FIXED_ONE/8, FIXED_ONE,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_shotgun_idle, _shotgun_firing, _shotgun_reloading,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/3, 5, 5, 5, 0, // was NONE

		{
			{
				/* rounds per magazine */
				SHOTGUN_BURST_COUNT, 
	
				/* Ammunition type */
				_i_shotgun_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				25,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_shotgun_firing, _snd_empty_gun, NONE, NONE, _snd_shotgun_reloading, NONE,
				
				/* projectile type */
				_projectile_shotgun_bullet,
				
				/* theta error */
				SHOTGUN_SPREAD,
				
				/* dx, dz */
				(WORLD_ONE_FOURTH/6), -NORMAL_WEAPON_DZ,		/* Primary */
				
				/* shell casing type */
				NONE, 

				/* burst count */
				SHOTGUN_BURST_COUNT
			},
			
			/* left weapon (for consistency)... */
			{
				/* rounds per magazine */
				SHOTGUN_BURST_COUNT, 
	
				/* Ammunition type */
				_i_shotgun_magazine, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				25,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_shotgun_firing, _snd_empty_gun, NONE, NONE, _snd_shotgun_reloading, NONE,
				
				/* projectile type */
				_projectile_shotgun_bullet,
				
				/* theta error */
				SHOTGUN_SPREAD,
				
				/* dx, dz */
				(WORLD_ONE_FOURTH/6), -NORMAL_WEAPON_DZ,		/* Primary */
				
				/* shell casing type */
				NONE, 

				/* burst count */
				SHOTGUN_BURST_COUNT
			}
		}
	},
	
	/* The Ball- Don't Drop It. */
	{
		/* item type, powerup type, item class, item flags */
		_i_red_ball, NONE, _normal_class, 0,

		0, 0, /* firing intensity, firing decay */

		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/15, FIXED_ONE/15, FIXED_ONE/16, 0,
		
		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,

		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_collection_player,
		30, 30, 30,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/4, 0, 0, 0, 0,

		{
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing, reload sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_ball_dropped,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, -150,		/* Primary */

				/* shell casing type */
				NONE, 
				
				/* burst count */
				0
			},
			
			{
				/* rounds per magazine */
				1, 
	
				/* Ammunition type */
				NONE, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, TICKS_PER_SECOND/3, 0,
				
				/* recoil magnitude */
				0,
				
				/* firing, click, charging, shell casing, reload sound */
				NONE, NONE, NONE, NONE, NONE, NONE,
				
				/* projectile type */
				_projectile_ball_dropped,
				
				/* theta error */
				0,
				
				/* dx, dz */
				0, 0,		/* Primary */

				/* shell casing type */
				NONE, 
				
				/* burst count */
				0
			}
		}
	},

	/* LP addition: SMG */
	{
		/* item type, powerup type, item class, item flags */
		_i_smg, NONE, _normal_class, _weapon_is_automatic|_weapon_fires_under_media,

		3*FIXED_ONE/4, TICKS_PER_SECOND/5, /* firing intensity, firing decay */


		/* idle height, bob amplitude, kick height, reload height */
		FIXED_ONE+FIXED_ONE/6, FIXED_ONE/35, FIXED_ONE/16, 3*FIXED_ONE/4,

		/* horizontal positioning.. */
		FIXED_ONE_HALF, 0,
		
		/* collection, idle, firing, reloading shapes; shell casing, charging, charged */
		_weapon_in_hand_collection,
		_smg_idle, _smg_firing, _smg_reloading,
		NONE,
		NONE, NONE,

		/* ready/await/load/finish/powerup rounds ticks */
		TICKS_PER_SECOND/2, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, TICKS_PER_SECOND/3, 0,

		{
			{
				/* rounds per magazine */
				32, 
	
				/* Ammunition type */
				_i_smg_ammo, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, 0, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_smg_firing, _snd_empty_gun, NONE, _snd_assault_rifle_shell_casings, _snd_smg_reloading, NONE,
				
				/* projectile type */
				_projectile_smg_bullet,
				
				/* theta error */
				3,
				
				/* dx, dz */
				0, -NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				_shell_casing_smg,

				/* burst count */
				2
			},
			{
				/* rounds per magazine */
				32, 
	
				/* Ammunition type */
				_i_smg_ammo, 
				
				/* Ticks per round, recovery ticks, charging ticks */
				NONE, 0, 0,
				
				/* recoil magnitude */
				5,
				
				/* firing, click, charging, shell casing, reload sound */
				_snd_smg_firing, _snd_empty_gun, NONE, _snd_assault_rifle_shell_casings, _snd_smg_reloading, NONE,
				
				/* projectile type */
				_projectile_smg_bullet,
				
				/* theta error */
				3,
				
				/* dx, dz */
				0, -NORMAL_WEAPON_DZ,
				
				/* shell casing type */
				_shell_casing_smg,

				/* burst count */
				2
			}
		}
	},
};
