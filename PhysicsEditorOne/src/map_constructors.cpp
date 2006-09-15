/*
MAP_CONSTRUCTORS.C

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

Friday, June 3, 1994 1:06:31 PM

Thursday, March 23, 1995 8:53:35 PM  (Jason')
	added guess_side_lightsource_indexes().

Jan 30, 2000 (Loren Petrich):
	Added some typecasts

Feb. 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 15, 2000 (Loren Petrich):
	Suppressed some assertions designed to check for map consistency;
	this is to get around some Pfhorte bugs.

April 16, 2000 (Loren Petrich):
	Made the incorrect-count vwarns optional

Aug 29, 2000 (Loren Petrich):
	Created packing and unpacking functions for all the
		externally-accessible data types defined here

Dec 14, 2000 (Loren Petrich):
	Added growable lists for lists of intersecting endpoints, lines, and polygons
*/

const bool DoIncorrectCountVWarn = true;


//#include "cseries.h"
#include "header.h"
#include "map.h"
//#include "flood_map.h"
#include "Packing.h"

#include <limits.h>
#include <vector>

/*
maps of one polygon don’t have their impassability information computed

//detached polygons (i.e., shadows) and their twins will not have their neighbor polygon lists correctly computed
//adjacent polygons should be precalculated in the polygon structure
//intersecting_flood_proc can’t store side information (using sign) with line index zero
//keep_line_segment_out_of_walls() can’t use precalculated height information and should do weird things next to elevators and doors
*/

#ifdef env68k
#pragma segment map
#endif

/* ---------- structures */

#define MAXIMUM_INTERSECTING_INDEXES 64

struct intersecting_flood_data
{
	// This stuff now global:
	/*
	short *line_indexes;
	short line_count;
	
	short *endpoint_indexes;
	short endpoint_count;
	
	short *polygon_indexes;
	short polygon_count;
	*/
	
	short original_polygon_index;
	world_point2d center;
	
	long minimum_separation_squared;
};

/* ---------- globals */
static long map_index_buffer_count= 0l; /* Added due to the dynamic nature of maps */

// LP: Temporary areas for nearby endpoint/line/polygon finding;
// OK for this to be global since they replace only single instances.
static vector<short> LineIndices(MAXIMUM_INTERSECTING_INDEXES);
static vector<short> EndpointIndices(MAXIMUM_INTERSECTING_INDEXES);
static vector<short> PolygonIndices(MAXIMUM_INTERSECTING_INDEXES);


/* ---------- private prototypes */

static short calculate_clockwise_endpoints(short polygon_index, short *buffer);
static void calculate_adjacent_polygons(short polygon_index, short *polygon_indexes);
static void calculate_adjacent_sides(short polygon_index, short *side_indexes);
static long calculate_polygon_area(short polygon_index);

static void add_map_index(short index, short *count);
static void find_intersecting_endpoints_and_lines(short polygon_index, world_distance minimum_separation);
static long intersecting_flood_proc(short source_polygon_index, short line_index,
	short destination_polygon_index, void *data);

static void precalculate_polygon_sound_sources(void);

/* ---------- code */

uint8 *unpack_endpoint_data(uint8 *Stream, endpoint_data *Objects, size_t Count)
{
	uint8* S = Stream;
	endpoint_data* ObjPtr = Objects;
     
     for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->flags);
		StreamToValue(S,ObjPtr->highest_adjacent_floor_height);
		StreamToValue(S,ObjPtr->lowest_adjacent_ceiling_height);
		
		StreamToValue(S,ObjPtr->vertex.x);
		StreamToValue(S,ObjPtr->vertex.y);
		StreamToValue(S,ObjPtr->transformed.x);
		StreamToValue(S,ObjPtr->transformed.y);
		
		StreamToValue(S,ObjPtr->supporting_polygon_index);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_endpoint_data));
	return S;
}

uint8 *pack_endpoint_data(uint8 *Stream, endpoint_data *Objects, size_t Count)
{
	uint8* S = Stream;
	endpoint_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->flags);
		ValueToStream(S,ObjPtr->highest_adjacent_floor_height);
		ValueToStream(S,ObjPtr->lowest_adjacent_ceiling_height);
		
		ValueToStream(S,ObjPtr->vertex.x);
		ValueToStream(S,ObjPtr->vertex.y);
		ValueToStream(S,ObjPtr->transformed.x);
		ValueToStream(S,ObjPtr->transformed.y);
		
		ValueToStream(S,ObjPtr->supporting_polygon_index);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_endpoint_data));
	return S;
}


