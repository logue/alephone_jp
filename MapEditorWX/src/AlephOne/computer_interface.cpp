/*
	computer_interface.c

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

	Monday, May 8, 1995 7:18:55 PM- rdm created.

Feb 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 16, 2000 (Loren Petrich):
	Set up for more graceful degradation when
	there is no terminal data in a map;
	also had get_indexed_terminal_data() return NULL
	if terminal data could not be found.

Feb 18, 2000 (Loren Petrich):
	Suppressed all the dprintf warnings, such as one for a picture being
	too large for a terminal.

Feb 19, 2000 (Loren Petrich):
	Had a frustrating time getting get_date_string() to work properly;
	SecondsToDate() seems to be broken.

Feb 21, 2000 (Loren Petrich):
	Corrected a troublesome assert in find_checkpoint_location()
	Moved drawing of borders to after drawing of other stuff,
	to fix checkpoint-overdraw bug.

Feb 26, 2000 (Loren Petrich):
	Fixed level-0 teleportation bug; the hack is to move the destination
	down by 1.
	
	Set font in PICT-error-message code to "systemFont".

Mar 5, 2000 (Loren Petrich):
	Improved handling of clipping in _render_computer_interface();
	it is trimmed to the terminal window when rendering there, and restored
	to the screen's full size when leaving.

May 11, 2000 (Loren Petrich):
	Suppressed vhalts here; these were for unrecognized terminal states.
	Changed them into vwarns.

May 20, 2000 (Loren Petrich):
	Put in more graceful degradation for
	get_indexed_grouping()
	get_indexed_font_changes()
	These will return NULL for an invalid index

July 5, 2000 (Loren Petrich):
	Using world_pixels instead of screen_window

Aug 10, 2000 (Loren Petrich):
	Added Chris Pruett's Pfhortran changes

Aug 22, 2000 (Loren Petrich):
	Added object-oriented resource handling

Sep 24, 2000 (Loren Petrich):
	Banished OverallBounds as unnecessary; world_pixels->portRect does fine here

Jun 23, 2001 (Loren Petrich):
	Suppressed some of the asserts in the code; tried to make degradation more graceful

Jan 25, 2002 (Br'fin (Jeremy Parsons)):
	Added accessors for datafields now opaque in Carbon
*/

// add logon/logoff keywords. (& make terminal display them)
// cameras
// static
// delayed teleport

// activate tags
// picture with scrolling text.
// checkpoint with scrolling text
// don't use charwidth

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include <vector>

///#include "cseries.h"
#include "header.h"

#include "FileHandler.h"

#include "world.h"
#include "map.h"
#include "player.h"
#include "computer_interface.h"
//#include "screen_drawing.h"
//#include "overhead_map.h"
#include "mysound.h"
#include "interface.h" // for the error strings.
//#include "shell.h"
#include "platforms.h" // for tagged platforms
#include "lightsource.h" // for tagged lightsources
//#include "screen.h"

//#include "images.h"
#include "Packing.h"

//CP Addition: scripting support
//#include "scripting.h"

// MH: Lua scripting
//#include "lua_script.h"

#define LABEL_INSET 3
#define LOG_DURATION_BEFORE_TIMEOUT (2*TICKS_PER_SECOND)
#define BORDER_HEIGHT 18
#define BORDER_INSET 9
#define FUDGE_FACTOR 1

#define MAC_LINE_END 13

enum {
	_reading_terminal,
	_no_terminal_state,
	NUMBER_OF_TERMINAL_STATES
};

enum {
	_terminal_is_dirty= 0x01
};

enum {
	_any_abort_key_mask= _action_trigger_state,
	_terminal_up_arrow= _moving_forward,
	_terminal_down_arrow= _moving_backward,
	_terminal_page_down= _turning_right,
	_terminal_page_up= _turning_left,
	_terminal_next_state= _left_trigger_state
};

