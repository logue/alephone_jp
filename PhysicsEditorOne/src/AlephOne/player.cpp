#include "stdafx.h"
/*
PLAYER.C

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

Saturday, December 11, 1993 10:25:55 AM

Friday, September 30, 1994 5:48:25 PM (Jason)
	moved nearly all sounds out of the damage_definition structure and into shapes.
Wednesday, October 26, 1994 3:18:59 PM (Jason)
	invincible players are now damaged by fusion projectiles.
Wednesday, November 30, 1994 6:56:20 PM  (Jason)
	oxygen is used up faster by running and by firing.
Thursday, January 12, 1995 11:18:18 AM  (Jason')
	dead players don’t continue to use up oxygen.
Thursday, July 6, 1995 4:53:52 PM
	supports multi-player cooperative games. (Ryan)

Feb 4, 2000 (Loren Petrich):
	Added SMG wielding stuff

	Changed halt() to assert(false) for better debugging

Feb 18, 2000 (Loren Petrich):
	Added support for a chase cam.
	Note that mark_player_collections() always loads the player sprites
	in expectation of a chase cam; this could be made to conditional on
	whether a chase cam will ever be active.

Feb 21, 2000 (Loren Petrich):
	Changed NO_TELEPORTATION_DESTINATION to SHRT_MAX, an idiot-proof value,
	since there are unlikely to be that many polygons in a map.
	
	Added upward and rightward shifts of the chase-cam position

Feb 25, 2000 (Loren Petrich):
	Moved chase-cam data into preferences data; using accessor in "interface.h"
	Made it possible to swim under a liquid if one has the ball

Feb 26, 2000 (Loren Petrich):
	Fixed level-0 teleportation bug; the hack is to move the destination
	down by 1.
	
	Added chase-cam reset feature, for the purpose of doing chase-cam inertia.
	The reset is necessary to take into account teleporting or entering a level.

Mar 2, 2000 (Loren Petrich):
	Moved the chase-cam stuff into ChaseCam.c/h
	
Mar 22, 2000 (Loren Petrich):
	Added a function to revive_player() to reset the field of view properly
	when reviving

May 14, 2000 (Loren Petrich):
	Added XML-configuration support for various player features

May 22, 2000 (Loren Petrich):
	Added XML configurability for the powerup durations

May 27, 2000 (Loren Petrich):
	Added oxygen depletion and replenishment rates

Jun 11, 2000 (Loren Petrich):
	Pegging health and oxygen to maximum values when damaged;
	takes into account negative damage from healing projectiles.
	Also turned "agressor" into "aggressor".

Jun 15, 2000 (Loren Petrich):
	Added support for Chris Pruett's Pfhortran

Jun 28, 2000 (Loren Petrich):
	Generalized the invincibility-powerup vulnerability and added XML support for that

Jul 1, 2000 (Loren Petrich):
	Added Benad's changes

Jul 10, 2000 (Loren Petrich):
	Changed calculate_player_team() slightly; no more first vassert()

Aug 31, 2000 (Loren Petrich):
	Added stuff for unpacking and packing

Apr 27, 2001 (Loren Petrich):
	Made player guided missiles optional
        
Oct 21, 2001 (Woody Zenfell):
        Made player_shape_definitions available to the rest of the system -
        in particular, so that SDL network dialog widgets can use it to render
        player icons.

Feb 20, 2002 (Woody Zenfell):
    Ripped action_queue support out into new ActionQueues class (see ActionQueues.h)
    Providing pointer gRealActionQueues to help others find the set of queues they are
    accustomed to using.

May 20, 2002 (Woody Zenfell):
    get_ticks_since_local_player_in_terminal() mechanism

Jan 12, 2003 (Woody Zenfell):
	Single entry point (reset_action_queues()) to reset all ActionQueues that need to be reset

May 22, 2003 (Woody Zenfell):
	Fixing damaging polygon types; giving player netgame penalty feedback; announcing player
	net disconnects.

 May 27, 2003 (Woody Zenfell):
	I hear dead people.  (netmic, star protocol or newer only)

 June 14, 2003 (Woody Zenfell):
	update_players() now has a predictive mode of execution which takes many fewer actions
	(i.e. tries to alter only state like the player's location and facing etc.)

 May 21, 2004 (Alexei Svitkine):
	Made all the MML-settable stuff in this file have a ResetValues method that resets to
	old values (which we now save). Had to move some free-standing variables into structs
	for this.
*/

