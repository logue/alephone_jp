/*
ITEMS.C

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

Monday, January 3, 1994 10:06:08 PM

Monday, September 5, 1994 2:17:43 PM
	razed.
Friday, October 21, 1994 3:44:11 PM
	changed inventory updating mechanism, added maximum counts of items.
Wednesday, November 2, 1994 3:49:57 PM (Jason)
	object_was_just_destroyed is now called immediately on powerups.
Tuesday, January 31, 1995 1:24:10 PM  (Jason')
	can only hold unlimited ammo on total carnage (not everything)
Wednesday, October 11, 1995 3:10:34 PM  (Jason)
	network-only items

Feb 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 15, 2000 (Loren Petrich):
	Added item-animation handling
	Non-animated items ought to be randomized, but one problem is that
	randomize_object_sequence() only works when the shapes are loaded,
	and the shapes are usually not loaded when the map items are created.

May 16, 2000 (Loren Petrich):
	Added XML support for configuring various item features

May 26, 2000 (Loren Petrich):
	Added XML shapes support

Jul 1, 2000 (Loren Petrich):
	Did some inlining of the item-definition accessor
	
	Added Benad's netgame-type changes

Aug 10, 2000 (Loren Petrich):
	Added Chris Pruett's Pfhortran changes

Feb 11, 2001 (Loren Petrich):
	Reversed the "polarity" of the "facing" member of "object",
	which is used as a flag in the case of randomized unanimated objects.
	It will become NONE when these objects are inited.
*/

//#include "cseries.h"

#include "map.h"
#include "interface.h"
#include "monsters.h"
#include "player.h"
#include "mysound.h"
/*#include "platforms.h"
#include "fades.h"
*/
#include "items.h"
//#include "flood_map.h"
#include "effects.h"
//#include "game_window.h"
#include "weapons.h" /* needed for process_new_item_for_reloading */
//#include "network_games.h"

// LP addition: for the XML stuff
//#include <string.h>
//#include <limits.h>
//#include "ShapesParser.h"

//CP addition: Scripting Hooks
//#include "scripting.h"

//MH: Lua scripting
//#include "lua_script.h"

#ifdef env68k
#pragma segment marathon
#endif

/* ---------- structures */

#define strITEM_NAME_LIST 150
#define strHEADER_NAME_LIST 151

#define MAXIMUM_ARM_REACH (3*WORLD_ONE_FOURTH)

/* ---------- private prototypes */

/* ---------- globals */

#include "item_definitions.h"

/* ---------- private prototypes */

// Item-definition accessor
static item_definition *get_item_definition(
	const short type);

static bool get_item(short player_index, short object_index);

static bool test_item_retrieval(short polygon_index1, world_point3d *location1, world_point3d *location2);

static long item_trigger_cost_function(short source_polygon_index, short line_index,
	short destination_polygon_index, void *unused);

/* ---------- code */