#define strCOMPUTER_LABELS 135
enum
{
	_marathon_name,
	_computer_starting_up,
	_computer_manufacturer,
	_computer_address,
	_computer_terminal,
	_scrolling_message,
	_acknowledgement_message,
	_disconnecting_message,
	_connection_terminated_message,
	_date_format
};

#define TERMINAL_IS_DIRTY(term) ((term)->flags & _terminal_is_dirty)
#define SET_TERMINAL_IS_DIRTY(term, v) ((void)((v)? ((term)->flags |= _terminal_is_dirty) : ((term)->flags &= ~_terminal_is_dirty)))

/* Maximum face changes per text grouping.. */
#define MAXIMUM_FACE_CHANGES_PER_TEXT_GROUPING (128)

enum {
	_text_is_encoded_flag= 0x0001
};

enum {
	_logon_group,
	_unfinished_group,
	_success_group,
	_failure_group,
	_information_group,
	_end_group,
	_interlevel_teleport_group, // permutation is level to go to
	_intralevel_teleport_group, // permutation is polygon to go to.
	_checkpoint_group, // permutation is the goal to show
	_sound_group, // permutation is the sound id to play
	_movie_group, // permutation is the movie id to play
	_track_group, // permutation is the track to play
	_pict_group, // permutation is the pict to display
	_logoff_group,
	_camera_group, //  permutation is the object index
	_static_group, // permutation is the duration of static.
	_tag_group, // permutation is the tag to activate

	NUMBER_OF_GROUP_TYPES
};

enum // flags to indicate text styles for paragraphs
{
	_plain_text      = 0x00,
	_bold_text       = 0x01,
	_italic_text     = 0x02,
	_underline_text  = 0x04
};

enum { /* terminal grouping flags */
	_draw_object_on_right= 0x01,  // for drawing checkpoints, picts, movies.
	_center_object= 0x02
};

struct terminal_groupings {
	int16 flags; /* varies.. */
	int16 type; /* _information_text, _checkpoint_text, _briefing_text, _movie, _sound_bite, _soundtrack */
	int16 permutation; /* checkpoint id for chkpt, level id for _briefing, movie id for movie, sound id for sound, soundtrack id for soundtrack */
	int16 start_index;
	int16 length;
	int16 maximum_line_count;
};
const int SIZEOF_terminal_groupings = 12;

struct text_face_data {
	int16 index;
	int16 face;
	int16 color;
};
const int SIZEOF_text_face_data = 6;

// This is externally visible, so its external size is defined in the header file
struct player_terminal_data
{
	int16 flags;
	int16 phase;
	int16 state;
	int16 current_group;
	int16 level_completion_state;
	int16 current_line;
	int16 maximum_line;
	int16 terminal_id;
	int32 last_action_flag;
};

struct terminal_key {
	int16 keycode;
	int16 offset;
	int16 mask;
	int32 action_flag;
};

struct font_dimensions {
	int16 lines_per_screen;
	int16 character_width;
};

/* Terminal data loaded from map (maintained by computer_interface.cpp) */
struct terminal_text_t {	// Object describing one terminal
	terminal_text_t() : text_length(0), text(NULL) {}
	terminal_text_t(const terminal_text_t &other) {copy(other);}
	~terminal_text_t() {delete[] text;}

	const terminal_text_t &operator=(const terminal_text_t &other)
	{
		if (this != &other)
			copy(other);
		return *this;
	}

	void copy(const terminal_text_t &other)
	{
		flags = other.flags;
		lines_per_page = other.lines_per_page;
		groupings = other.groupings;
		font_changes = other.font_changes;
		text_length = other.text_length;
		text = new uint8[text_length];
		memcpy(text, other.text, text_length);
	}

	uint16 flags;
	int16 lines_per_page;

	vector<terminal_groupings> groupings;
	vector<text_face_data> font_changes;

	int text_length;
	uint8 *text;
};

static vector<terminal_text_t> map_terminal_text;

/* internal global structure */
static struct player_terminal_data *player_terminals;

