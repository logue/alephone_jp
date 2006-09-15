#ifndef __TEXTURES_H
#define __TEXTURES_H

/*
TEXTURES.H

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

Saturday, August 20, 1994 12:08:34 PM
*/

//#include    "cseries.h"
#include "header.h"


/* ---------- structures */

//enum /* bitmap flags */

//struct bitmap_definition
//const int SIZEOF_bitmap_definition = 30;

/* ---------- prototypes/TEXTURES.C */

/* assumes pixel data follows bitmap_definition structure immediately */
//pixel8 *calculate_bitmap_origin(struct bitmap_definition *bitmap);

/* initialize bytes_per_row, height and row_address[0] before calling */
//void precalculate_bitmap_row_addresses(struct bitmap_definition *texture);

//void map_bytes(byte *buffer, byte *table, long size);
//void remap_bitmap(struct bitmap_definition *bitmap,	pixel8 *table);

#endif

