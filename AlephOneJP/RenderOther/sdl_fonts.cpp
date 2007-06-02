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
#if 0
void initialize_fonts(void)
{
        logContext("initializing fonts");
	// Open font resource files
	bool found = false;
	vector<DirectorySpecifier>::const_iterator i = data_search_path.begin(), end = data_search_path.end();
	while (i != end) {
		FileSpecifier fonts = *i + "Fonts";

		if (open_res_file(fonts))
			found = true;
		i++;
	}
	if (!found) {
		logFatal("Can't open font resource file");
/*
                vector<DirectorySpecifier>::const_iterator i = data_search_path.begin(), end = data_search_path.end();
                while (i != end) {
                        FileSpecifier fonts = *i + "Fonts";
                        fdprintf(fonts.GetPath());
                        i++;
                }
*/                
		exit(1);
	}
}


/*
 *  Load font from resources and allocate sdl_font_info
 */

sdl_font_info *load_font(const TextSpec &spec)
{
	sdl_font_info *info = NULL;

	// Look for ID/size in list of loaded fonts
	id_and_size_t id_and_size(spec.font, spec.size);
	font_list_t::const_iterator it = font_list.find(id_and_size);
	if (it != font_list.end()) {	// already loaded
		info = it->second;
		info->ref_count++;
		return info;
	}

	// Load font family resource
	LoadedResource fond;
	if (!get_resource(FOUR_CHARS_TO_INT('F', 'O', 'N', 'D'), spec.font, fond)) {
		fprintf(stderr, "Font family resource for font ID %d not found\n", spec.font);
		return NULL;
	}
	SDL_RWops *p = SDL_RWFromMem(fond.GetPointer(), (int)fond.GetLength());
	assert(p);

	// Look for font size in association table
	SDL_RWseek(p, 52, SEEK_SET);
	int num_assoc = SDL_ReadBE16(p) + 1;
	while (num_assoc--) {
		int size = SDL_ReadBE16(p);
		SDL_ReadBE16(p); // skip style
		int id = SDL_ReadBE16(p);
		if (size == spec.size) {

			// Size found, load bitmap font resource
			info = new sdl_font_info;
			if (!get_resource(FOUR_CHARS_TO_INT('N', 'F', 'N', 'T'), id, info->rsrc))
				get_resource(FOUR_CHARS_TO_INT('F', 'O', 'N', 'T'), id, info->rsrc);
			if (info->rsrc.IsLoaded()) {

				// Found, switch stream to font resource
				SDL_RWclose(p);
				p = SDL_RWFromMem(info->rsrc.GetPointer(), (int)info->rsrc.GetLength());
				assert(p);
				void *font_ptr = info->rsrc.GetPointer(true);

				// Read font information
				SDL_RWseek(p, 2, SEEK_CUR);
				info->first_character = static_cast<uint8>(SDL_ReadBE16(p));
				info->last_character = static_cast<uint8>(SDL_ReadBE16(p));
				SDL_RWseek(p, 2, SEEK_CUR);
				info->maximum_kerning = SDL_ReadBE16(p);
				SDL_RWseek(p, 2, SEEK_CUR);
				info->rect_width = SDL_ReadBE16(p);
				info->rect_height = SDL_ReadBE16(p);
				SDL_RWseek(p, 2, SEEK_CUR);
				info->ascent = SDL_ReadBE16(p);
				info->descent = SDL_ReadBE16(p);
				info->leading = SDL_ReadBE16(p);
				int bytes_per_row = SDL_ReadBE16(p) * 2;

				//printf(" first %d, last %d, max_kern %d, rect_w %d, rect_h %d, ascent %d, descent %d, leading %d, bytes_per_row %d\n",
				//	info->first_character, info->last_character, info->maximum_kerning,
				//	info->rect_width, info->rect_height, info->ascent, info->descent, info->leading, bytes_per_row);

				// Convert bitmap to pixmap (1 byte/pixel)
				info->bytes_per_row = bytes_per_row * 8;
				uint8 *src = (uint8 *)font_ptr + SDL_RWtell(p);
				uint8 *dst = info->pixmap = (uint8 *)malloc(info->rect_height * info->bytes_per_row);
				assert(dst);
				for (int y=0; y<info->rect_height; y++) {
					for (int x=0; x<bytes_per_row; x++) {
						uint8 b = *src++;
						*dst++ = (b & 0x80) ? 0xff : 0x00;
						*dst++ = (b & 0x40) ? 0xff : 0x00;
						*dst++ = (b & 0x20) ? 0xff : 0x00;
						*dst++ = (b & 0x10) ? 0xff : 0x00;
						*dst++ = (b & 0x08) ? 0xff : 0x00;
						*dst++ = (b & 0x04) ? 0xff : 0x00;
						*dst++ = (b & 0x02) ? 0xff : 0x00;
						*dst++ = (b & 0x01) ? 0xff : 0x00;
					}
				}
				SDL_RWseek(p, info->rect_height * bytes_per_row, SEEK_CUR);

				// Set table pointers
				int table_size = info->last_character - info->first_character + 3;	// Tables contain 2 additional entries
				info->location_table = (uint16 *)((uint8 *)font_ptr + SDL_RWtell(p));
				byte_swap_memory(info->location_table, _2byte, table_size);
				SDL_RWseek(p, table_size * 2, SEEK_CUR);
				info->width_table = (int8 *)font_ptr + SDL_RWtell(p);

				// Add font information to list of known fonts
				info->ref_count++;
				font_list[id_and_size] = info;

			} else {
				delete info;
				info = NULL;
				fprintf(stderr, "Bitmap font resource ID %d not found\n", id);
			}
		}
	}

	// Free resources
	SDL_RWclose(p);
	return info;
}


/*
 *  Unload font, free sdl_font_info
 */

void unload_font(sdl_font_info *info)
{
	// Look for font in list of loaded fonts
	font_list_t::const_iterator i = font_list.begin(), end = font_list.end();
	while (i != end) {
		if (i->second == info) {

			// Found, decrement reference counter and delete
			info->ref_count--;
			if (info->ref_count <= 0) {
				delete info;
				font_list.erase(i->first);
				return;
			}
		}
		i++;
	}
}
# else
void initialize_fonts(void)
{
	logContext("initializing fonts");
}

#define FONTJ12 "shnmk12.bdf"
#define FONTE12 "shnm6x12a.bdf"
#define FONTJ10 "knj10.bdf"
#define FONTE10 "5x10a.bdf"
// 0001 1100 0000 0000
uint16 sjis2jis(char** data) {
	char d1,d2;
	uint8 c1,c2;
	uint16 ret;
	d1 = *((*data)++);
	if( d1 > 0) { return d1; }
	c1 = 256 + d1; 
	d2 = *((*data)++);
	c2 = d2 < 0 ? 256 + d2 : d2;
	if( c2 < 0x9f && c2 > 0x3f) {
		if( c1 < 0xa0 && c1 > 0x80) {
			c1 = (c1 - 0x70) * 2 - 1;
		} else if( c1 < 0xf0 && c1 > 0xdf) {
			c1 = (c1 - 0xb0) * 2 - 1;
		} else { (*data)--; return c1; }
		c2 -= c2 > 0x7f ? 0x20 : 0x1f;
	} else {
		if( c1 < 0xa0 && c1 > 0x80) {
			c1 = (c1 - 0x70) * 2;
		} else if( c1 < 0xf0 && c1 > 0xbf) {
			c1 = (c1 - 0xb0) * 2;
		} else { (*data)--; return c1; }
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
#endif