uint8 *unpack_line_data(uint8 *Stream, line_data *Objects, size_t Count)
{
	uint8* S = Stream;
	line_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToList(S,ObjPtr->endpoint_indexes,2);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->length);
		StreamToValue(S,ObjPtr->highest_adjacent_floor);
		StreamToValue(S,ObjPtr->lowest_adjacent_ceiling);
		
		StreamToValue(S,ObjPtr->clockwise_polygon_side_index);
		StreamToValue(S,ObjPtr->counterclockwise_polygon_side_index);
		
		StreamToValue(S,ObjPtr->clockwise_polygon_owner);
		StreamToValue(S,ObjPtr->counterclockwise_polygon_owner);
		
		S += 6*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_line_data));
	return S;
}

uint8 *pack_line_data(uint8 *Stream, line_data *Objects, size_t Count)
{
	uint8* S = Stream;
	line_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ListToStream(S,ObjPtr->endpoint_indexes,2);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->length);
		ValueToStream(S,ObjPtr->highest_adjacent_floor);
		ValueToStream(S,ObjPtr->lowest_adjacent_ceiling);
		
		ValueToStream(S,ObjPtr->clockwise_polygon_side_index);
		ValueToStream(S,ObjPtr->counterclockwise_polygon_side_index);
		
		ValueToStream(S,ObjPtr->clockwise_polygon_owner);
		ValueToStream(S,ObjPtr->counterclockwise_polygon_owner);
		
		S += 6*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_line_data));
	return S;
}


inline void StreamToSideTxtr(uint8* &S, side_texture_definition& Object)
{
	StreamToValue(S,Object.x0);
	StreamToValue(S,Object.y0);
	StreamToValue(S,Object.texture);
}

inline void SideTxtrToStream(uint8* &S, side_texture_definition& Object)
{
	ValueToStream(S,Object.x0);
	ValueToStream(S,Object.y0);
	ValueToStream(S,Object.texture);	
}


void StreamToSideExclZone(uint8* &S, side_exclusion_zone& Object)
{
	StreamToValue(S,Object.e0.x);
	StreamToValue(S,Object.e0.y);
	StreamToValue(S,Object.e1.x);
	StreamToValue(S,Object.e1.y);
	StreamToValue(S,Object.e2.x);
	StreamToValue(S,Object.e2.y);
	StreamToValue(S,Object.e3.x);
	StreamToValue(S,Object.e3.y);
}

void SideExclZoneToStream(uint8* &S, side_exclusion_zone& Object)
{
	ValueToStream(S,Object.e0.x);
	ValueToStream(S,Object.e0.y);
	ValueToStream(S,Object.e1.x);
	ValueToStream(S,Object.e1.y);
	ValueToStream(S,Object.e2.x);
	ValueToStream(S,Object.e2.y);
	ValueToStream(S,Object.e3.x);
	ValueToStream(S,Object.e3.y);
}


uint8 *unpack_side_data(uint8 *Stream, side_data *Objects, size_t Count)
{
	uint8* S = Stream;
	side_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToSideTxtr(S,ObjPtr->primary_texture);
		StreamToSideTxtr(S,ObjPtr->secondary_texture);
		StreamToSideTxtr(S,ObjPtr->transparent_texture);
		
		StreamToSideExclZone(S,ObjPtr->exclusion_zone);
		
		StreamToValue(S,ObjPtr->control_panel_type);
		StreamToValue(S,ObjPtr->control_panel_permutation);
		
		StreamToValue(S,ObjPtr->primary_transfer_mode);
		StreamToValue(S,ObjPtr->secondary_transfer_mode);
		StreamToValue(S,ObjPtr->transparent_transfer_mode);
		
		StreamToValue(S,ObjPtr->polygon_index);
		StreamToValue(S,ObjPtr->line_index);
		
		StreamToValue(S,ObjPtr->primary_lightsource_index);
		StreamToValue(S,ObjPtr->secondary_lightsource_index);
		StreamToValue(S,ObjPtr->transparent_lightsource_index);
		
		StreamToValue(S,ObjPtr->ambient_delta);
		
		S += 1*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_side_data));
	return S;
}