#define NUMBER_OF_TERMINAL_KEYS (sizeof(terminal_keys)/sizeof(struct terminal_key))

// Get the interface font to use from screen_drawing_<platform>.cpp
/*extern TextSpec *_get_font_spec(short font_index);
#if defined(mac)
extern void UseInterfaceFont(short font_index);
#elif defined(SDL)
extern sdl_font_info *GetInterfaceFont(short font_index);
extern uint16 GetInterfaceStyle(short font_index);
#endif
*/
/* ------------ private prototypes */
static player_terminal_data *get_player_terminal_data(
	short player_index);

/*static void draw_logon_text(Rect *bounds, terminal_text_t *terminal_text,
	short current_group_index, short logon_shape_id);
static void draw_computer_text(Rect *bounds, 
	terminal_text_t *terminal_text, short current_group_index, short current_line);
static void _draw_computer_text(char *base_text, short start_index, Rect *bounds,
	terminal_text_t *terminal_text, short current_line);
static short find_group_type(terminal_text_t *data, 
	short group_type);
static void teleport_to_level(short level_number);
static void teleport_to_polygon(short player_index, short polygon_index);
static struct terminal_groupings *get_indexed_grouping(
	terminal_text_t *data, short index);
static struct text_face_data *get_indexed_font_changes(
	terminal_text_t *data, short index);
static char *get_text_base(terminal_text_t *data);
// LP change: added a flag to indicate whether stuff after the other
// terminal stuff is to be drawn; if not, then draw the stuff before the
// other terminal stuff.
static void draw_terminal_borders(struct view_terminal_data *data, 
	struct player_terminal_data *terminal_data, Rect *terminal_frame,
	bool after_other_terminal_stuff);
static void next_terminal_state(short player_index);
static void next_terminal_group(short player_index, terminal_text_t *terminal_text);
static void get_date_string(char *date_string);
static void present_checkpoint_text(Rect *frame,
	terminal_text_t *terminal_text, short current_group_index,
	short current_line);
static bool find_checkpoint_location(short checkpoint_index, world_point2d *location, 
	short *polygon_index);
static void	set_text_face(struct text_face_data *text_face);
static void draw_line(char *base_text, short start_index, short end_index, Rect *bounds,
	terminal_text_t *terminal_text, short *text_face_start_index,
	short line_number);
static bool calculate_line(char *base_text, short width, short start_index, 
	short text_end_index, short *end_index);
static void handle_reading_terminal_keys(short player_index, long action_flags);
static void calculate_bounds_for_object(Rect *frame, short flags, Rect *bounds, Rect *source);
static void display_picture(short picture_id, Rect *frame, short flags);
static void display_picture_with_text(struct player_terminal_data *terminal_data, 
	Rect *bounds, terminal_text_t *terminal_text, short current_lien);
static short count_total_lines(char *base_text, short width, short start_index, short end_index);
static void calculate_bounds_for_text_box(Rect *frame, short flags, Rect *bounds);
static void goto_terminal_group(short player_index, terminal_text_t *terminal_text, 
	short new_group_index);
static bool previous_terminal_group(short player_index, terminal_text_t *terminal_text);
static void fill_terminal_with_static(Rect *bounds);
static short calculate_lines_per_page(void);

#ifdef PREPROCESSING_CODE
struct static_preprocessed_terminal_data *preprocess_text(char *text, short length);
static void pre_build_groups(struct terminal_groupings *groups,
	short *group_count, struct text_face_data *text_faces, short *text_face_count, 
	char *base_text, short *base_length);
static short matches_group(char *base_text, short length, short index, short possible_group, 
	short *permutation);
#else
static terminal_text_t *get_indexed_terminal_data(short id);

static void encode_text(terminal_text_t *terminal_text);
static void decode_text(terminal_text_t *terminal_text);
#endif
*/
/* ------------ machine-specific code */

#if defined(mac)
#include "computer_interface_mac.h"
#elif defined(SDL)
#include "computer_interface_sdl.h"
extern SDL_Surface *draw_surface;
#endif