#define DONT_REPEAT_DEFINITIONS

/*#include "cseries.h"
*/
#include "player.h"
#include "map.h"
#include "monster_definitions.h"
#include "monsters.h"
#include "interface.h"
#include "mysound.h"
#include "items.h"
#include "effects.h"
#include "fades.h"
#include "media.h"
/*
*/
#include "weapons.h"
/*#include "game_window.h"
#include "computer_interface.h"
*/
#include "projectiles.h"
/*#include "network_games.h"
#include "network.h"
#include "screen.h"
#include "shell.h" // for screen_printf()
*/

/*
//anybody on the receiving pad of a teleport should explode (what happens to invincible guys?)
// Really should create a function that initializes the player state.
??new players should teleport in
*/

// LP addition:
//#include "ChaseCam.h"
#include "Packing.h"
//#include "network.h"

// ZZZ additions:
//#include "ActionQueues.h"

// jkvw addition:
//#include "lua_script.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#ifdef env68k
#pragma segment player
#endif

/* ---------- constants */

struct player_powerup_durations_definition {
	short InvisibilityDuration;
	short InvincibilityDuration;
	short ExtravisionDuration;
	short InfravisionDuration;
};

// These are variables, because they can be set with an XML parser
struct player_powerup_durations_definition player_powerup_durations = {
	70*TICKS_PER_SECOND,
	50*TICKS_PER_SECOND,
	3*TICKS_PER_MINUTE,
	3*TICKS_PER_MINUTE
};

#define kINVISIBILITY_DURATION  player_powerup_durations.InvisibilityDuration
#define kINVINCIBILITY_DURATION player_powerup_durations.InvincibilityDuration
#define kEXTRAVISION_DURATION   player_powerup_durations.ExtravisionDuration
#define kINFRAVISION_DURATION   player_powerup_durations.InfravisionDuration

#define MINIMUM_REINCARNATION_DELAY (TICKS_PER_SECOND)
#define NORMAL_REINCARNATION_DELAY (10*TICKS_PER_SECOND)
#define SUICIDE_REINCARNATION_DELAY (15*TICKS_PER_SECOND)

#define DEAD_PLAYER_HEIGHT WORLD_ONE_FOURTH

#define OXYGEN_WARNING_LEVEL TICKS_PER_MINUTE
#define OXYGEN_WARNING_FREQUENCY (TICKS_PER_MINUTE/4)
#define OXYGEN_WARNING_OFFSET (10*TICKS_PER_SECOND)

#define LAST_LEVEL 100

/* ---------- structures */

// ZZZ: moved struct action_queue inside ActionQueues (see ActionQueues.cpp).
// ZZZ: moved struct player_shape_information to player.h for sharing

struct damage_response_definition
{
	short type;
	short damage_threshhold; /* NONE is none, otherwise bumps fade by one if over threshhold */
	
	short fade;
	short sound, death_sound, death_action;
};

struct player_powerup_definition
{
	short Powerup_Invincibility;
	short Powerup_Invisibility;
	short Powerup_Infravision;
	short Powerup_Extravision;
	short Powerup_TripleEnergy;
	short Powerup_DoubleEnergy;
	short Powerup_Energy;
	short Powerup_Oxygen;
};

/* ---------- globals */

struct player_data *players;
struct damage_record team_damage_given[NUMBER_OF_TEAM_COLORS];
struct damage_record team_damage_taken[NUMBER_OF_TEAM_COLORS];
struct damage_record team_monster_damage_taken[NUMBER_OF_TEAM_COLORS];
struct damage_record team_monster_damage_given[NUMBER_OF_TEAM_COLORS];
struct damage_record team_friendly_fire[NUMBER_OF_TEAM_COLORS];