uint8 *pack_side_data(uint8 *Stream, side_data *Objects, size_t Count)
{
	uint8* S = Stream;
	side_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		ValueToStream(S,ObjPtr->flags);
		
		SideTxtrToStream(S,ObjPtr->primary_texture);
		SideTxtrToStream(S,ObjPtr->secondary_texture);
		SideTxtrToStream(S,ObjPtr->transparent_texture);
		
		SideExclZoneToStream(S,ObjPtr->exclusion_zone);
		
		ValueToStream(S,ObjPtr->control_panel_type);
		ValueToStream(S,ObjPtr->control_panel_permutation);
		
		ValueToStream(S,ObjPtr->primary_transfer_mode);
		ValueToStream(S,ObjPtr->secondary_transfer_mode);
		ValueToStream(S,ObjPtr->transparent_transfer_mode);
		
		ValueToStream(S,ObjPtr->polygon_index);
		ValueToStream(S,ObjPtr->line_index);
		
		ValueToStream(S,ObjPtr->primary_lightsource_index);
		ValueToStream(S,ObjPtr->secondary_lightsource_index);
		ValueToStream(S,ObjPtr->transparent_lightsource_index);
		
		ValueToStream(S,ObjPtr->ambient_delta);
		
		S += 1*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_side_data));
	return S;
}


uint8 *unpack_polygon_data(uint8 *Stream, polygon_data *Objects, size_t Count)
{
	uint8* S = Stream;
	polygon_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		StreamToValue(S,ObjPtr->flags);
		StreamToValue(S,ObjPtr->permutation);
		
		StreamToValue(S,ObjPtr->vertex_count);
		StreamToList(S,ObjPtr->endpoint_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		StreamToList(S,ObjPtr->line_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		StreamToValue(S,ObjPtr->floor_texture);
		StreamToValue(S,ObjPtr->ceiling_texture);
		StreamToValue(S,ObjPtr->floor_height);
		StreamToValue(S,ObjPtr->ceiling_height);
		StreamToValue(S,ObjPtr->floor_lightsource_index);
		StreamToValue(S,ObjPtr->ceiling_lightsource_index);
		
		StreamToValue(S,ObjPtr->area);
		
		StreamToValue(S,ObjPtr->first_object);
		
		StreamToValue(S,ObjPtr->first_exclusion_zone_index);
		StreamToValue(S,ObjPtr->line_exclusion_zone_count);
		StreamToValue(S,ObjPtr->point_exclusion_zone_count);
		
		StreamToValue(S,ObjPtr->floor_transfer_mode);
		StreamToValue(S,ObjPtr->ceiling_transfer_mode);
		
		StreamToList(S,ObjPtr->adjacent_polygon_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		StreamToValue(S,ObjPtr->first_neighbor_index);
		StreamToValue(S,ObjPtr->neighbor_count);
		
		StreamToValue(S,ObjPtr->center.x);
		StreamToValue(S,ObjPtr->center.y);
		
		StreamToList(S,ObjPtr->side_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		StreamToValue(S,ObjPtr->floor_origin.x);
		StreamToValue(S,ObjPtr->floor_origin.y);
		StreamToValue(S,ObjPtr->ceiling_origin.x);
		StreamToValue(S,ObjPtr->ceiling_origin.y);
		
		StreamToValue(S,ObjPtr->media_index);
		StreamToValue(S,ObjPtr->media_lightsource_index);
		
		StreamToValue(S,ObjPtr->sound_source_indexes);
		
		StreamToValue(S,ObjPtr->ambient_sound_image_index);
		StreamToValue(S,ObjPtr->random_sound_image_index);
		
		S += 1*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_polygon_data));
	return S;
}

uint8 *pack_polygon_data(uint8 *Stream, polygon_data *Objects, size_t Count)
{
	uint8* S = Stream;
	polygon_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		ValueToStream(S,ObjPtr->flags);
		ValueToStream(S,ObjPtr->permutation);
		
		ValueToStream(S,ObjPtr->vertex_count);
		ListToStream(S,ObjPtr->endpoint_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		ListToStream(S,ObjPtr->line_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		ValueToStream(S,ObjPtr->floor_texture);
		ValueToStream(S,ObjPtr->ceiling_texture);
		ValueToStream(S,ObjPtr->floor_height);
		ValueToStream(S,ObjPtr->ceiling_height);
		ValueToStream(S,ObjPtr->floor_lightsource_index);
		ValueToStream(S,ObjPtr->ceiling_lightsource_index);
		
		ValueToStream(S,ObjPtr->area);
		
		ValueToStream(S,ObjPtr->first_object);
		
		ValueToStream(S,ObjPtr->first_exclusion_zone_index);
		ValueToStream(S,ObjPtr->line_exclusion_zone_count);
		ValueToStream(S,ObjPtr->point_exclusion_zone_count);
		
		ValueToStream(S,ObjPtr->floor_transfer_mode);
		ValueToStream(S,ObjPtr->ceiling_transfer_mode);
		
		ListToStream(S,ObjPtr->adjacent_polygon_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		ValueToStream(S,ObjPtr->first_neighbor_index);
		ValueToStream(S,ObjPtr->neighbor_count);
		
		ValueToStream(S,ObjPtr->center.x);
		ValueToStream(S,ObjPtr->center.y);
		
		ListToStream(S,ObjPtr->side_indexes,MAXIMUM_VERTICES_PER_POLYGON);
		
		ValueToStream(S,ObjPtr->floor_origin.x);
		ValueToStream(S,ObjPtr->floor_origin.y);
		ValueToStream(S,ObjPtr->ceiling_origin.x);
		ValueToStream(S,ObjPtr->ceiling_origin.y);
		
		ValueToStream(S,ObjPtr->media_index);
		ValueToStream(S,ObjPtr->media_lightsource_index);
		
		ValueToStream(S,ObjPtr->sound_source_indexes);
		
		ValueToStream(S,ObjPtr->ambient_sound_image_index);
		ValueToStream(S,ObjPtr->random_sound_image_index);
		
		S += 1*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_polygon_data));
	return S;
}


uint8 *unpack_map_annotation(uint8 *Stream, map_annotation* Objects, size_t Count)
{
	uint8* S = Stream;
	map_annotation* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		
		StreamToValue(S,ObjPtr->location.x);
		StreamToValue(S,ObjPtr->location.y);
		StreamToValue(S,ObjPtr->polygon_index);
		
		StreamToBytes(S,ObjPtr->text,MAXIMUM_ANNOTATION_TEXT_LENGTH);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_map_annotation));
	return S;
}

uint8 *pack_map_annotation(uint8 *Stream, map_annotation* Objects, size_t Count)
{
	uint8* S = Stream;
	map_annotation* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		
		ValueToStream(S,ObjPtr->location.x);
		ValueToStream(S,ObjPtr->location.y);
		ValueToStream(S,ObjPtr->polygon_index);
		
		BytesToStream(S,ObjPtr->text,MAXIMUM_ANNOTATION_TEXT_LENGTH);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_map_annotation));
	return S;
}