/* ------------ code begins */

player_terminal_data *get_player_terminal_data(
	short player_index)
{
	struct player_terminal_data *player_terminal = GetMemberWithBounds(player_terminals,player_index,MAXIMUM_NUMBER_OF_PLAYERS);
	
	vassert(player_terminal, csprintf(temporary, "player index #%d is out of range", player_index));

	return player_terminal;
}


#ifdef PREPROCESSING_CODE
/*------------ */
/* -----> Preprocessing code... */
struct group_header_data {
	char *name;
	bool has_permutation;
};

static struct group_header_data group_data[]= {
	{"LOGON", true }, // permutation is the logo id to draw...
	{"UNFINISHED", false },
 	{"FINISHED", false },
	{"FAILED", false },
	{"INFORMATION", false },
	{"END", false },
	{"INTERLEVEL TELEPORT", true },
	{"INTRALEVEL TELEPORT", true },
	{"CHECKPOINT", true },
	{"SOUND", true },
	{"MOVIE", true },
	{"TRACK", true },
	{"PICT", true},
	{"LOGOFF", true }, // permutation is the logo id to draw...
	{"CAMERA", true}, // permutation is the object index
	{"STATIC", true}, // permutation is the duration of static.
	{"TAG", true} // permutation is the tag to activate
};

#define MAXIMUM_GROUPS_PER_TERMINAL 15

static void calculate_maximum_lines_for_groups(struct terminal_groupings *groups, 
	short group_count, char *text_base);

/* Note that this is NOT a marathon function, but an editor function... */
struct static_preprocessed_terminal_data *preprocess_text(
	char *text, 
	short length)
{
	short group_count, text_face_count;
	struct terminal_groupings groups[MAXIMUM_GROUPS_PER_TERMINAL];
	struct text_face_data text_faces[MAXIMUM_FACE_CHANGES_PER_TEXT_GROUPING];
	short new_length;
	struct static_preprocessed_terminal_data *data_structure;
	long total_length;
	short index;
	char *text_destination;

	new_length= length;
	pre_build_groups(groups, &group_count, text_faces, &text_face_count,
		text, &new_length);

	/* Allocate our conglomerated structure */
	total_length= sizeof(static_preprocessed_terminal_data) +
		group_count * sizeof(terminal_groupings) +
		text_face_count * sizeof(text_face_data) +
		new_length;

	data_structure= (struct static_preprocessed_terminal_data *) malloc(total_length);
	assert(data_structure);

	/* set these up.. */
	data_structure->total_length= total_length;
	data_structure->flags= 0; /* Don't encode (yet) */
	data_structure->grouping_count= group_count;
	data_structure->font_changes_count= text_face_count;

	/* Calculate the default lines per page for this font */
	data_structure->lines_per_page= calculate_lines_per_page();

	/* Calculate the maximum lines for each group */
	calculate_maximum_lines_for_groups(groups, group_count, text);

	for(index= 0; index<group_count; ++index)
	{
		struct terminal_groupings *destination;
		
		destination= get_indexed_grouping(data_structure, index);
		obj_copy(*destination, groups[index]);
	}

	for(index= 0; index<text_face_count; ++index)
	{
		struct text_face_data *destination;
		
		destination= get_indexed_font_changes(data_structure, index);
		obj_copy(*destination, text_faces[index]);

		// dprintf("%d/%d index: %d face: %d color: %d;g", index, text_face_count, text_faces[index].index, text_faces[index].face, text_faces[index].color);
	}

	text_destination= get_text_base(data_structure);
	memcpy(text_destination, text, new_length);
	//dprintf("Base: %x new_length: %d", text_destination, new_length);

	/* We be done! */
	return data_structure;
}

