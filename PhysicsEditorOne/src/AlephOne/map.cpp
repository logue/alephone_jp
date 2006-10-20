#include "stdafx.h"
#include "header.h"
/*
MAP.C

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

Sunday, August 15, 1993 12:13:52 PM

Tuesday, December 7, 1993 9:35:13 AM
	fixed bug in map_index_to_map_point (removed bitwise exclusive-ors).
Sunday, January 2, 1994 10:53:34 PM
	transmogrify_object_shape plays sounds now.
Wednesday, March 9, 1994 4:34:40 PM
	support for lightsourcing/mapping floor ceiling with polygons.
Monday, June 27, 1994 6:52:10 PM
	ajr--push_out_line now takes the length of the line instead of calculating it.
Friday, December 9, 1994 1:31:09 PM  (Jason)
	translate_map_object moves objects leaving the map into the center of their polygon.
Friday, June 9, 1995 2:25:33 PM  (Jason)
	sounds on the other side of a media boundary are obstructed
Monday, September 18, 1995 4:38:30 PM  (Jason)
	the old sound_index is now the landscape_index for a given level

Jan 30, 2000 (Loren Petrich):
	Added some typecasts

Feb 4, 2000 (Loren Petrich):
	Renamed the "pathways/marathon" environment
	Changed halt() to assert(false) for better debugging

Feb 13, 2000 (Loren Petrich):
	Added some idiot-proofing to the tick count in animate_object().

Feb 15, 2000 (Loren Petrich):
	Suppressed some assertions designed to check for map consistency;
	this is to get around some Pfhorte bugs.

Feb 17, 2000 (Loren Petrich):
	Fixed stuff near arctangent() to be long-distance-friendly

Feb 20, 2000 (Loren Petrich): Suppressed height-consistency check in
	change_polygon_height().

Apr 28, 2000 (Loren Petrich): In animate_object(), switched the two tests
	on the current frame so that the Pfhor can teleport out in
	M2's "Charon Doesn't Make Change".

Jul 6, 2000 (Loren Petrich): Readjusted the frame checking yet again, so that both keyframe = 0
	and keyframe = [number of frames] would be detected.

Jul 7, 2000 (Loren Petrich): Did yet another frame-checking readjustment, in order to suppress
	the reactivated Hunter soft-death bug.

Aug 20, 2000 (Loren Petrich): eliminated a "pause()" statement -- some debugging statement?
	
Oct 13, 2000 (Loren Petrich):
	Converted the intersected-objects list into a Standard Template Library vector

Oct 19, 2000 (Loren Petrich):
	Changed get_object_shape_and_transfer_mode() so that it makes data->collection_code equal to NONE
	if it does not find a valid sequence or view.
	
Nov 19, 2000 (Loren Petrich):
	Added XML support for texture-loading control. This contains a switch to indicate whether to load
	the landscape textures, and also stuff for loading the various texture environments.
	Each one of these has slots for several collection ID's to load; one can use a converted M1 map
	directly with this approach.

Feb 8, 2001 (Loren Petrich):
	Had not too long ago changed many of the arrays into dynamically-allocated ones, thus ending the
	limits on the numbers of points, lines, polygons, etc.
	Fixed a *serious* bug in the calculation of the "dynamic world" quantities in recalculate_map_counts() --
	there are some count-down loops, but they ought to count down to the last used entity, not the last unused one.

Feb 3, 2003 (Loren Petrich):
	In attach_parasitic_object(), will transmit the sizing of the host object to the parasite.

 June 14, 2003 (Woody Zenfell):
	New functions for manipulating polygons' object lists (in support of prediction).
 */

/*
find_line_crossed leaving polygon could be sped up considerable by reversing the search direction in some circumstances

//find_line_crossed_leaving_polygon() does weird things when walking along a gridline
//keep_line_segment_out_of_walls() can slide the player slowly along a wall
*/

//#include "cseries.h"
#include "map.h"
//#include "interface.h"
#include "monsters.h"
//#include "preferences.h"
#include "projectiles.h"
#include "effects.h"
#include "player.h"
/*#include "platforms.h"
#include "lightsource.h"
#include "media.h"
#include "mysound.h"
*/
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include <list>

#ifdef env68k
#pragma segment map
#endif

/* ---------- structures */

/*
struct environment_definition
{
	short *shape_collections; *//* NONE terminated *//*
};
*/

/* ---------- constants */