uint8 *unpack_map_object(uint8 *Stream, map_object* Objects, size_t Count)
{
	uint8* S = Stream;
	map_object* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		StreamToValue(S,ObjPtr->index);
		StreamToValue(S,ObjPtr->facing);
		StreamToValue(S,ObjPtr->polygon_index);
		StreamToValue(S,ObjPtr->location.x);
		StreamToValue(S,ObjPtr->location.y);
		StreamToValue(S,ObjPtr->location.z);
		
		StreamToValue(S,ObjPtr->flags);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_map_object));
	return S;
}

uint8 *pack_map_object(uint8 *Stream, map_object* Objects, size_t Count)
{
	uint8* S = Stream;
	map_object* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		ValueToStream(S,ObjPtr->index);
		ValueToStream(S,ObjPtr->facing);
		ValueToStream(S,ObjPtr->polygon_index);
		ValueToStream(S,ObjPtr->location.x);
		ValueToStream(S,ObjPtr->location.y);
		ValueToStream(S,ObjPtr->location.z);
		
		ValueToStream(S,ObjPtr->flags);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_map_object));
	return S;
}


uint8 *unpack_object_frequency_definition(uint8 *Stream, object_frequency_definition* Objects, size_t Count)
{
	uint8* S = Stream;
	object_frequency_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->initial_count);
		StreamToValue(S,ObjPtr->minimum_count);
		StreamToValue(S,ObjPtr->maximum_count);
		
		StreamToValue(S,ObjPtr->random_count);
		StreamToValue(S,ObjPtr->random_chance);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_object_frequency_definition));
	return S;
}