/* Life would be better if these were encoded like this for me.. */
static void pre_build_groups(
	struct terminal_groupings *groups, 
	short *group_count,
	struct text_face_data *text_faces,
	short *text_face_count,
	char *base_text,
	short *base_length)
{
	long index, current_length;
	bool in_group= false;
	short current_face, face_count, color_index, grp_count, data_length;
	bool last_was_return= true; /* in case the first line is a comment */

	/* Initial color, and face (plain) */
	color_index= current_face= 0;

	grp_count= face_count= 0;
	data_length= (*base_length);
	current_length= index= 0;
	/* Find the text groupings! */
	while(index<data_length)
	{
		if(base_text[index]=='#')
		{
			short possible_group;
			char first_char;

			/* This is some form of descriptive keyword.. */
			first_char= toupper(base_text[index+1]);
			for(possible_group= 0; possible_group<NUMBER_OF_GROUP_TYPES; ++possible_group)
			{
				if(first_char==group_data[possible_group].name[0])
				{
					short start_index, permutation;
					
					start_index= matches_group(base_text, data_length, index+1, possible_group, 
						&permutation);
					if(start_index != NONE)
					{
						short destination_index;
						
						if(in_group) 
						{
							/* Minus one, because we have the # included.. */
							assert(grp_count+1<MAXIMUM_GROUPS_PER_TERMINAL);
							groups[grp_count++].length= current_length;
							base_text[index]= 0; // null out the end of each group.
							destination_index= index+1;
						} else {	
							destination_index= index;
						}
						
						assert(data_length-start_index>=0);
						/* move it down-> check this! */
						memmove(&base_text[destination_index], 
							&base_text[start_index], data_length-start_index);
						data_length -= (start_index-destination_index);
						groups[grp_count].flags= 0;
						groups[grp_count].type= possible_group;
						groups[grp_count].permutation= permutation;
						groups[grp_count].start_index= destination_index;
						current_length= 0;
						in_group= true;
						break; /* out of for loop */
					}
				}
			}

			/* If we didn't match it, continue on..... */
			if(possible_group==NUMBER_OF_GROUP_TYPES)
			{
				index++;
				current_length++;
			}
//			vassert(possible_group==NUMBER_OF_GROUP_TYPES || base_text[index]!='#', 
//				csprintf(temporary, "Base: %x index: %d", base_text, index));
		} 
		else if(base_text[index]=='$')
		{
			bool changed_font= true;
			short move_down_by;
			
			move_down_by= 2;
			switch(base_text[index+1])
			{
				case 'B': /* Bold on! */
					current_face |= _bold_text;
					break;
					
				case 'b': /* bold off */
					current_face &= ~_bold_text;
					break;

				case 'I': /* Italic on */
					current_face |= _italic_text;
					break;
					
				case 'i': /* Italic off */
					current_face &= ~_italic_text;
					break;
					
				case 'U': /* Underline on */
					current_face |= _underline_text;
					break;
					
				case 'u': /* Underline off */
					current_face &= ~_underline_text;
					break;

				case 'C':
					switch(base_text[index+2])
					{
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
							color_index= base_text[index+2]-'0';
							move_down_by= 3;
							break;
							
						default:
							break;
					}
					break;
					
				default:
					/* Pass it on through, unchanged */
					changed_font= false;
					move_down_by= 0;
					break;
			}
			
			/* If we changed the font, move the text down.. */
			if(changed_font)
			{
				assert(face_count+1<MAXIMUM_FACE_CHANGES_PER_TEXT_GROUPING);
				text_faces[face_count].index= index;
				text_faces[face_count].color= color_index;
				text_faces[face_count++].face= current_face;
				
				/* And move the data down by 2 characters.. */
				memmove(&base_text[index], 
					&base_text[index+move_down_by], data_length-index-move_down_by);
				data_length -= move_down_by;
	
				/* Note that index doesn't change.. */
			} else {
				index++;
				current_length++;
			}
		} 
		else if (base_text[index]==';' && last_was_return)
		{
			short destination_index, start_index;

			/* this is a comment */
			destination_index= start_index= index;
			while(start_index<data_length && base_text[start_index] != MAC_LINE_END) start_index++;

			/* Eat the return on the comment line. */
			if(start_index<data_length && base_text[start_index]==MAC_LINE_END) start_index++;
			
			/* Nix the comment */			
			memmove(&base_text[destination_index], &base_text[start_index], data_length-start_index);
			data_length -= (start_index-destination_index);
		} else {
			if(base_text[index]==MAC_LINE_END)
			{
				last_was_return= true;
			} else {
				last_was_return= false;
			}
			index++;
			current_length++;
		}
	}

	/* Save the proper positions.. */
	(*text_face_count)= face_count;
	(*group_count)= grp_count;
	(*base_length)= data_length;
	if(in_group) groups[grp_count].length= current_length;
}

