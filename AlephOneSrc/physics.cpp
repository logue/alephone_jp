//#include "stdafx.h"
#include "map.h"
/*
PHYSICS.C

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

Wednesday, May 11, 1994 9:32:16 AM

Saturday, May 21, 1994 11:36:31 PM
	missing effects due to map (i.e., gravity and collision detection).  last day in san
	jose after WWDC.
Sunday, May 22, 1994 11:14:55 AM
	there are two viable methods of running a synchronized network game.  the first is doom's,
	where each player shares with each other player only his control information for that tick
	(this imposes a maximum frame rate, as the state-of-the-world will be advanced at the same
	time on all machines).  the second is the continuous lag-tolerant model where each player
	shares absolute information with each other player as often as possible and local machines
	do their best at guessing what everyone else in the game is doing until they get better
	information.  whichever choice is made will change the physics drastically.  we're going to
	take the latter approach, and cache the KeyMap at interrupt time to be batch-processed
	later at frame time.

Feb. 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 6, 2000 (Loren Petrich):
	Added access to size of physics-definition structure

Feb 20, 2000 (Loren Petrich):
	Fixed chase-cam behavior: DROP_DEAD_HEIGHT is effectively zero for it.
	Also, set up-and-down bob to zero when it is active.

Aug 31, 2000 (Loren Petrich):
	Added stuff for unpacking and packing

May 16, 2002 (Woody Zenfell):
    Letting user decide whether to auto-recenter when running

 June 14, 2003 (Woody Zenfell):
	update_player_physics_variables() can now operate in a reduced-impact mode
		that changes less of the game state.  Useful for partial-game-state
		save-and-restore code (as used by prediction mechanism).
*/

/*
running backwards shouldn’t mean doom in a fistfight

//who decides on the physics model, anyway?  static_world-> or player->
//falling through gridlines and crapping on elevators has to do with variables->flags being wrong after the player dies
//absolute (or nearly-absolute) positioning information for yaw, pitch and velocity
//the physics model is too soft (more noticable at high frame rates)
//we can continually boot ourselves out of nearly-orthogonal walls by tiny amounts, resulting in a slide
//it’s fairly obvious that players can still end up in walls
//the recenter key should work faster
*/

#ifdef DEBUG
//#define DIVERGENCE_CHECK
#endif

/*#include "cseries.h"
#include "render.h"
#include "map.h"
*/
#include "player.h"
//#include "interface.h"
#include "monsters.h"

//#include "media.h"

// LP addition:
//#include "ChaseCam.h"
#include "Packing.h"

#include <string.h>

#ifdef env68k
#pragma segment player
#endif

/* ---------- constants */

#define COEFFICIENT_OF_ABSORBTION 2
#define SMALL_ENOUGH_VELOCITY (constants->climbing_acceleration)
#define CLOSE_ENOUGH_TO_FLOOR WORLD_TO_FIXED(WORLD_ONE/16)

#define AIRBORNE_HEIGHT WORLD_TO_FIXED(WORLD_ONE/16)

// LP change: drop-dead height is effectively zero when the chase-cam is on;
// this keeps it from dropping.
#define DROP_DEAD_HEIGHT WORLD_TO_FIXED(ChaseCam_IsActive() ? 0 : WORLD_ONE_HALF)

#define FLAGS_WHICH_PREVENT_RECENTERING (_turning|_looking|_sidestepping|_looking_vertically|_look_dont_turn|_sidestep_dont_turn)

/* ---------- private prototypes */


/* ---------- globals */

/* import constants, structures and globals for physics models */
#include "physics_models.h"

/* ---------- code */

#ifdef DIVERGENCE_CHECK
#define SAVED_POINT_COUNT 8192
static world_point3d *saved_points;
static angle *saved_thetas;
static short saved_point_count, saved_point_iterations= 0;
static bool saved_divergence_warning;
#endif



uint8 *unpack_physics_constants(uint8 *Stream, size_t Count)
{
	return unpack_physics_constants(Stream,physics_models,Count);
}

uint8 *unpack_physics_constants(uint8 *Stream, physics_constants *Objects, size_t Count)
{
	uint8* S = Stream;
	physics_constants* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->maximum_forward_velocity);
		StreamToValue(S,ObjPtr->maximum_backward_velocity);
		StreamToValue(S,ObjPtr->maximum_perpendicular_velocity);
		StreamToValue(S,ObjPtr->acceleration);
		StreamToValue(S,ObjPtr->deceleration);
		StreamToValue(S,ObjPtr->airborne_deceleration);
		StreamToValue(S,ObjPtr->gravitational_acceleration);
		StreamToValue(S,ObjPtr->climbing_acceleration);
		StreamToValue(S,ObjPtr->terminal_velocity);
		StreamToValue(S,ObjPtr->external_deceleration);

		StreamToValue(S,ObjPtr->angular_acceleration);
		StreamToValue(S,ObjPtr->angular_deceleration);
		StreamToValue(S,ObjPtr->maximum_angular_velocity);
		StreamToValue(S,ObjPtr->angular_recentering_velocity);
		StreamToValue(S,ObjPtr->fast_angular_velocity);
		StreamToValue(S,ObjPtr->fast_angular_maximum);
		StreamToValue(S,ObjPtr->maximum_elevation);
		StreamToValue(S,ObjPtr->external_angular_deceleration);
		
		StreamToValue(S,ObjPtr->step_delta);
		StreamToValue(S,ObjPtr->step_amplitude);
		StreamToValue(S,ObjPtr->radius);
		StreamToValue(S,ObjPtr->height);
		StreamToValue(S,ObjPtr->dead_height);
		StreamToValue(S,ObjPtr->camera_height);
		StreamToValue(S,ObjPtr->splash_height);
		
		StreamToValue(S,ObjPtr->half_camera_separation);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_physics_constants));
	return S;
}

