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
 *  sdl_fonts.cpp - SDL font handling
 *
 *  Written in 2000 by Christian Bauer
 */

#include "cseries.h"
#include "sdl_fonts.h"
#include "byte_swapping.h"
#include "resource_manager.h"
#include "FileHandler.h"
#include "Logging.h"

#include <SDL_endian.h>
#include <vector>
#include <map>

#ifndef NO_STD_NAMESPACE
using std::vector;
using std::pair;
using std::map;
#endif


// Global variables
typedef pair<int, int> id_and_size_t;
typedef map<id_and_size_t, sdl_font_info *> font_list_t;
static font_list_t font_list;				// List of all loaded fonts

// From shell_sdl.cpp
extern vector<DirectorySpecifier> data_search_path;


/*
 *  Initialize font management
 */

void initialize_fonts(void)
{
        logContext("initializing fonts");
}

#define FONTJ12 "shnmk12.bdf"
#define FONTE12 "shnm6x12a.bdf"
#define FONTJ10 "knj10.bdf"
#define FONTE10 "5x10a.bdf"
// 0001 1100 0000 0000
uint16 sjis2jis(const char** datal) {
	char*& data = *datal;
	char d1,d2;
	uint8 c1,c2;
	uint16 ret;
	d1 = *data++;
	if( d1 > 0) { return d1; }
	c1 = 256 + d1; 
	d2 = *data++;
	c2 = d2 < 0 ? 256 + d2 : d2;
	if( c2 < 0x9f && c2 > 0x3f) {
		if( c1 < 0xa0 && c1 > 0x80) {
			c1 = (c1 - 0x70) * 2 - 1;
		} else if( c1 < 0xf0 && c1 > 0xdf) {
			c1 = (c1 - 0xb0) * 2 - 1;
		} else { data--; return c1; }
		c2 -= c2 > 0x7f ? 0x20 : 0x1f;
	} else {
		if( c1 < 0xa0 && c1 > 0x80) {
			c1 = (c1 - 0x70) * 2;
		} else if( c1 < 0xf0 && c1 > 0xbf) {
			c1 = (c1 - 0xb0) * 2;
		} else { data--; return c1; }
		c2 -= 0x7e;
	}
	ret = ((uint16)c1 << 8) | c2;
//	fprintf(stderr,"%04x ",(*(uint16*)(data-2)));
	return ret;
}
// 010000000000 0000
//            1
// 0-> 15 1->14

static void ParseChar(uint8* pixs, FILE* fp, int xsize, int ysize) {
	char buf[256];
	int x,y;
	int xs = xsize > 8 ? 15 : 7;
	for (y = 0; y <= ysize; y++) {
		fgets(buf, 256, fp);
		if(strstr(buf,"BITMAP") ) { continue; }
		if(strstr(buf,"ENDCHAR") ) { return; }
		int txt = strtol(buf,0,16);
		for(x = 0; x < xsize;x++) {
			pixs[(y)*(ysize)+x] = (txt & ( 1 << (xs - x))) ? 1 : 0;
		}
	}
}

sdl_font_info *load_font(const TextSpec &spec)
{
	const char* epath, *jpath;
	FILE* ep, *jp;
	sdl_font_info *ret = new sdl_font_info;
	ret->location_table = new uint32 [65536];
	ret->width_table = new int8 [65536];
	memset(ret->location_table,0,65536*2);
	memset(ret->width_table,0,65536);
	if(spec.size < 10 ) { 
		epath = FONTE10; 
		jpath = FONTJ10;
		ret->ascent = 8;
		ret->descent = 2;
		ret->leading = 0;
		ret->bytes_per_row = 10;
	} else { 
		epath = FONTE12; 
		jpath = FONTJ12;
		ret->ascent = 10;
		ret->descent = 2;
		ret->leading = 0;
		ret->bytes_per_row = 12;
	}
	int ln = ret->bytes_per_row;
	int dsize = ln * ln;
	ep = fopen(epath,"r");
	if( ! ep ) { fprintf(stderr,"Cannot open English Font file \n"); exit(1); }
	jp = fopen(jpath,"r");
	if( ! jp ) { fprintf(stderr,"Cannot open Japanese Font file \n"); exit(1); }
	ret->pixmap = new uint8 [(96*96+256)*dsize];
	const int BUF = 256;
	char buf[BUF];
	int index;
	while(fgets(buf, BUF, ep)) {
		if( buf[0] == 'E' && strstr(buf, "ENCODING") != NULL) {
			char* p = strchr(buf, ' ');
			index = strtol(p, 0, 10);
			if( index < 0xa0 && index > 0x80 || index < 0xf0 && index > 0xbf || index < 32) {
				continue;
			}
			do {
				fgets(buf, BUF, ep);
			} while (strcmp(buf, "BITMAP\n"));
			uint8* in = ret->pixmap + (dsize) * index;
			ret->width_table[index] = ln / 2;
			ret->location_table[index] = in - ret->pixmap;
			ParseChar(in,ep,ln/2,ln);
			
		}
	}
	uint8* in = ret->pixmap + dsize * 256;
	while(fgets(buf,BUF,jp)) {		
		if( buf[0] == 'E' && strstr(buf, "ENCODING") != NULL) {
			char* p = strchr(buf, ' ');
			index = strtol(p, 0, 10);
			do {
				fgets(buf, BUF, jp);
			} while (strcmp(buf, "BITMAP\n"));
			ret->width_table[index] = ln;
			ret->location_table[index] = in - ret->pixmap;
			ParseChar(in,jp,ln,ln);
			in += dsize;
		}
		
	}
	fclose(ep);
	fclose(jp);
	return ret;
}


/*
 *  Unload font, free sdl_font_info
 */

void unload_font(sdl_font_info *info)
{
	delete [] info->pixmap;
	info->pixmap = NULL;
	delete [] info->width_table;
	delete [] info->location_table;
	delete info;
}