uint8 *pack_object_frequency_definition(uint8 *Stream, object_frequency_definition* Objects, size_t Count)
{
	uint8* S = Stream;
	object_frequency_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->initial_count);
		ValueToStream(S,ObjPtr->minimum_count);
		ValueToStream(S,ObjPtr->maximum_count);
		
		ValueToStream(S,ObjPtr->random_count);
		ValueToStream(S,ObjPtr->random_chance);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_object_frequency_definition));
	return S;
}


uint8 *unpack_static_data(uint8 *Stream, static_data* Objects, size_t Count)
{
	uint8* S = Stream;
	static_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->environment_code);
		
		StreamToValue(S,ObjPtr->physics_model);
		StreamToValue(S,ObjPtr->song_index);
		StreamToValue(S,ObjPtr->mission_flags);
		StreamToValue(S,ObjPtr->environment_flags);
		
		S += 4*2;
		
		StreamToBytes(S,ObjPtr->level_name,LEVEL_NAME_LENGTH);
		StreamToValue(S,ObjPtr->entry_point_flags);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_static_data));
	return S;
}

uint8 *pack_static_data(uint8 *Stream, static_data* Objects, size_t Count)
{
	uint8* S = Stream;
	static_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->environment_code);
		
		ValueToStream(S,ObjPtr->physics_model);
		ValueToStream(S,ObjPtr->song_index);
		ValueToStream(S,ObjPtr->mission_flags);
		ValueToStream(S,ObjPtr->environment_flags);
		
		S += 4*2;
		
		BytesToStream(S,ObjPtr->level_name,LEVEL_NAME_LENGTH);
		ValueToStream(S,ObjPtr->entry_point_flags);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_static_data));
	return S;
}


uint8 *unpack_ambient_sound_image_data(uint8 *Stream, ambient_sound_image_data* Objects, size_t Count)
{
	uint8* S = Stream;
	ambient_sound_image_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->sound_index);
		StreamToValue(S,ObjPtr->volume);
		
		S += 5*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_ambient_sound_image_data));
	return S;
}

uint8 *pack_ambient_sound_image_data(uint8 *Stream, ambient_sound_image_data* Objects, size_t Count)
{
	uint8* S = Stream;
	ambient_sound_image_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->sound_index);
		ValueToStream(S,ObjPtr->volume);
		
		S += 5*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_ambient_sound_image_data));
	return S;
}


uint8 *unpack_random_sound_image_data(uint8 *Stream, random_sound_image_data* Objects, size_t Count)
{
	uint8* S = Stream;
	random_sound_image_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->sound_index);

		StreamToValue(S,ObjPtr->volume);
		StreamToValue(S,ObjPtr->delta_volume);
		StreamToValue(S,ObjPtr->period);
		StreamToValue(S,ObjPtr->delta_period);
		StreamToValue(S,ObjPtr->direction);
		StreamToValue(S,ObjPtr->delta_direction);
		StreamToValue(S,ObjPtr->pitch);
		StreamToValue(S,ObjPtr->delta_pitch);
		
		StreamToValue(S,ObjPtr->phase);
		
		S += 3*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_random_sound_image_data));
	return S;
}

uint8 *pack_random_sound_image_data(uint8 *Stream, random_sound_image_data* Objects, size_t Count)
{
	uint8* S = Stream;
	random_sound_image_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->sound_index);

		ValueToStream(S,ObjPtr->volume);
		ValueToStream(S,ObjPtr->delta_volume);
		ValueToStream(S,ObjPtr->period);
		ValueToStream(S,ObjPtr->delta_period);
		ValueToStream(S,ObjPtr->direction);
		ValueToStream(S,ObjPtr->delta_direction);
		ValueToStream(S,ObjPtr->pitch);
		ValueToStream(S,ObjPtr->delta_pitch);
		
		ValueToStream(S,ObjPtr->phase);
		
		S += 3*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_random_sound_image_data));
	return S;
}


static void StreamToGameData(uint8* &S, game_data& Object)
{
	StreamToValue(S,Object.game_time_remaining);
	StreamToValue(S,Object.game_type);
	StreamToValue(S,Object.game_options);
	StreamToValue(S,Object.kill_limit);
	StreamToValue(S,Object.initial_random_seed);
	StreamToValue(S,Object.difficulty_level);
	StreamToList(S,Object.parameters,2);
}

static void GameDataToStream(uint8* &S, game_data& Object)
{
	ValueToStream(S,Object.game_time_remaining);
	ValueToStream(S,Object.game_type);
	ValueToStream(S,Object.game_options);
	ValueToStream(S,Object.kill_limit);
	ValueToStream(S,Object.initial_random_seed);
	ValueToStream(S,Object.difficulty_level);
	ListToStream(S,Object.parameters,2);
}