struct player_data *local_player, *current_player;
short local_player_index, current_player_index;

// ZZZ: Let folks ask for a pointer to the main set of ActionQueues.
//static ActionQueues*   sRealActionQueues = NULL;
//ActionQueues* GetRealActionQueues() { return sRealActionQueues; }

static struct player_shape_definitions player_shapes=
{
	6, /* collection */
	
	9, 8, /* dying hard, dying soft */
	11, 10, /* dead hard, dead soft */
	{7, 0, 0, 24, 23}, /* legs: stationary, walking, running, sliding, airborne */
	// LP additions: SMG-wielding/firing shapes (just before last two)
	{1, 3, 20, 26, 14, 12, 31, 16, 28, 33, 5, 18}, /* idle torsos: fists, magnum, fusion, assault, rocket, flamethrower, alien, shotgun, double pistol, double shotgun, da ball */
	{1, 3, 21, 26, 14, 12, 31, 16, 28, 33, 5, 18}, /* charging torsos: fists, magnum, fusion, assault, rocket, flamethrower, alien, shotgun, double pistol, double shotgun, ball */
	{2, 4, 22, 27, 15, 13, 32, 17, 28, 34, 6, 19}, /* firing torsos: fists, magnum, fusion, assault, rocket, flamethrower, alien, shotgun, double pistol, double shotgun, ball */
};

#define NUMBER_OF_PLAYER_INITIAL_ITEMS (sizeof(player_initial_items)/sizeof(short))
static short player_initial_items[]= 
{ 
	_i_magnum,  // First weapon is the weapon he will use...
	_i_knife,
	_i_knife,
	_i_magnum_magazine, 
	_i_magnum_magazine,
	_i_magnum_magazine,
	
	// LP additions, in case one wants to start very loaded
     // AS: if we want to start loaded, shouldn't it be '_i_bong'?
	_i_knife,
	_i_knife,
	_i_knife,
	_i_knife,
	_i_knife,
	
	_i_knife,
	_i_knife,
	_i_knife,
	_i_knife,
	_i_knife
};
	
#define NUMBER_OF_DAMAGE_RESPONSE_DEFINITIONS (sizeof(damage_response_definitions)/sizeof(struct damage_response_definition))

static struct damage_response_definition damage_response_definitions[]=
{
	{_damage_explosion, 100, _fade_yellow, NONE, _snd_human_scream, _monster_is_dying_hard},
	{_damage_crushing, NONE, _fade_red, NONE, _snd_human_wail, _monster_is_dying_hard},
	{_damage_projectile, NONE, _fade_red, NONE, _snd_human_scream, NONE},
	{_damage_shotgun_projectile, NONE, _fade_red, NONE, _snd_human_scream, NONE},
	{_damage_electrical_staff, NONE, _fade_cyan, NONE, _snd_human_scream, NONE},
	{_damage_hulk_slap, NONE, _fade_cyan, NONE, _snd_human_scream, NONE},
	{_damage_absorbed, 100, _fade_white, _snd_absorbed, NONE, NONE},
	{_damage_teleporter, 100, _fade_white, _snd_absorbed, NONE, NONE},
	{_damage_flame, NONE, _fade_orange, NONE, _snd_human_wail, _monster_is_dying_flaming},
	{_damage_hound_claws, NONE, _fade_red, NONE, _snd_human_scream, NONE},
	{_damage_compiler_bolt, NONE, _fade_static, NONE, _snd_human_scream, NONE},
	{_damage_alien_projectile, NONE, _fade_dodge_purple, NONE, _snd_human_wail, _monster_is_dying_flaming},
	{_damage_hunter_bolt, NONE, _fade_burn_green, NONE, _snd_human_scream, NONE},
	{_damage_fusion_bolt, 60, _fade_negative, NONE, _snd_human_scream, NONE},
	{_damage_fist, 40, _fade_red, NONE, _snd_human_scream, NONE},
	{_damage_yeti_claws, NONE, _fade_burn_cyan, NONE, _snd_human_scream, NONE},
	{_damage_yeti_projectile, NONE, _fade_dodge_yellow, NONE, _snd_human_scream, NONE},
	{_damage_defender, NONE, _fade_purple, NONE, _snd_human_scream, NONE},
	{_damage_lava, NONE, _fade_long_orange, NONE, _snd_human_wail, _monster_is_dying_flaming},
	{_damage_goo, NONE, _fade_long_green, NONE, _snd_human_wail, _monster_is_dying_flaming},
	{_damage_suffocation, NONE, NONE, NONE, _snd_suffocation, _monster_is_dying_soft},
	{_damage_energy_drain, NONE, NONE, NONE, NONE, NONE},
	{_damage_oxygen_drain, NONE, NONE, NONE, NONE, NONE},
	{_damage_hummer_bolt, NONE, _fade_flicker_negative, NONE, _snd_human_scream, NONE},
};

