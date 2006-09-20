#ifndef __COMPUTER_INTERFACE_H
#define __COMPUTER_INTERFACE_H

/*
	computer_interface.h

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

	Tuesday, August 23, 1994 11:25:40 PM (ajr)
	Thursday, May 25, 1995 5:18:03 PM- rewriting.

	New paradigm:
	Groups each start with one of the following groups:
	 #UNFINISHED, #SUCCESS, #FAILURE

	First is shown the
	#LOGON XXXXX
	
	Then there are any number of groups with:
	#INFORMATION, #CHECKPOINT, #SOUND, #MOVIE, #TRACK
	
	And a final:
	#INTERLEVEL TELEPORT, #INTRALEVEL TELEPORT		
	
	Each group ends with:
	#END

	Groupings:
	#logon XXXX- login message (XXXX is shape for login screen)
	#unfinished- unfinished message
	#success- success message
	#failure- failure message
	#information- information
	#briefing XX- briefing, then load XX
	#checkpoint XX- Checkpoint xx (associated with goal) 
	#sound XXXX- play sound XXXX
	#movie XXXX- play movie XXXX (from Movie file)
	#track XXXX- play soundtrack XXXX (from Music file)
	#interlevel teleport XXX- go to level XXX
	#intralevel teleport XXX- go to polygon XXX
	#pict XXXX- diplay the pict resource XXXX

	Special embedded keys:   
	$B- Bold on
	$b- bold off
	$I- Italic on
	$i- italic off
	$U- underline on
	$u- underline off
	$- anything else is passed through unchanged

	Preprocessed format:
	static:
		int32 total_length;
		short grouping_count;
		short font_changes_count;
		short total_text_length;
	dynamic:
		struct terminal_groupings groups[grouping_count];
		struct text_face_data[font_changes_count];
		char text;
*/
#include "player.h"

/* ------------ structures */
struct static_preprocessed_terminal_data {
	int16 total_length;
	int16 flags;
	int16 lines_per_page; /* Added for internationalization/sync problems */
	int16 grouping_count;
	int16 font_changes_count;
};
const int SIZEOF_static_preprocessed_terminal_data = 10;

struct view_terminal_data {
	short top, left, bottom, right;
	short vertical_offset;
};

// External-data size of current terminal state
const int SIZEOF_player_terminal_data = 20;

/* ------------ prototypes */
void initialize_terminal_manager(void);
void initialize_player_terminal_info(short player_index);
void enter_computer_interface(short player_index, short text_number, short completion_flag);
void _render_computer_interface(struct view_terminal_data *data);
void update_player_for_terminal_mode(short player_index);
void update_player_keys_for_terminal(short player_index, uint32 action_flags);
uint32 build_terminal_action_flags(char *keymap);
void dirty_terminal_view(short player_index);
void abort_terminal_mode(short player_index);

//bool player_in_terminal_mode(short player_index);

// LP: to pack and unpack this data;
// these hide the unpacked data from the outside world.
// "Map terminal" means the terminal data read in from the map;
// "player terminal" means the terminal state for each player.
// For the map terminal data, the "count" is number of packed bytes.

extern void unpack_map_terminal_data(uint8 *Stream, size_t Count);
extern void pack_map_terminal_data(uint8 *Stream, size_t Count);
uint8 *unpack_player_terminal_data(uint8 *Stream, size_t Count);
uint8 *pack_player_terminal_data(uint8 *Stream, size_t Count);

extern size_t calculate_packed_terminal_data_length(void);

//HogePiyo move these from computer_interface.cpp
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

extern vector<terminal_text_t> map_terminal_text;

#ifdef PREPROCESSING_CODE
struct static_preprocessed_terminal_data *preprocess_text(char *text, short length);
struct static_preprocessed_terminal_data *get_indexed_terminal_data(short id);
void encode_text(struct static_preprocessed_terminal_data *terminal_text);
void decode_text(struct static_preprocessed_terminal_data *terminal_text);
void find_all_picts_references_by_terminals(byte *compiled_text, short terminal_count,
	short *picts, short *picture_count);
void find_all_checkpoints_references_by_terminals(byte *compiled_text, 
	short terminal_count, short *checkpoints, short *checkpoint_count);
bool terminal_has_finished_text_type(short terminal_id, short finished_type);
#endif

terminal_text_t *get_indexed_terminal_data(
	short id);
#endif