uint8 *unpack_dynamic_data(uint8 *Stream, dynamic_data* Objects, size_t Count)
{
	uint8* S = Stream;
	dynamic_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->tick_count);

		StreamToValue(S,ObjPtr->random_seed);

		StreamToGameData(S,ObjPtr->game_information);
		
		StreamToValue(S,ObjPtr->player_count);
		StreamToValue(S,ObjPtr->speaking_player_index);
		
		S += 2;
		StreamToValue(S,ObjPtr->platform_count);
		StreamToValue(S,ObjPtr->endpoint_count);
		StreamToValue(S,ObjPtr->line_count);
		StreamToValue(S,ObjPtr->side_count);
		StreamToValue(S,ObjPtr->polygon_count);
		StreamToValue(S,ObjPtr->lightsource_count);
		StreamToValue(S,ObjPtr->map_index_count);
		StreamToValue(S,ObjPtr->ambient_sound_image_count);
		StreamToValue(S,ObjPtr->random_sound_image_count);
		
		StreamToValue(S,ObjPtr->object_count);
		StreamToValue(S,ObjPtr->monster_count);
		StreamToValue(S,ObjPtr->projectile_count);
		StreamToValue(S,ObjPtr->effect_count);
		StreamToValue(S,ObjPtr->light_count);
		
		StreamToValue(S,ObjPtr->default_annotation_count);
		StreamToValue(S,ObjPtr->personal_annotation_count);
		
		StreamToValue(S,ObjPtr->initial_objects_count);
		
		StreamToValue(S,ObjPtr->garbage_object_count);
		
		StreamToValue(S,ObjPtr->last_monster_index_to_get_time);
		StreamToValue(S,ObjPtr->last_monster_index_to_build_path);
		
		StreamToValue(S,ObjPtr->new_monster_mangler_cookie);
		StreamToValue(S,ObjPtr->new_monster_vanishing_cookie);	
		
		StreamToValue(S,ObjPtr->civilians_killed_by_players);
		
		StreamToList(S,ObjPtr->random_monsters_left,MAXIMUM_OBJECT_TYPES);
		StreamToList(S,ObjPtr->current_monster_count,MAXIMUM_OBJECT_TYPES);
		StreamToList(S,ObjPtr->random_items_left,MAXIMUM_OBJECT_TYPES);
		StreamToList(S,ObjPtr->current_item_count,MAXIMUM_OBJECT_TYPES);

		StreamToValue(S,ObjPtr->current_level_number);
		
		StreamToValue(S,ObjPtr->current_civilian_causalties);
		StreamToValue(S,ObjPtr->current_civilian_count);
		StreamToValue(S,ObjPtr->total_civilian_causalties);
		StreamToValue(S,ObjPtr->total_civilian_count);
		
		StreamToValue(S,ObjPtr->game_beacon.x);
		StreamToValue(S,ObjPtr->game_beacon.y);
		StreamToValue(S,ObjPtr->game_player_index);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_dynamic_data));
	return S;
}

