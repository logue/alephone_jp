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

#include <boost/tokenizer.hpp>
#include <string>

#ifndef NO_STD_NAMESPACE
using std::vector;
using std::pair;
using std::map;
#endif

#ifdef HAVE_SDL_TTF
#include <boost/tuple/tuple_comparison.hpp>
#include "preferences.h" // smooth_font
#include "AlephSansMono-Bold.h"
#endif

// Global variables
typedef pair<int, int> id_and_size_t;
typedef map<id_and_size_t, sdl_font_info *> font_list_t;
static font_list_t font_list;				// List of all loaded fonts

#ifdef HAVE_SDL_TTF
typedef pair<TTF_Font *, int> ref_counted_ttf_font_t;
typedef map<ttf_font_key_t, ref_counted_ttf_font_t> ttf_font_list_t;
static ttf_font_list_t ttf_font_list;
#endif

// From shell_sdl.cpp
extern vector<DirectorySpecifier> data_search_path;


/*
 *  Initialize font management
 */

#ifdef HAVE_SDL_TTF
extern void fix_missing_overhead_map_fonts();
extern void fix_missing_interface_fonts();
#endif

void initialize_fonts(void)
{
        logContext("initializing fonts");
	
		// use our own built-in font
		fix_missing_overhead_map_fonts();
		fix_missing_interface_fonts();

	
}



// sdl_font_info::_draw_text is in screen_drawing.cpp

int8 ttf_font_info::char_width(uint16 c, uint16 style) const
{
	int advance;
	TTF_GlyphMetrics(get_ttf(style), c, 0, 0, 0, 0, &advance);
	
	return advance;
}
uint16 ttf_font_info::_text_width(const char *text, uint16 style, bool utf8) const
{
	return _text_width(text, strlen(text), style, utf8);
}





font_info *load_font(const TextSpec &spec) {
	ttf_font_info* info = new ttf_font_info();
	if(!TTF_WasInit() && TTF_Init()==-1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}	
	info->font = TTF_OpenFont("Fonts.ttf", spec.size);
	return info;
}



void ttf_font_info::_unload()
{
	delete this;
}

void unload_font(font_info *info)
{
	info->_unload();
}


#include "converter.h"
uint16 ttf_font_info::_text_width(const char *text, size_t length, uint16 style, bool utf8) const
{
	int width = 0;
	int cst = TTF_GetFontStyle(font), css = TTF_STYLE_NORMAL;
	if( style & styleBold ) {
		css |= TTF_STYLE_BOLD;
	}
	if( style & styleItalic ) {
		css |= TTF_STYLE_ITALIC;
	}
	if( style & styleUnderline ) {
		css |= TTF_STYLE_UNDERLINE;
	}
	TTF_SetFontStyle(font,css);
	if (utf8)
	{
		TTF_SizeUTF8(font, text, &width, 0);
	}
	else
	{
		uint16 *temp = utf82utf16(text, length);
		TTF_SizeUNICODE(font, temp, &width, 0);
	}
	TTF_SetFontStyle(font,cst);
	return width;
}

int ttf_font_info::_trunc_text(const char *text, int max_width, uint16 style) const
{
	int width;
	uint16* temp = utf82utf16(text, 1024);
	TTF_SizeUNICODE(font, temp, &width, 0);
	if (width < max_width) return strlen(text);

	int num = strlen(text) - 1;

	while (num > 0 && width > max_width)
	{
		num--;
		temp[num] = 0x0;
		TTF_SizeUNICODE(get_ttf(style), temp, &width, 0);
	}

	return num;
}


uint16 font_info::text_width(const char *text, uint16 style, bool utf8) const
{
	if (style & styleShadow)
		return _text_width(text, style, utf8) + 1;
	else
		return _text_width(text, style, utf8);
}

uint16 font_info::text_width(const char *text, size_t length, uint16 style, bool utf8) const
{
	if (style & styleShadow)
		return _text_width(text, length, style, utf8) + 1;
	else
		return _text_width(text, length, style, utf8);
}

static 	inline bool style_code(char c)
{
	switch(tolower(c)) {
	case 'p':
	case 'b':
	case 'i':
	case 'l':
	case 'r':
	case 'c':
	case 's':
		return true;
		break;
	default:
		return false;
	}
}