// LP change: made this much bigger than the number of M2/Moo polygons
#define NO_TELEPORTATION_DESTINATION INT16_MAX

// These are all configureable with MML.
struct player_settings_definition player_settings = {
	PLAYER_MAXIMUM_SUIT_ENERGY,    // InitialEnergy
	PLAYER_MAXIMUM_SUIT_OXYGEN,    // InitialOxygen
	PLAYER_MAXIMUM_SUIT_ENERGY/4,  // StrippedEnergy
	PLAYER_MAXIMUM_SUIT_ENERGY,    // SingleEnergy
	2*PLAYER_MAXIMUM_SUIT_ENERGY,  // DoubleEnergy
	3*PLAYER_MAXIMUM_SUIT_ENERGY,  // TripleEnergy
	FIXED_ONE_HALF,                // PlayerSelfLuminosity
	true,                          // CanSwim
	false,                         // PlayerShotsGuided
	QUARTER_CIRCLE/3,              // PlayerHalfVisualArc
	QUARTER_CIRCLE/3,              // PlayerHalfVertVisualArc
	31,                            // PlayerVisualRange
	31,                            // PlayerDarkVisualRange
	1,                             // OxygenDepletion
	0,                             // OxygenReplenishment
	0,                             // OxygenChange
	_damage_fusion_bolt            // Vulnerability
};

// LP: the various powerup item ID's are changeable, but set to appropriate defaults here
struct player_powerup_definition player_powerups = {
	_i_invincibility_powerup,
	_i_invisibility_powerup,
	_i_infravision_powerup,
	_i_extravision_powerup,
	_i_triple_energy_powerup,
	_i_double_energy_powerup,
	_i_energy_powerup,
	_i_oxygen_powerup
};


/* ---------- code */

player_data *get_player_data(
	const size_t player_index)
{
	player_data *data = GetMemberWithBounds(players,player_index,dynamic_world->player_count);
	vassert(data,
		csprintf(temporary, "asked for player #%lu/#%d", player_index, dynamic_world->player_count));
	
	return data;
}



static void StreamToPhysVars(uint8* &S, physics_variables& Object)
{
		StreamToValue(S,Object.head_direction);
		StreamToValue(S,Object.last_direction);
		StreamToValue(S,Object.direction);
		StreamToValue(S,Object.elevation);
		StreamToValue(S,Object.angular_velocity);
		StreamToValue(S,Object.vertical_angular_velocity);	
		StreamToValue(S,Object.velocity);
		StreamToValue(S,Object.perpendicular_velocity);
		StreamToValue(S,Object.last_position.x);
		StreamToValue(S,Object.last_position.y);
		StreamToValue(S,Object.last_position.z);
		StreamToValue(S,Object.position.x);
		StreamToValue(S,Object.position.y);
		StreamToValue(S,Object.position.z);
		StreamToValue(S,Object.actual_height);
		
		StreamToValue(S,Object.adjusted_pitch);
		StreamToValue(S,Object.adjusted_yaw);

		StreamToValue(S,Object.external_velocity.i);
		StreamToValue(S,Object.external_velocity.j);
		StreamToValue(S,Object.external_velocity.k);
		StreamToValue(S,Object.external_angular_velocity);
		
		StreamToValue(S,Object.step_phase);
		StreamToValue(S,Object.step_amplitude);	
		
		StreamToValue(S,Object.floor_height);
		StreamToValue(S,Object.ceiling_height);	
		StreamToValue(S,Object.media_height);
		
		StreamToValue(S,Object.action);
		StreamToValue(S,Object.old_flags);	
		StreamToValue(S,Object.flags);
}

