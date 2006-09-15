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

//static bool test_item_retrieval(short polygon_index1, world_point3d *location1, world_point3d *location2);

static long item_trigger_cost_function(short source_polygon_index, short line_index,
	short destination_polygon_index, void *unused);

/* ---------- code */
static bool get_item(
	short player_index,
	short object_index) 
{
	struct object_data *object= get_object_data(object_index);	
	bool success;

	assert(GET_OBJECT_OWNER(object)==_object_is_item);
	
	//success= try_and_add_player_item(player_index, object->permutation);
	if (success)
	{
		/* remove it */
		remove_map_object(object_index);
	}
	
	return success;
}

// Item-definition accessor
item_definition *get_item_definition(
	const short type)
{
	return GetMemberWithBounds(item_definitions,type,NUMBER_OF_DEFINED_ITEMS);
}

//a non-inlined version for external use
item_definition *get_item_definition_external(
	const short type)
{
	return get_item_definition(type);
}

short new_item(
	struct object_location *location,
	short type)
{
	short object_index;
	struct item_definition *definition= get_item_definition(type);
	// LP change: added idiot-proofing
	if (!definition) return false;
	
	bool add_item= true;

	assert(sizeof(item_definitions)/sizeof(struct item_definition)==NUMBER_OF_DEFINED_ITEMS);

	/* Do NOT add items that are network-only in a single player game, and vice-versa */
	if (dynamic_world->player_count>1)
	{
		if (definition->invalid_environments & _environment_network) add_item= false;
		//if (get_item_kind(type)==_ball && !current_game_has_balls()) add_item= false;
	} 
	else
	{
		if (definition->invalid_environments & _environment_single_player) add_item= false;
	}

	if (add_item)
	{
		/* add the object to the map */
		object_index= new_map_object(location, definition->base_shape);
		if (object_index!=NONE)
		{
			struct object_data *object= get_object_data(object_index);
			
			// LP addition: using the facing direction as a flag in the "unanimated" case:
			// will be initially zero, but will become nonzero when initialized,
			// so that the shape randomization will be done only once.
			
			SET_OBJECT_OWNER(object, _object_is_item);
			object->permutation= type;
			
			if ((location->flags&_map_object_is_network_only) && dynamic_world->player_count<=1)
			{
//				dprintf("killed #%d;g;", type);
				SET_OBJECT_INVISIBILITY(object, true);
				object->permutation= NONE;
			}
			
			/* let PLACEMENT.C keep track of how many there are */
			object_was_just_added(_object_is_item, type);
			// and let Lua know too
			//L_Call_Item_Created(object_index);
 		}
	}
	else
	{
		object_index= NONE;
	}
	
	return object_index;
}


void get_item_name(
	char *buffer,
	short item_id,
	bool plural)
{
	struct item_definition *definition= get_item_definition(item_id);
	// LP change: added idiot-proofing
	if (!definition)
	{
		if (plural)
			sprintf(buffer,"Unlisted items with ID %d",item_id);
		else
			sprintf(buffer,"Unlisted item with ID %d",item_id);
		
		return;
	}
	
	getcstr(buffer, strITEM_NAME_LIST, plural ? definition->plural_name_id :
		definition->singular_name_id);
}

void get_header_name(
	char *buffer,
	short type)
{
	getcstr(buffer, strHEADER_NAME_LIST, type);
}
short count_inventory_lines(
	short player_index)
{
	struct player_data *player= get_player_data(player_index);
	bool types[NUMBER_OF_ITEM_TYPES];
	short count= 0;
	short loop;
	
	/* Clean out the header array, so we can count properly */
	for(loop=0; loop<NUMBER_OF_ITEM_TYPES; ++loop)
	{
		types[loop]= false;
	}
	
	for(loop=0; loop<NUMBER_OF_DEFINED_ITEMS; ++loop)
	{
		if (loop==_i_knife) continue;
		if (player->items[loop] != NONE)
		{
			count++;
			types[get_item_kind(loop)]= true;
		}
	}
	
	/* Now add in the header lines.. */
	for(loop= 0; loop<NUMBER_OF_ITEM_TYPES; ++loop)
	{
		if(types[loop]) count++;
	}
	
	return count;
}
/*
void swipe_nearby_items(
	short player_index)
/*
void mark_item_collections(
	bool loading)
{
	mark_collection(_collection_items, loading);
}
*/
bool unretrieved_items_on_map(
	void)
{
	bool found_item= false;
	struct object_data *object;
	short object_index;
	
	for (object_index= 0, object= objects; object_index<MAXIMUM_OBJECTS_PER_MAP; ++object_index, ++object)
	{
		if (SLOT_IS_USED(object) && GET_OBJECT_OWNER(object)==_object_is_item)
		{
			if (get_item_kind(object->permutation)==_item)
			{
				found_item= true;
				break;
			}
		}
	}
	
	return found_item;
}

bool item_valid_in_current_environment(
	short item_type)
{
	bool valid= true;
	struct item_definition *definition= get_item_definition(item_type);
	// LP change: added idiot-proofing
	if (!definition) return false;
	
	if (definition->invalid_environments & static_world->environment_flags)
	{
		valid= false;
	}
	
	return valid;
}

short get_item_kind(
	short item_id)
{
	struct item_definition *definition= get_item_definition(item_id);
	// LP change: added idiot-proofing
	if (!definition) return NONE;
	
	return definition->item_kind;
}

