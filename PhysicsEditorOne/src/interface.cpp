/*
	INTERFACE.C

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

	Thursday, December 30, 1993 6:56:22 PM
	Mac specific code.....

	Friday, July 8, 1994 2:32:44 PM (alain)
		All old code in here is obsolete. This now has interface for the top-level
		interface (Begin Game, etc…)
	Saturday, September 10, 1994 12:45:48 AM  (alain)
		the interface gutted again. just the stuff that handles the menu though, the rest stayed
		the same.
	Thursday, June 8, 1995 2:56:16 PM (ryan)
		Pillaged, raped, & burned. (in that order)

Jan 30, 2000 (Loren Petrich):
	Added some typecasts
	Removed some "static" declarations that conflict with "extern"
	Surrounded choose_saved_game_to_load with "extern "C""

Feb. 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb. 9, 2000 (Loren Petrich):
	Changed NUMBER_OF_INTRO_SCREENS to 3
	Changed NUMBER_OF_CREDIT_SCREENS to Hamish Sinclair's favorite number
	
	Fixed multiple-clicks-necessary problem for too few screens.
	Was in next_game_state(); set game_state.phase (countdown value) to zero.
	
Feb 19, 2000 (Loren Petrich):
	Set the single-player color to the player color set in the preferences,
	for the benefit of chase-cam users.

Mar 5, 2000 (Loren Petrich):
	Added reset_screen() when starting a game, so that extravision
	will not be persistent.

May 13, 2000 (Loren Petrich):
	Added Rhys Hill's fix for problems with quitting OpenGL

Aug 12, 2000 (Loren Petrich):
	Using object-oriented file handler

Aug 24, 2000 (Loren Petrich):
	Added source selector to calculate_picture_clut(), in order to better deal with
	object-oriented file handlers

Nov 25, 2000 (Loren Petrich):
	Added support for movies that start at any level, including at the end of a game.
	Also added end-screen control.

Jan 31, 2001 (Loren Petrich):
	In pause_game(), will stop the liquid faders that are active
	
Jan 25, 2002 (Br'fin (Jeremy Parsons)):
	Disabled network and network microphone calls under Carbon

Feb 27, 2002 (Br'fin (Jeremy Parsons)):
	Renabled network calls, but not microphone calls under Carbon

May 16, 2002 (Woody Zenfell):
    Enforcing standard player behavior with regard to films and netplay
    
Jun 5, 2002 (Loren Petrich):
	Added do-nothing "case _revert_game:" in portable_process_screen_click()
	at the request of Michael Adams.
        
Feb 1, 2003 (Woody Zenfell):
        Reenabling network microphone support on all platforms, trying to share code
        and present consistent interfaces to the greatest degree practical.
        
Feb 8-12, 2003 (Woody Zenfell):
        Introducing support for generalized game startup (will enable resumption of saved-games
        as netgames, among other things).

Feb 13, 2003 (Woody Zenfell):
        We can now resume games as network games.
*/

// NEED VISIBLE FEEDBACK WHEN APPLETALK IS NOT AVAILABLE!!!

/* ZZZ: more on enforcing standard behavior...
    + Standard behavior forced when playing a network game.
    + Standard behavior forced when replaying a film.
    + Custom behavior allowed when starting or restoring a single-player game.
    + No film recorded in single-player if custom behavior != standard behavior.

    Once films and netplay properly record each player's behavior prefs,
    and the relevant code uses per-player settings, this won't be necessary.
    Try a mass-search for "player_behavior" to find the areas affected.
*/

//#include "cseries.h" // sorry ryan, nov. 4
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#ifdef PERFORMANCE
#include <perf.h>

extern TP2PerfGlobals perf_globals;
#endif

#include "map.h"
#include "interface.h"
#include "player.h"
//#include "screen_drawing.h"
#include "mysound.h"
#include "fades.h"
/*
//#include "game_window.h"
//#include "game_errors.h"
//#include "music.h"
//#include "images.h"
#include "screen.h"
#include "network.h"
#include "vbl.h"
#include "shell.h"
#include "preferences.h"
#include "lua_script.h" // PostIdle
*/
#include "FileHandler.h"
/* Change this when marathon changes & replays are no longer valid */
enum recording_version {
	aleph_recording_version= 0,
};
const short default_recording_version= aleph_recording_version;
const short max_handled_recording= aleph_recording_version;

/*#include "screen_definitions.h"
#include "interface_menus.h"

// LP addition: getting OpenGL rendering stuff
#include "render.h"
#include "OGL_Render.h"
#include "alephversion.h"

// To tell it to stop playing,
// and also to run the end-game script
#include "XML_LevelScript.h"

// Network microphone/speaker
#include "network_sound.h"
#include "network_distribution_types.h"
*/
// ZZZ: should the function that uses these (join_networked_resume_game()) go elsewhere?
#include "wad.h"
#include "game_wad.h"

//#include "motion_sensor.h" // for reset_motion_sensor()

#ifdef env68k
	#pragma segment shell
#endif

/* ------------- enums */

/* ------------- constants */
#define DISPLAY_PICT_RESOURCE_TYPE 'PICT'
#define CLOSE_WITHOUT_WARNING_DELAY (5*TICKS_PER_SECOND)

#define NUMBER_OF_INTRO_SCREENS (3)
#define INTRO_SCREEN_DURATION (215) // fudge to align with sound

#ifdef DEMO
#define INTRO_SCREEN_TO_START_SONG_ON (1)
#else
#define INTRO_SCREEN_TO_START_SONG_ON (0)
#endif