class style_separator
{
public:
	bool operator() (std::string::const_iterator& next, std::string::const_iterator end, std::string& token)
	{
		if (next == end) return false;

		token = std::string();

		// if we start with a token, return it
		if (*next == '|' && next + 1 != end && style_code(*(next + 1)))
		{
			token += *next;
			++next;
			token += *next;
			++next;
			return true;
		}

		token += *next;
		++next;

		// add characters until we hit a token
		for (;next != end && !(*next == '|' && next + 1 != end && style_code(*(next + 1))); ++next)
		{
			token += *next;
		}

		return true;
	}

	void reset() { }

};

static inline bool is_style_token(const std::string& token)
{
	return (token.size() == 2 && token[0] == '|' && style_code(token[1]));
}

static void update_style(uint16& style, const std::string& token)
{
	if (tolower(token[1]) == 'p')
		style &= ~(styleBold | styleItalic);
	else if (tolower(token[1]) == 'b')
	{
		style |= styleBold;
		style &= ~styleItalic;
	}
	else if (tolower(token[1]) == 'i')
	{
		style |= styleItalic;
		style &= ~styleBold;
	}
}


int font_info::draw_styled_text(SDL_Surface *s, const std::string& text, size_t length, int x, int y, uint32 pixel, uint16 style, bool utf8) const 
{
	int width = 0;
	boost::tokenizer<style_separator> tok(text.begin(), text.begin() + length);
	for (boost::tokenizer<style_separator>::iterator it = tok.begin(); it != tok.end(); ++it)
	{
		if (is_style_token(*it))
		{
			update_style(style, *it);
		}
		else
		{
			if (style & styleShadow)
			{
				_draw_text(s, it->c_str(), it->size(), x + width + 1, y + 1, SDL_MapRGB(s->format, 0x0, 0x0, 0x0), style, utf8);
			}
			width += _draw_text(s, it->c_str(), it->size(), x + width, y, pixel, style, utf8);
		}
	}

	return width;
}

int font_info::styled_text_width(const std::string& text, size_t length, uint16 style, bool utf8) const 
{
	int width = 0;
	boost::tokenizer<style_separator> tok(text.begin(), text.begin() + length);
	for (boost::tokenizer<style_separator>::iterator it = tok.begin(); it != tok.end(); ++it)
	{
		if (is_style_token(*it))
		{
			update_style(style, *it);
		}
		else
		{
			width += _text_width(it->c_str(), it->length(), style, utf8);
		}
	}

	if (style & styleShadow)
		return width + 1;
	else
		return width;
}

int font_info::trunc_styled_text(const std::string& text, int max_width, uint16 style) const
{
	if (style & styleShadow)
	{
		max_width -= 1;
		style &= (~styleShadow);
	}

	int length = 0;
	boost::tokenizer<style_separator> tok(text);
	for (boost::tokenizer<style_separator>::iterator it = tok.begin(); it != tok.end(); ++it)
	{
		if (is_style_token(*it))
		{
			update_style(style, *it);
			length += 2;
		}
		else
		{
			int additional_length = _trunc_text(it->c_str(), max_width, style);
			max_width -= _text_width(it->c_str(), additional_length, style);
			length += additional_length;
			if (additional_length < it->size())
				return length;
		}
	}

	return length;
}

std::string font_info::style_at(const std::string& text, std::string::const_iterator pos, uint16 style) const
{
	boost::tokenizer<style_separator> tok(text.begin(), pos);
	for (boost::tokenizer<style_separator>::iterator it = tok.begin(); it != tok.end(); ++it)
	{
		if (is_style_token(*it))
			update_style(style, *it);
	}
	
	if (style & styleBold)
		return string("|b");
	else if (style & styleItalic)
		return string("|i");
	else
		return string();
}

int font_info::draw_text(SDL_Surface *s, const char *text, size_t length, int x, int y, uint32 pixel, uint16 style, bool utf8) const
{
	if (style & styleShadow)
	{
		_draw_text(s, text, length, x + 1, y + 1, SDL_MapRGB(s->format, 0x0, 0x0, 0x0), style, utf8);
	}

	_draw_text(s, text, length, x, y, pixel, style, utf8);
}

int font_info::trunc_text(const char *text, int max_width, uint16 style) const
{
	if (style & styleShadow)
		return _trunc_text(text, max_width - 1, style);
	else
		return _trunc_text(text, max_width, style);
}
