#include "stdafx.h"
/*

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

Feb 10, 2000 (Loren Petrich):
	Here is all the behind-the-scenes stuff for getting the dynamic limits.

Feb 14, 2000 (Loren Petrich):
	Changed it to read 'DLim' resource 128

Feb 19, 2000 (Loren Petrich):
	Added local and global monster-buffer upper limits (collision checking)
*/

//#include "cseries.h"

#include <string.h>

#include "dynamic_limits.h"
/*#include "map.h"*/
#include "effects.h"
#include "monsters.h"
#include "projectiles.h"
//#include "flood_map.h"

// Reasonable defaults;
// the original ones are in []'s
static uint16 dynamic_limits[NUMBER_OF_DYNAMIC_LIMITS] =
{
	1024,	// [384] Objects (every possible kind)
	 512,	// [220] NPC's
	 128,	// [20] Paths for NPC's to follow (determines how many may be active)
	 128,	// [64] Projectiles
	 128,	// [64] Currently-active effects (blood splatters, explosions, etc.)
	1024,	// [72] Number of objects to render
	  64,	// [16] Local collision buffer (target visibility, NPC-NPC collisions, etc.)
	 256	// [64] Global collision buffer (projectiles with other objects)
};

uint16 *original_dynamic_limits = NULL;

// Accessor
uint16 get_dynamic_limit(int which) {
	return dynamic_limits[which];
}