uint8 *pack_physics_constants(uint8 *Stream, size_t Count)
{
	return pack_physics_constants(Stream,physics_models,Count);
}

uint8 *pack_physics_constants(uint8 *Stream, physics_constants *Objects, size_t Count)
{
	uint8* S = Stream;
	physics_constants* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->maximum_forward_velocity);
		ValueToStream(S,ObjPtr->maximum_backward_velocity);
		ValueToStream(S,ObjPtr->maximum_perpendicular_velocity);
		ValueToStream(S,ObjPtr->acceleration);
		ValueToStream(S,ObjPtr->deceleration);
		ValueToStream(S,ObjPtr->airborne_deceleration);
		ValueToStream(S,ObjPtr->gravitational_acceleration);
		ValueToStream(S,ObjPtr->climbing_acceleration);
		ValueToStream(S,ObjPtr->terminal_velocity);
		ValueToStream(S,ObjPtr->external_deceleration);

		ValueToStream(S,ObjPtr->angular_acceleration);
		ValueToStream(S,ObjPtr->angular_deceleration);
		ValueToStream(S,ObjPtr->maximum_angular_velocity);
		ValueToStream(S,ObjPtr->angular_recentering_velocity);
		ValueToStream(S,ObjPtr->fast_angular_velocity);
		ValueToStream(S,ObjPtr->fast_angular_maximum);
		ValueToStream(S,ObjPtr->maximum_elevation);
		ValueToStream(S,ObjPtr->external_angular_deceleration);
		
		ValueToStream(S,ObjPtr->step_delta);
		ValueToStream(S,ObjPtr->step_amplitude);
		ValueToStream(S,ObjPtr->radius);
		ValueToStream(S,ObjPtr->height);
		ValueToStream(S,ObjPtr->dead_height);
		ValueToStream(S,ObjPtr->camera_height);
		ValueToStream(S,ObjPtr->splash_height);
		
		ValueToStream(S,ObjPtr->half_camera_separation);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_physics_constants));
	return S;
}


// LP addition: get number of physics models (restricted sense)
size_t get_number_of_physics_models() {return NUMBER_OF_PHYSICS_MODELS;}

struct physics_constants physics_models[NUMBER_OF_PHYSICS_MODELS]=
{
	/* game walking */
	{
		FIXED_ONE/14, FIXED_ONE/17, FIXED_ONE/20, /* max forward, backward and perpendicular velocity */
		FIXED_ONE/200, FIXED_ONE/100, FIXED_ONE/180, /* acceleration, deceleration, airborne deceleration */
		FIXED_ONE/400, FIXED_ONE/300, FIXED_ONE/7, /* gravity, normal acceleration, terminal velocity */
		FIXED_ONE/200, /* external deceleration */
	
		(5*FIXED_ONE)/8, (5*FIXED_ONE)/4, 6*FIXED_ONE, (3*FIXED_ONE)/4, /* angular acceleration, deceleration, max */
		QUARTER_CIRCLE*FIXED_ONE/6, QUARTER_CIRCLE*FIXED_ONE, /* fast angular v, max */
		QUARTER_CIRCLE*FIXED_ONE/3, /* maximum elevation */
		FIXED_ONE/3, /* external angular deceleration */
	
		FIXED_ONE/20, FIXED_ONE/10, /* step delta, step amplitude */
		FIXED_ONE/4, (4*FIXED_ONE)/5, FIXED_ONE/4, (1*FIXED_ONE)/5, /* radius, height, dead height, viewpoint height */
		FIXED_ONE/2, /* splash height */
		FIXED_ONE/32 /* camera separation */
	},

	/* game running */
	{
		FIXED_ONE/8, FIXED_ONE/12, FIXED_ONE/13, /* max forward, backward and perpendicular velocity */
		FIXED_ONE/100, FIXED_ONE/50, FIXED_ONE/180, /* acceleration, deceleration, airborne deceleration */
		FIXED_ONE/400, FIXED_ONE/200, FIXED_ONE/7, /* gravity, normal acceleration, terminal velocity */
		FIXED_ONE/200, /* external deceleration */
	
		(5*FIXED_ONE)/4, (5*FIXED_ONE)/2, 10*FIXED_ONE, (3*FIXED_ONE)/2, /* angular acceleration, deceleration, max */
		QUARTER_CIRCLE*FIXED_ONE/6, QUARTER_CIRCLE*FIXED_ONE, /* fast angular v, max */
		QUARTER_CIRCLE*FIXED_ONE/3, /* maximum elevation */
		FIXED_ONE/3, /* external angular deceleration */
	
		FIXED_ONE/20, FIXED_ONE/10, /* step delta, step amplitude */
		FIXED_ONE/4, (4*FIXED_ONE)/5, FIXED_ONE/4, (1*FIXED_ONE)/5, /* radius, height, dead height, viewpoint height */
		FIXED_ONE/2, /* splash height */
		FIXED_ONE/32 /* camera separation */
	},
};