/* Return NONE if it doesn't matches.. */
static short matches_group(
	char *base_text, 
	short length,
	short index, 
	short possible_group, 
	short *permutation)
{
	short start_index= NONE;

	if(memcmp(&base_text[index], group_data[possible_group].name, 
		strlen(group_data[possible_group].name))==0)
	{
		/* This is a match.  find the end... */
		start_index= index+strlen(group_data[possible_group].name);
		
		if(group_data[possible_group].has_permutation)
		{
			/* Find the permutation... */
			*permutation= atoi(&base_text[start_index]);
		}
		
		/* Eat the rest of it.. */
		while(start_index<length && base_text[start_index] != MAC_LINE_END) start_index++;
		if(base_text[start_index]==MAC_LINE_END) start_index++;
	}
	
	return start_index;
}

static void find_all_permutations_of_type(
	byte *terminals,
	short terminal_count,
	short group_type,
	short *permutations,
	short *permutation_count)
{
	short terminal_index;
	struct static_preprocessed_terminal_data *data;
	long offset= 0l;
	short count= 0;

	for(terminal_index= 0; terminal_index<terminal_count; terminal_index++)
	{
		short group_index;
	
		data= (struct static_preprocessed_terminal_data *) (terminals+offset);
		for(group_index= 0; group_index<data->grouping_count; ++group_index)
		{
			struct terminal_groupings *group= get_indexed_grouping(data, group_index);
			// LP addition: just in case...
			if (!group) continue;
			if(group->type==group_type)
			{
				permutations[count++]= group->permutation;
			}
		}
		
		offset+= data->total_length;
	}

	*permutation_count= count;
}

void find_all_picts_references_by_terminals(
	byte *compiled_text, 
	short terminal_count,
	short *picts, 
	short *picture_count)
{
	find_all_permutations_of_type((byte *) compiled_text, terminal_count, _pict_group, picts, 
		picture_count);
}

void find_all_checkpoints_references_by_terminals(
	byte *compiled_text, 
	short terminal_count,
	short *checkpoints, 
	short *checkpoint_count)
{
	find_all_permutations_of_type((byte *) compiled_text, terminal_count, _checkpoint_group, 
		checkpoints, checkpoint_count);
}

bool terminal_has_finished_text_type(
	short terminal_id,
	short finished_type)
{
	bool has_type= false;
	terminal_text_t *terminal_text= get_indexed_terminal_data(terminal_id);
	// LP addition: quit if none
	if (!terminal_text) return false;
	short index;
	
	index= find_group_type(terminal_text, finished_type);
	if(index==terminal_text->grouping_count) 
	{
		has_type= false;
	} else {
		has_type= true;
	}

	return has_type;
}

