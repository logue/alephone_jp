#ifndef __PHYSICS_MODELS_H
#define __PHYSICS_MODELS_H
#include "stdafx.h"
#include "world.h"

/*
PHYSICS_MODELS.H

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

Tuesday, May 31, 1994 5:18:35 PM
*/

/* ---------- constants */

enum /* models */
{
	_model_game_walking,
	_model_game_running,
	NUMBER_OF_PHYSICS_MODELS
};

/* ---------- structures */

struct physics_constants
{
	_fixed maximum_forward_velocity, maximum_backward_velocity, maximum_perpendicular_velocity;
	_fixed acceleration, deceleration, airborne_deceleration; /* forward, backward and perpendicular */
	_fixed gravitational_acceleration, climbing_acceleration, terminal_velocity;
	_fixed external_deceleration;
	
	_fixed angular_acceleration, angular_deceleration, maximum_angular_velocity, angular_recentering_velocity;
	_fixed fast_angular_velocity, fast_angular_maximum; /* for head movements */
	_fixed maximum_elevation; /* positive and negative */
	_fixed external_angular_deceleration;
	
	/* step_length is distance between adjacent nodes in the actor’s phase */
	_fixed step_delta, step_amplitude;
	_fixed radius, height, dead_height, camera_height, splash_height;
	
	_fixed half_camera_separation;
};

/* ---------- globals */

extern struct physics_constants physics_models[NUMBER_OF_PHYSICS_MODELS];

// Added for the convenience of the 1-2-3 Converter
uint8 *unpack_physics_constants(uint8 *Stream, physics_constants *Objects, size_t Count);
uint8 *pack_physics_constants(uint8 *Stream, physics_constants *Objects, size_t Count);

#endif

