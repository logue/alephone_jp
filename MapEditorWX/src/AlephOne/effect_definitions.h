#ifndef __EFFECT_DEFINITIONS_H
#define __EFFECT_DEFINTIIONS_H
//#include "stdafx.h"
#include "map.h"
#include "mysound.h"
#include "effects.h"

/*
EFFECT_DEFINITIONS.H

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

Tuesday, May 31, 1994 5:21:28 PM

Feb 3, 2000 (Loren Petrich):
	Added Jjaro-texture effects
	Added VacBob effects
*/

/* ---------- constants */


/* ---------- structures */


/* ---------- effect definitions */

extern struct effect_definition effect_definitions[NUMBER_OF_EFFECT_TYPES];

// Added for the convenience of the 1-2-3 Converter
uint8 *unpack_effect_definition(uint8 *Stream, effect_definition *Objects, size_t Count);
uint8 *pack_effect_definition(uint8 *Stream, effect_definition *Objects, size_t Count);

#endif