#define DEFAULT_MAP_MEMORY_SIZE (128*KILO)

/* ---------- globals */

// LP: modified texture-environment management so as to be easier to handle with XML

const int NUMBER_OF_ENVIRONMENTS = 5;
const int NUMBER_OF_ENV_COLLECTIONS = 7;

static short Environments[NUMBER_OF_ENVIRONMENTS][NUMBER_OF_ENV_COLLECTIONS] = 
{
	{_collection_walls1, _collection_scenery1, NONE, NONE, NONE, NONE, NONE},	// Lh'owon Water
	{_collection_walls2, _collection_scenery2, NONE, NONE, NONE, NONE, NONE},	// Lh'owon Lava
	{_collection_walls3, _collection_scenery3, NONE, NONE, NONE, NONE, NONE},	// Lh'owon Sewage
	{_collection_walls4, _collection_scenery4, NONE, NONE, NONE, NONE, NONE},	// Jjaro (originally to be Pathways or Marathon)
	{_collection_walls5, _collection_scenery5, NONE, NONE, NONE, NONE, NONE}	// Pfhor
};

/*
static short e1[]= {_collection_walls1, _collection_scenery1, NONE}; // lh’owon
static short e2[]= {_collection_walls2, _collection_scenery2, NONE}; // lh’owon
static short e3[]= {_collection_walls3, _collection_scenery3, NONE}; // lh’owon
static short e4[]= {_collection_walls4, _collection_scenery4, NONE}; // pathways (or marathon) (LP: jjaro)
static short e5[]= {_collection_walls5, _collection_scenery5, NONE}; // pfhor ship

#define NUMBER_OF_ENVIRONMENTS (sizeof(environment_definitions)/sizeof(struct environment_definition))
static struct environment_definition environment_definitions[]=
{
	{e1},
	{e2},
	{e3},
	{e4},
	{e5}
};
*/

/* ---------- map globals */

// Turned some of these lists into variable arrays;
// took over their maximum numbers as how many of them

struct static_data *static_world = NULL;
struct dynamic_data *dynamic_world = NULL;

// These are allocated here because the numbers of these objects vary as a game progresses.
vector<effect_data> EffectList(MAXIMUM_EFFECTS_PER_MAP);
vector<object_data> ObjectList(MAXIMUM_OBJECTS_PER_MAP);
vector<monster_data> MonsterList(MAXIMUM_MONSTERS_PER_MAP);
vector<projectile_data> ProjectileList(MAXIMUM_PROJECTILES_PER_MAP);
// struct object_data *objects = NULL;
// struct monster_data *monsters = NULL;
// struct projectile_data *projectiles = NULL;

/*vector<endpoint_data> EndpointList;
vector<line_data> LineList;
vector<side_data> SideList;
vector<polygon_data> PolygonList;
vector<platform_data> PlatformList;
*/
// struct polygon_data *map_polygons = NULL;
// struct side_data *map_sides = NULL;
// struct line_data *map_lines = NULL;
// struct endpoint_data *map_endpoints = NULL;
// struct platform_data *platforms = NULL;

vector<ambient_sound_image_data> AmbientSoundImageList;
vector<random_sound_image_data> RandomSoundImageList;
// struct ambient_sound_image_data *ambient_sound_images = NULL;
// struct random_sound_image_data *random_sound_images = NULL;

vector<int16> MapIndexList;
// short *map_indexes = NULL;

vector<uint8> AutomapLineList;
vector<uint8> AutomapPolygonList;
// byte *automap_lines = NULL;
// byte *automap_polygons = NULL;

vector<map_annotation> MapAnnotationList;
// struct map_annotation *map_annotations = NULL;

vector<map_object> SavedObjectList;
// struct map_object *saved_objects = NULL;
struct item_placement_data *placement_information = NULL;

bool game_is_networked = false;

// This could be a handle
struct map_memory_data {
	byte *memory;
	long size;
	long index;
};

// static struct map_memory_data map_structure_memory;

// LP addition: growable list of intersected objects
static vector<short> IntersectedObjects;

// Whether or not Marathon 2/oo landscapes had been loaded (switch off for Marathon 1 compatibility)
bool LandscapesLoaded = true;

// The index number of the first texture loaded (should be the main wall texture);
// needed for infravision fog when landscapes are switched off
short LoadedWallTexture = NONE;

/* ---------- private prototypes */


/* ---------- code */

