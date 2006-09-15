/*
GAME_WAD.C

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

Sunday, July 3, 1994 10:45:17 PM

Routines for loading an entire game.

Sunday, September 25, 1994 5:03:54 PM  (alain)
	call recalculate_redundant_endpoint_data() upon restoring saved game since
	the redundant data isn't saved.
Sunday, November 6, 1994 5:35:34 PM
	added support for the unified platforms/doors, cleaned up some old code of mine...
Saturday, August 26, 1995 2:28:56 PM
	made portable.

Jan 30, 2000 (Loren Petrich):
	Added some typecasts
	Removed some "static" declarations that conflict with "extern"

Feb 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 6, 2000 (Loren Petrich):
	Added loading and saving of physics models in savegames and from map files

Feb 12, 2000 (Loren Petrich):
	Added MARATHON_INFINITY_DATA_VERSION where appropriate

Feb 14, 2000 (Loren Petrich):
	Added more Pfhorte-friendly error checking to reading in of
	map-info ('Minf') chunk; allowing it to be 2 bytes shorter.

Feb 17, 2000 (Loren Petrich):
	Hides cursor after warning user about loading non-Bungie map files
	(strERRORS, warningExternalMapsFile)

Feb 19, 2000 (Loren Petrich):
	Fixed off-by-one asserts in load_***() routines;

Feb 26, 2000 (Loren Petrich):
	Added chase-cam initialization

June 15, 2000 (Loren Petrich):
	Added supprt for Chris Pruett's Pfhortran

Aug 12, 2000 (Loren Petrich):
	Using object-oriented file handler

Aug 25, 2000 (Loren Petrich):
	Cleared errors (game_errors.c/h) produced by Pfhortran
	and by checking on a scenario's image files

Aug 28, 2000 (Loren Petrich):
	Started on using new pack/unpack routines

Nov 26, 2000 (Loren Petrich):
	Movied a RunLevelScript() before some other stuff, such as entering_map(),
	so that textures to be loaded can be specified before they actually get loaded.

Feb 15, 2002 (Br'fin (Jeremy Parsons)):
	Additional save data is now applied to the Temporary file instead of the original
	(Old level preview info is now saved under Macintosh again)
*/

// This needs to do the right thing on save game, which is storing the precalculated crap.

//#include "cseries.h"

#include <string.h>
#include <stdlib.h>

#include "map.h"
#include "monsters.h"
//#include "network.h"
#include "projectiles.h"
#include "effects.h"
#include "player.h"
/*#include "platforms.h"
#include "flood_map.h"
#include "scenery.h"
*/
#include "lightsource.h"
#include "media.h"
#include "weapons.h"
/*#include "shell.h"
#include "preferences.h"
*/
#include "FileHandler.h"

#include "tags.h"
#include "wad.h"
#include "game_wad.h"
#include "interface.h"
#include "game_errors.h"
#include "mysound.h"
#include "Packing.h"
/*#include "editor.h"
#include "game_window.h"
#include "computer_interface.h" // for loading/saving terminal state.
#include "images.h"
#include "shell.h"
#include "preferences.h"

// LP change: added chase-cam init and render allocation
#include "ChaseCam.h"
#include "render.h"

#include "XML_LevelScript.h"

// For packing and unpacking some of the stuff

#include "motion_sensor.h"	// ZZZ for reset_motion_sensor()

#ifdef env68k
#pragma segment file_io
#endif

// unify the save game code into one structure.

/* -------- local globals */
FileSpecifier MapFileSpec;
static bool file_is_set= false;

// LP addition: was a physics model loaded from the previous level loaded?
static bool PhysicsModelLoadedEarlier = false;

// The following local globals are for handling games that need to be restored.
struct revert_game_info
{
	bool game_is_from_disk;
	struct game_data game_information;
	struct player_start_data player_start;
	struct entry_point entry_point;
	FileSpecifier SavedGame;
};
static struct revert_game_info revert_game_data;


static uint8 *unpack_directory_data(uint8 *Stream, directory_data *Objects, size_t Count);
//static uint8 *pack_directory_data(uint8 *Stream, directory_data *Objects, int Count);



/*
 *  Unpacking/packing functions
 */

static uint8 *unpack_directory_data(uint8 *Stream, directory_data *Objects, size_t Count)
{
	uint8* S = Stream;
	directory_data* ObjPtr = Objects;

	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->mission_flags);
		StreamToValue(S,ObjPtr->environment_flags);
		StreamToValue(S,ObjPtr->entry_point_flags);
		StreamToBytes(S,ObjPtr->level_name,LEVEL_NAME_LENGTH);
	}

	assert((S - Stream) == SIZEOF_directory_data);
	return S;
}

// ZZZ: gnu cc swears this is currently unused, and I don't see any sneaky #includes that might need it...
/*
static uint8 *pack_directory_data(uint8 *Stream, directory_data *Objects, int Count)
{
	uint8* S = Stream;
	directory_data* ObjPtr = Objects;

	for (int k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->mission_flags);
		ValueToStream(S,ObjPtr->environment_flags);
		ValueToStream(S,ObjPtr->entry_point_flags);
		BytesToStream(S,ObjPtr->level_name,LEVEL_NAME_LENGTH);
	}

	assert((S - Stream) == SIZEOF_directory_data);
	return S;
}
*/