#define INTRO_SCREEN_BETWEEN_DEMO_BASE (INTRO_SCREEN_BASE+1) /* +1 to get past the powercomputing */
#define NUMBER_OF_INTRO_SCREENS_BETWEEN_DEMOS (1)
#define DEMO_INTRO_SCREEN_DURATION (10*TICKS_PER_SECOND)

#define TICKS_UNTIL_DEMO_STARTS (30*TICKS_PER_SECOND)

#define NUMBER_OF_PROLOGUE_SCREENS 0
#define PROLOGUE_DURATION (10*TICKS_PER_SECOND)

#define NUMBER_OF_EPILOGUE_SCREENS 1
#define EPILOGUE_DURATION (INDEFINATE_TIME_DELAY)

#define NUMBER_OF_CREDIT_SCREENS 7
#define CREDIT_SCREEN_DURATION (15*60*TICKS_PER_SECOND)

#define NUMBER_OF_CHAPTER_HEADINGS 0
#define CHAPTER_HEADING_DURATION (7*MACHINE_TICKS_PER_SECOND)

// For exiting the Marathon app
// #if defined(DEBUG) || !defined(DEMO)
#define NUMBER_OF_FINAL_SCREENS 0
// #else
// #define NUMBER_OF_FINAL_SCREENS 1
// #endif
#define FINAL_SCREEN_DURATION (INDEFINATE_TIME_DELAY)

/* For teleportation, end movie, etc. */
#define EPILOGUE_LEVEL_NUMBER 256

/* ------------- structures */
struct game_state {
	short state;
	short flags;
	short user;
	long phase;
	long last_ticks_on_idle;
	short current_screen;
	bool suppress_background_tasks;
	bool current_netgame_allows_microphone;
	short main_menu_display_count; // how many times have we shown the main menu?
};

struct screen_data {
	short screen_base;
	short screen_count;
	long duration;
};

/* -------------- constants */
/*struct screen_data display_screens[]= {
	{ INTRO_SCREEN_BASE, NUMBER_OF_INTRO_SCREENS, INTRO_SCREEN_DURATION },
	{ MAIN_MENU_BASE, 1, 0 },
	{ CHAPTER_SCREEN_BASE, NUMBER_OF_CHAPTER_HEADINGS, CHAPTER_HEADING_DURATION },
	{ PROLOGUE_SCREEN_BASE, NUMBER_OF_PROLOGUE_SCREENS, PROLOGUE_DURATION },
	{ EPILOGUE_SCREEN_BASE, NUMBER_OF_EPILOGUE_SCREENS, EPILOGUE_DURATION },
	{ CREDIT_SCREEN_BASE, NUMBER_OF_CREDIT_SCREENS, CREDIT_SCREEN_DURATION},
	{ INTRO_SCREEN_BETWEEN_DEMO_BASE, NUMBER_OF_INTRO_SCREENS_BETWEEN_DEMOS, DEMO_INTRO_SCREEN_DURATION },
	{ FINAL_SCREEN_BASE, NUMBER_OF_FINAL_SCREENS, FINAL_SCREEN_DURATION }
};*/

#if 0
struct chapter_screen_sound_data {
	short level;
	short sound_code;
};

struct chapter_screen_sound_data chapter_screen_sounds[]=
{
	{0, _snd_chapter1},
	{1, _snd_chapter2},
	{2, _snd_chapter3}
};
#define NUMBER_OF_CHAPTER_SCREEN_SOUNDS (sizeof(chapter_screen_sounds)/sizeof(chapter_screen_sounds[1]))
#endif

/* -------------- local globals */
static struct game_state game_state;
static FileSpecifier DraggedReplayFile;
static bool interface_fade_in_progress= false;
static short interface_fade_type;
static short current_picture_clut_depth;
static struct color_table *animated_color_table= NULL;
static struct color_table *current_picture_clut= NULL;

/* -------------- externs */
extern short interface_bit_depth;
extern short bit_depth;

/* ----------- prototypes/PREPROCESS_MAP_MAC.C */
extern bool load_game_from_file(FileSpecifier& File);
extern bool choose_saved_game_to_load(FileSpecifier& File);

/* ---------------------- prototypes */
/*static void display_credits(void);
static void draw_button(short index, bool pressed);
static void handle_replay(bool last_replay);
static bool begin_game(short user, bool cheat);
static void start_game(short user, bool changing_level);
// LP: "static" removed
void handle_load_game(void);
static void handle_save_film(void);
static void finish_game(bool return_to_main_menu);
static void clean_up_after_failed_game(bool inNetgame, bool inRecording, bool inFullCleanup);
static void handle_network_game(bool gatherer);
static void next_game_screen(void);
static void handle_interface_menu_screen_click(short x, short y, bool cheatkeys_down);

static void display_introduction(void);
static void display_loading_map_error(void);
static void display_quit_screens(void);
static void	display_screen(short base_pict_id);
static void display_introduction_screen_for_demo(void);
static void display_epilogue(void);

static void force_system_colors(void);
static bool point_in_rectangle(short x, short y, screen_rectangle *rect);

static void start_interface_fade(short type, struct color_table *original_color_table);
static void update_interface_fades(void);
static void interface_fade_out(short pict_resource_number, bool fade_music);
static bool can_interface_fade_out(void);
static void transfer_to_new_level(short level_number);
static void try_and_display_chapter_screen(short level, bool interface_table_is_valid, bool text_block);

static screen_data *get_screen_data(
	short index);
*/
/* ---------------------- code begins */