static void PhysVarsToStream(uint8* &S, physics_variables& Object)
{
		ValueToStream(S,Object.head_direction);
		ValueToStream(S,Object.last_direction);
		ValueToStream(S,Object.direction);
		ValueToStream(S,Object.elevation);
		ValueToStream(S,Object.angular_velocity);
		ValueToStream(S,Object.vertical_angular_velocity);	
		ValueToStream(S,Object.velocity);
		ValueToStream(S,Object.perpendicular_velocity);
		ValueToStream(S,Object.last_position.x);
		ValueToStream(S,Object.last_position.y);
		ValueToStream(S,Object.last_position.z);
		ValueToStream(S,Object.position.x);
		ValueToStream(S,Object.position.y);
		ValueToStream(S,Object.position.z);
		ValueToStream(S,Object.actual_height);
		
		ValueToStream(S,Object.adjusted_pitch);
		ValueToStream(S,Object.adjusted_yaw);

		ValueToStream(S,Object.external_velocity.i);
		ValueToStream(S,Object.external_velocity.j);
		ValueToStream(S,Object.external_velocity.k);
		ValueToStream(S,Object.external_angular_velocity);
		
		ValueToStream(S,Object.step_phase);
		ValueToStream(S,Object.step_amplitude);	
		
		ValueToStream(S,Object.floor_height);
		ValueToStream(S,Object.ceiling_height);	
		ValueToStream(S,Object.media_height);
		
		ValueToStream(S,Object.action);
		ValueToStream(S,Object.old_flags);	
		ValueToStream(S,Object.flags);
}


inline void StreamToDamRec(uint8* &S, damage_record& Object)
{
		StreamToValue(S,Object.damage);
		StreamToValue(S,Object.kills);
}

static void DamRecToStream(uint8* &S, damage_record& Object)
{
		ValueToStream(S,Object.damage);
		ValueToStream(S,Object.kills);
}