uint8 *pack_dynamic_data(uint8 *Stream, dynamic_data* Objects, size_t Count)
{
	uint8* S = Stream;
	dynamic_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->tick_count);

		ValueToStream(S,ObjPtr->random_seed);

		GameDataToStream(S,ObjPtr->game_information);
		
		ValueToStream(S,ObjPtr->player_count);
		ValueToStream(S,ObjPtr->speaking_player_index);
		
		S += 2;
		ValueToStream(S,ObjPtr->platform_count);
		ValueToStream(S,ObjPtr->endpoint_count);
		ValueToStream(S,ObjPtr->line_count);
		ValueToStream(S,ObjPtr->side_count);
		ValueToStream(S,ObjPtr->polygon_count);
		ValueToStream(S,ObjPtr->lightsource_count);
		ValueToStream(S,ObjPtr->map_index_count);
		ValueToStream(S,ObjPtr->ambient_sound_image_count);
		ValueToStream(S,ObjPtr->random_sound_image_count);
		
		ValueToStream(S,ObjPtr->object_count);
		ValueToStream(S,ObjPtr->monster_count);
		ValueToStream(S,ObjPtr->projectile_count);
		ValueToStream(S,ObjPtr->effect_count);
		ValueToStream(S,ObjPtr->light_count);
		
		ValueToStream(S,ObjPtr->default_annotation_count);
		ValueToStream(S,ObjPtr->personal_annotation_count);
		
		ValueToStream(S,ObjPtr->initial_objects_count);
		
		ValueToStream(S,ObjPtr->garbage_object_count);
		
		ValueToStream(S,ObjPtr->last_monster_index_to_get_time);
		ValueToStream(S,ObjPtr->last_monster_index_to_build_path);
		
		ValueToStream(S,ObjPtr->new_monster_mangler_cookie);
		ValueToStream(S,ObjPtr->new_monster_vanishing_cookie);	
		
		ValueToStream(S,ObjPtr->civilians_killed_by_players);
		
		ListToStream(S,ObjPtr->random_monsters_left,MAXIMUM_OBJECT_TYPES);
		ListToStream(S,ObjPtr->current_monster_count,MAXIMUM_OBJECT_TYPES);
		ListToStream(S,ObjPtr->random_items_left,MAXIMUM_OBJECT_TYPES);
		ListToStream(S,ObjPtr->current_item_count,MAXIMUM_OBJECT_TYPES);

		ValueToStream(S,ObjPtr->current_level_number);
		
		ValueToStream(S,ObjPtr->current_civilian_causalties);
		ValueToStream(S,ObjPtr->current_civilian_count);
		ValueToStream(S,ObjPtr->total_civilian_causalties);
		ValueToStream(S,ObjPtr->total_civilian_count);
		
		ValueToStream(S,ObjPtr->game_beacon.x);
		ValueToStream(S,ObjPtr->game_beacon.y);
		ValueToStream(S,ObjPtr->game_player_index);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_dynamic_data));
	return S;
}


uint8 *unpack_object_data(uint8 *Stream, object_data* Objects, size_t Count)
{
	uint8* S = Stream;
	object_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->location.x);
		StreamToValue(S,ObjPtr->location.y);
		StreamToValue(S,ObjPtr->location.z);
		StreamToValue(S,ObjPtr->polygon);
		
		StreamToValue(S,ObjPtr->facing);
		
		StreamToValue(S,ObjPtr->shape);
		
		StreamToValue(S,ObjPtr->sequence);
		StreamToValue(S,ObjPtr->flags);
		StreamToValue(S,ObjPtr->transfer_mode);
		StreamToValue(S,ObjPtr->transfer_period);
		StreamToValue(S,ObjPtr->transfer_phase);
		StreamToValue(S,ObjPtr->permutation);
		
		StreamToValue(S,ObjPtr->next_object);
		StreamToValue(S,ObjPtr->parasitic_object);
		
		StreamToValue(S,ObjPtr->sound_pitch);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_object_data));
	return S;
}

uint8 *pack_object_data(uint8 *Stream, object_data* Objects, size_t Count)
{
	uint8* S = Stream;
	object_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->location.x);
		ValueToStream(S,ObjPtr->location.y);
		ValueToStream(S,ObjPtr->location.z);
		ValueToStream(S,ObjPtr->polygon);
		
		ValueToStream(S,ObjPtr->facing);
		
		ValueToStream(S,ObjPtr->shape);
		
		ValueToStream(S,ObjPtr->sequence);
		ValueToStream(S,ObjPtr->flags);
		ValueToStream(S,ObjPtr->transfer_mode);
		ValueToStream(S,ObjPtr->transfer_period);
		ValueToStream(S,ObjPtr->transfer_phase);
		ValueToStream(S,ObjPtr->permutation);
		
		ValueToStream(S,ObjPtr->next_object);
		ValueToStream(S,ObjPtr->parasitic_object);
		
		ValueToStream(S,ObjPtr->sound_pitch);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_object_data));
	return S;
}


uint8 *unpack_damage_definition(uint8 *Stream, damage_definition* Objects, size_t Count)
{
	uint8* S = Stream;
	damage_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->base);
		StreamToValue(S,ObjPtr->random);
		StreamToValue(S,ObjPtr->scale);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_damage_definition));
	return S;
}

uint8 *pack_damage_definition(uint8 *Stream, damage_definition* Objects, size_t Count)
{
	uint8* S = Stream;
	damage_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->base);
		ValueToStream(S,ObjPtr->random);
		ValueToStream(S,ObjPtr->scale);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_damage_definition));
	return S;
}
