#pragma once
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

*/

/* 
 *  shapes_sdl.cpp - Shapes handling, SDL specific stuff (included by shapes.cpp)
 *
 *  Written in 2000 by Christian Bauer
 */

/*
Oct 19, 2000 (Loren Petrich):
	Added graceful degradation in the case of frames or bitmaps not being found;
	get_shape_surface() returns NULL when that happens
        
October 2001 (Woody Zenfell):
        Changes to get_shape_surface() for RLE shapes, shading-table lookups, large
        low-level-shape indices, and quarter-size shapes
        (these for the w_players_in_game2 widget, primarily)
*/

#include <SDL_endian.h>
#include "screen_shared.h"

#include "byte_swapping.h"
#include "textures.h"
#include "collection_definition.h"

void initialize_shape_handler();
void open_shapes_file(FileSpecifier& File);
void close_shapes_file(void);
void shutdown_shape_handler(void);
extern SDL_Surface *screenSurface;
struct collection_header *get_collection_header(short collection_index);

/*
 *  Initialize shapes handling
 */
/*
static void initialize_pixmap_handler()
{
	// nothing to do
}


/*
 *  Convert shape to surface
 */

// ZZZ extension: pass out (if non-NULL) a pointer to a block of pixel data -
// caller should free() that storage after freeing the returned surface.
// Only needed for RLE-encoded shapes.
// Note that default arguments are used to make this function
// source-code compatible with existing usage.
// Note also that inShrinkImage currently only applies to RLE shapes.
SDL_Surface *get_shape_surface(int shape, int inCollection, byte** outPointerToPixelData,
                               float inIllumination, bool inShrinkImage,
                               SDL_Color *palette);


/*
 *  Load collection
 */

bool load_collection(short collection_index, bool strip);


/*
 *  Unload collection
 */

void unload_collection(struct collection_header *header);