static void calculate_maximum_lines_for_groups(
	struct terminal_groupings *groups,
	short group_count,
	char *text_base)
{
	short index;
	
	for(index= 0; index<group_count; ++index)
	{
		switch(groups[index].type)
		{
			case _logon_group:
			case _logoff_group:
			case _interlevel_teleport_group:
			case _intralevel_teleport_group:
			case _sound_group:
			case _tag_group:
			case _movie_group:
			case _track_group:
			case _camera_group:
			case _static_group:
			case _end_group:
				groups[index].maximum_line_count= 1; // any click or keypress gets us out.
				break;
	
			case _unfinished_group:
			case _success_group:
			case _failure_group:
				groups[index].maximum_line_count= 0; // should never get to one of these groups.
				break;
	
			case _checkpoint_group:
			case _pict_group:
				{
					Rect text_bounds, bounds;
		
					/* The only thing we care about is the width. */
					SetRect(&bounds, 0, 0, 640, 480);
					InsetRect(&bounds, BORDER_INSET, BORDER_HEIGHT+BORDER_INSET);
					calculate_bounds_for_text_box(&bounds, groups[index].flags, &text_bounds);
					groups[index].maximum_line_count= count_total_lines(text_base,
						RECTANGLE_WIDTH(&text_bounds), groups[index].start_index, 
						groups[index].start_index+groups[index].length);
				}
				break;
				
			case _information_group:
				{
					short width= 640; // еее sync (Must guarantee 100 high res!)
	
					width-= 2*(72-BORDER_INSET); /* 1 inch in from each side */				
					groups[index].maximum_line_count= count_total_lines(text_base, 
						width, groups[index].start_index, 
						groups[index].start_index+groups[index].length);
				}
				break;
				
			default:
				break;
		}
	}
}
#endif // End of preprocessing code

static struct terminal_groupings *get_indexed_grouping(
	terminal_text_t *data,
	short index)
{
	if (index < 0 || index >= int(data->groupings.size()))
		return NULL;

	return &data->groupings[index];
}

static struct text_face_data *get_indexed_font_changes(
	terminal_text_t *data,
	short index)
{
	if (index < 0 || index >= int(data->font_changes.size()))
		return NULL;

	return &data->font_changes[index];
}

static char *get_text_base(
	terminal_text_t *data)
{
	return (char *)data->text;
}
/*
static short calculate_lines_per_page(
	void)


/*
 *  Calculate the length the loaded terminal data would take up on disk
 *  (for saving)
 */

static size_t packed_terminal_length(const terminal_text_t &t)
{
	return SIZEOF_static_preprocessed_terminal_data
	     + t.groupings.size() * SIZEOF_terminal_groupings
	     + t.font_changes.size() * SIZEOF_text_face_data
	     + t.text_length;
}

size_t calculate_packed_terminal_data_length(void)
{
	size_t total = 0;

	// Loop for all terminals
	vector<terminal_text_t>::const_iterator t = map_terminal_text.begin(), tend = map_terminal_text.end();
	while (t != tend) {
		total += packed_terminal_length(*t);
		t++;
	}

	return total;
}


/*
 *  Unpack terminal data from stream
 */

void unpack_map_terminal_data(uint8 *p, size_t count)
{
	// Clear existing terminals
	map_terminal_text.clear();

	// Unpack all terminals
	while (count > 0) {

		// Create new terminal_text_t
		terminal_text_t t;
		map_terminal_text.push_back(t);
		terminal_text_t &data = map_terminal_text.back();

		// Read header
		uint8 *p_start = p, *p_header = p;
		uint16 total_length, grouping_count, font_changes_count;
		StreamToValue(p, total_length);
		StreamToValue(p, data.flags);
		StreamToValue(p, data.lines_per_page);
		StreamToValue(p, grouping_count);
		StreamToValue(p, font_changes_count);
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_static_preprocessed_terminal_data));

		// Reserve memory for groupings and font changes
		data.groupings.reserve(grouping_count);
		data.font_changes.reserve(font_changes_count);

		// Read groupings
		p_start = p;
		for (int i=0; i<grouping_count; i++) {
			terminal_groupings g;
			StreamToValue(p, g.flags);
			StreamToValue(p, g.type);
			StreamToValue(p, g.permutation);
			StreamToValue(p, g.start_index);
			StreamToValue(p, g.length);
			StreamToValue(p, g.maximum_line_count);
			data.groupings.push_back(g);
		}
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_terminal_groupings) * grouping_count);

		// Read font changes
		p_start = p;
		for (int i=0; i<font_changes_count; i++) {
			text_face_data f;
			StreamToValue(p, f.index);
			StreamToValue(p, f.face);
			StreamToValue(p, f.color);
			data.font_changes.push_back(f);
		}
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_text_face_data) * font_changes_count);

		// Read text (no conversion)
		data.text_length = total_length - static_cast<int>(p - p_header);
		assert(data.text_length >= 0);
		data.text = new uint8[data.text_length];
		StreamToBytes(p, data.text, data.text_length);

		// Continue with next terminal
		count -= total_length;
	}
}