uint8 *unpack_player_data(uint8 *Stream, player_data *Objects, size_t Count)
{
	uint8* S = Stream;
	player_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->identifier);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->color);
		StreamToValue(S,ObjPtr->team);
		StreamToBytes(S,ObjPtr->name,MAXIMUM_PLAYER_NAME_LENGTH+2);
		
		StreamToValue(S,ObjPtr->location.x);
		StreamToValue(S,ObjPtr->location.y);
		StreamToValue(S,ObjPtr->location.z);
		StreamToValue(S,ObjPtr->camera_location.x);
		StreamToValue(S,ObjPtr->camera_location.y);
		StreamToValue(S,ObjPtr->camera_location.z);	
		StreamToValue(S,ObjPtr->camera_polygon_index);
		StreamToValue(S,ObjPtr->facing);
		StreamToValue(S,ObjPtr->elevation);
		StreamToValue(S,ObjPtr->supporting_polygon_index);
		StreamToValue(S,ObjPtr->last_supporting_polygon_index);
		
		StreamToValue(S,ObjPtr->suit_energy);
		StreamToValue(S,ObjPtr->suit_oxygen);
		
		StreamToValue(S,ObjPtr->monster_index);
		StreamToValue(S,ObjPtr->object_index);
		
		StreamToValue(S,ObjPtr->weapon_intensity_decay);
		StreamToValue(S,ObjPtr->weapon_intensity);
		
		StreamToValue(S,ObjPtr->invisibility_duration);
		StreamToValue(S,ObjPtr->invincibility_duration);
		StreamToValue(S,ObjPtr->infravision_duration);	
		StreamToValue(S,ObjPtr->extravision_duration);
		
		StreamToValue(S,ObjPtr->delay_before_teleport);
		StreamToValue(S,ObjPtr->teleporting_phase);
		StreamToValue(S,ObjPtr->teleporting_destination);
		StreamToValue(S,ObjPtr->interlevel_teleport_phase);
		
		StreamToList(S,ObjPtr->items,NUMBER_OF_ITEMS);
		
		StreamToValue(S,ObjPtr->interface_flags);
		StreamToValue(S,ObjPtr->interface_decay);
		
		StreamToPhysVars(S,ObjPtr->variables);
		
		StreamToDamRec(S,ObjPtr->total_damage_given);
		for (int k=0; k<MAXIMUM_NUMBER_OF_PLAYERS; k++)
			StreamToDamRec(S,ObjPtr->damage_taken[k]);
		StreamToDamRec(S,ObjPtr->monster_damage_taken);
		StreamToDamRec(S,ObjPtr->monster_damage_given);
		
		StreamToValue(S,ObjPtr->reincarnation_delay);
		
		StreamToValue(S,ObjPtr->control_panel_side_index);
		
		StreamToValue(S,ObjPtr->ticks_at_last_successful_save);
		
		StreamToList(S,ObjPtr->netgame_parameters,2);
		
		S += 256*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_data));
	return S;
}
uint8 *pack_player_data(uint8 *Stream, player_data *Objects, size_t Count)
{
	uint8* S = Stream;
	player_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->identifier);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->color);
		ValueToStream(S,ObjPtr->team);
		BytesToStream(S,ObjPtr->name,MAXIMUM_PLAYER_NAME_LENGTH+2);
		
		ValueToStream(S,ObjPtr->location.x);
		ValueToStream(S,ObjPtr->location.y);
		ValueToStream(S,ObjPtr->location.z);
		ValueToStream(S,ObjPtr->camera_location.x);
		ValueToStream(S,ObjPtr->camera_location.y);
		ValueToStream(S,ObjPtr->camera_location.z);	
		ValueToStream(S,ObjPtr->camera_polygon_index);
		ValueToStream(S,ObjPtr->facing);
		ValueToStream(S,ObjPtr->elevation);
		ValueToStream(S,ObjPtr->supporting_polygon_index);
		ValueToStream(S,ObjPtr->last_supporting_polygon_index);
		
		ValueToStream(S,ObjPtr->suit_energy);
		ValueToStream(S,ObjPtr->suit_oxygen);
		
		ValueToStream(S,ObjPtr->monster_index);
		ValueToStream(S,ObjPtr->object_index);
		
		ValueToStream(S,ObjPtr->weapon_intensity_decay);
		ValueToStream(S,ObjPtr->weapon_intensity);
		
		ValueToStream(S,ObjPtr->invisibility_duration);
		ValueToStream(S,ObjPtr->invincibility_duration);
		ValueToStream(S,ObjPtr->infravision_duration);	
		ValueToStream(S,ObjPtr->extravision_duration);
		
		ValueToStream(S,ObjPtr->delay_before_teleport);
		ValueToStream(S,ObjPtr->teleporting_phase);
		ValueToStream(S,ObjPtr->teleporting_destination);
		ValueToStream(S,ObjPtr->interlevel_teleport_phase);
		
		ListToStream(S,ObjPtr->items,NUMBER_OF_ITEMS);
		
		ValueToStream(S,ObjPtr->interface_flags);
		ValueToStream(S,ObjPtr->interface_decay);
		
		PhysVarsToStream(S,ObjPtr->variables);
		
		DamRecToStream(S,ObjPtr->total_damage_given);
		for (int k=0; k<MAXIMUM_NUMBER_OF_PLAYERS; k++)
			DamRecToStream(S,ObjPtr->damage_taken[k]);
		DamRecToStream(S,ObjPtr->monster_damage_taken);
		DamRecToStream(S,ObjPtr->monster_damage_given);
		
		ValueToStream(S,ObjPtr->reincarnation_delay);
		
		ValueToStream(S,ObjPtr->control_panel_side_index);
		
		ValueToStream(S,ObjPtr->ticks_at_last_successful_save);
		
		ListToStream(S,ObjPtr->netgame_parameters,2);
		
		S += 256*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_data));
	return S;
}

short *original_player_initial_items = NULL;
