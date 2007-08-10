#ifndef __SCENERY_DEFINITIONS_H
#define __SCENERY_DEFINITIONS_H

/*
SCENERY_DEFINITIONS.H

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

Sunday, September 25, 1994 4:05:35 AM  (Jason')

Feb 4, 2000 (Loren Petrich):
	Added Jjaro scenery; used Anvil for nomenclature
	Not making Jjaro lamps destroyable right away;
	That could be done by making (effect = NONE) in effects.c make the breaking-glass sound
*/

/* ---------- constants */
#include "effects.h"
#include "scenery.h"

enum
{
	_scenery_is_solid= 0x0001,
	_scenery_is_animated= 0x0002,
	_scenery_can_be_destroyed= 0x0004
};

/* ---------- structures */

struct scenery_definition
{
	uint16 flags;
	shape_descriptor shape;
	
	world_distance radius, height;
	
	int16 destroyed_effect;
	shape_descriptor destroyed_shape;
};

/* ---------- globals */

#define NUMBER_OF_SCENERY_DEFINITIONS (sizeof(scenery_definitions)/sizeof(struct scenery_definition))

extern struct scenery_definition scenery_definitions[61];
#endif