/*
 *  Pack terminal data to stream
 */

void pack_map_terminal_data(uint8 *p, size_t count)
{
	// Pack all terminals
	vector<terminal_text_t>::const_iterator t = map_terminal_text.begin(), tend = map_terminal_text.end();
	while (t != tend) {

		// Write header
		uint8 *p_start = p;
		uint16 total_length = static_cast<uint16>(packed_terminal_length(*t));
		uint16 grouping_count = static_cast<uint16>(t->groupings.size());
		uint16 font_changes_count = static_cast<uint16>(t->font_changes.size());
		ValueToStream(p, total_length);
		ValueToStream(p, t->flags);
		ValueToStream(p, t->lines_per_page);
		ValueToStream(p, grouping_count);
		ValueToStream(p, font_changes_count);
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_static_preprocessed_terminal_data));

		// Write groupings
		p_start = p;
		vector<terminal_groupings>::const_iterator g = t->groupings.begin(), gend = t->groupings.end();
		while (g != gend) {
			ValueToStream(p, g->flags);
			ValueToStream(p, g->type);
			ValueToStream(p, g->permutation);
			ValueToStream(p, g->start_index);
			ValueToStream(p, g->length);
			ValueToStream(p, g->maximum_line_count);
			g++;
		}
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_terminal_groupings) * grouping_count);

		// Write font changes
		p_start = p;
		vector<text_face_data>::const_iterator f = t->font_changes.begin(), fend = t->font_changes.end();
		while (f != fend) {
			ValueToStream(p, f->index);
			ValueToStream(p, f->face);
			ValueToStream(p, f->color);
			f++;
		}
		assert((p - p_start) == static_cast<ptrdiff_t>(SIZEOF_text_face_data) * font_changes_count);

		// Write text (no conversion)
		BytesToStream(p, t->text, t->text_length);

		// Continue with next terminal
		t++;
	}
}


uint8 *unpack_player_terminal_data(uint8 *Stream, size_t Count)
{
	uint8* S = Stream;
	player_terminal_data* ObjPtr = player_terminals;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->flags);
		StreamToValue(S,ObjPtr->phase);
		StreamToValue(S,ObjPtr->state);
		StreamToValue(S,ObjPtr->current_group);
		StreamToValue(S,ObjPtr->level_completion_state);
		StreamToValue(S,ObjPtr->current_line);
		StreamToValue(S,ObjPtr->maximum_line);
		StreamToValue(S,ObjPtr->terminal_id);
		StreamToValue(S,ObjPtr->last_action_flag);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_terminal_data));
	return S;
}

uint8 *pack_player_terminal_data(uint8 *Stream, size_t Count)
{
	uint8* S = Stream;
	player_terminal_data* ObjPtr = player_terminals;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->flags);
		ValueToStream(S,ObjPtr->phase);
		ValueToStream(S,ObjPtr->state);
		ValueToStream(S,ObjPtr->current_group);
		ValueToStream(S,ObjPtr->level_completion_state);
		ValueToStream(S,ObjPtr->current_line);
		ValueToStream(S,ObjPtr->maximum_line);
		ValueToStream(S,ObjPtr->terminal_id);
		ValueToStream(S,ObjPtr->last_action_flag);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_player_terminal_data));
	return S;
}
