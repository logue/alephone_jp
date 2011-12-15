/*

	Copyright (C) 1991-2001 and beyond by Bungie Studios, Inc.
	and the "Aleph One" developers.
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU General Public License for more details.

	This license is contained in the file "COPYING",
	which is included with this source code; it is available online at
	http://www.gnu.org/licenses/gpl.html

	Font handler
	by Loren Petrich,
	December 17, 2000
	
	This is for specifying and working with text fonts

Dec 25, 2000 (Loren Petrich):
	Added OpenGL-rendering support

Dec 31, 2000 (Loren Petrich):
	Switched to a 32-bit intermediate GWorld, so that text antialiasing
	will work properly.

Jan 12, 2001 (Loren Petrich):
	Fixed MacOS version of TextWidth() -- uses current font
*/

#include "cseries.h"
#include <stdio.h>
#ifdef __MVCPP__
#include <windows.h>
#endif

#ifdef HAVE_OPENGL
#include "OGL_Headers.h"
#include "OGL_Blitter.h"
#endif

#include <math.h>
#include <string.h>
#include "FontHandler.h"

#include "shape_descriptors.h"
#include "screen_drawing.h"

#ifdef HAVE_OPENGL
set<FontSpecifier*> *FontSpecifier::m_font_registry = NULL;
#endif

// MacOS-specific: stuff that gets reused
// static CTabHandle Grays = NULL;

// Font-specifier equality and assignment:

bool FontSpecifier::operator==(FontSpecifier& F)
{
	if (strncmp(NameSet,F.NameSet,NameSetLen) != 0) return false;
	if (Size != F.Size) return false;
	if (Style != F.Style) return false;
	if (strncmp(File,F.File,NameSetLen) != 0) return false;
	return true;
}

FontSpecifier& FontSpecifier::operator=(FontSpecifier& F)
{
	memcpy(NameSet,F.NameSet,NameSetLen);
	Size = F.Size;
	Style = F.Style;
	memcpy(File,F.File,NameSetLen);
	return *this;
}

FontSpecifier::~FontSpecifier()
{
#ifdef HAVE_OPENGL
	OGL_Reset(false);
#endif
}

// Initializer: call before using because of difficulties in setting up a proper constructor:

void FontSpecifier::Init()
{
#ifdef SDL
	Info = NULL;
#endif
	Update();
#ifdef HAVE_OPENGL
				for(int n = 0; n < 256; ++n ) {
					OGL_Texture[n] = NULL;
				}
#endif
}


// MacOS- and SDL-specific stuff
#if defined(mac)

// Cribbed from _get_font_line_spacing() and similar functions in screen_drawing.cpp

void FontSpecifier::Update()
{
	// csfonts -- push old font
	TextSpec OldFont;
	GetFont(&OldFont);
	
	// Parse the font spec to find the font ID;
	// if it is not set, then it is assumed to be the system font
	ID = 0;
	
	Str255 Name;
	
	char *NamePtr = FindNextName(NameSet);
	
	while(NamePtr)
	{
		char *NameEndPtr = FindNameEnd(NamePtr);
		
		// Make a Pascal string out of the name
		int NameLen = MIN(NameEndPtr - NamePtr, 255);
		Name[0] = NameLen;
		memcpy(Name+1,NamePtr,NameLen);
		Name[NameLen+1] = 0;
		// dprintf("Name, Len: <%s>, %d",Name+1,NameLen);
		
		// MacOS ID->name translation
		GetFNum(Name,&ID);
		// dprintf("ID = %d",ID);
		if (ID != 0) break;
		
		NamePtr = FindNextName(NameEndPtr);
	}
	
	// Get the other font features
	Use();
	FontInfo Info;
	GetFontInfo(&Info);
	
	Ascent = Info.ascent;
	Descent = Info.descent;
	Leading = Info.leading;
	Height = Ascent + Leading;
	LineSpacing = Ascent + Descent + Leading;

	for (int k=0; k<256; k++)
		Widths[k] = ::CharWidth(k);
	
	// pop old font
	SetFont(&OldFont);
}


void FontSpecifier::Use()
{
	// MacOS-specific:
	TextFont(ID);
	TextFace(Style);
	TextSize(Size);
}


int FontSpecifier::TextWidth(const char *Text)
{
	// csfonts -- push old font
	TextSpec OldFont;
	GetFont(&OldFont);
	
	// Set to use current font
	Use();
	
	int Len = MIN(strlen(Text),255);
	// MacOS-specific; note the :: for getting the top-level function instead of a member one
	return int(::TextWidth(Text,0,Len));
	
	// pop old font
	SetFont(&OldFont);
}

#elif defined(SDL)

void FontSpecifier::Update()
{
	// Clear away
	if (Info) {
		unload_font(Info);
		Info = NULL;
	}
		
	TextSpec Spec;
	// Simply implements format "#<value>"; may want to generalize this
	if (File[0] == '#') 
	{
		short ID;
		sscanf(File+1, "%hd", &ID);
		
		Spec.font = ID;
	}
	else
	{
		Spec.font = -1; // no way to fall back :(
		Spec.normal = File;
	}

	Spec.size = Size;
	Spec.style = Style;
	Spec.adjust_height = AdjustLineHeight;
//				Spec.normal = "mono";
	Info = load_font(Spec);
	
	if (Info) {
		Ascent = Info->get_ascent();
		Descent = Info->get_descent();
		Leading = Info->get_leading();
		Height = Ascent + Leading;
		LineSpacing = Ascent + Descent + Leading;
		for (int k=0; k<256; k++)
			Widths[k] = char_width(k, Info, Style);
	} else
		Ascent = Descent = Leading = Height = LineSpacing = 0;
}

// Defined in screen_drawing_sdl.cpp
extern int8 char_width(uint8 c, const sdl_font_info *font, uint16 style);

int FontSpecifier::TextWidth(const char *text)
{
	// Japaneese font(assume text is shiftjis)
	return Info->text_width(text, 0,false);
}

#endif

#ifdef HAVE_OPENGL
void FontSpecifier::render_text_(int n, const char* str) {
	if( OGL_Texture[n] )
		return;
	// Put some padding around each glyph so as to avoid clipping i
	const int Pad = 1;
	int ascent_p = Ascent + Pad, descent_p = Descent + Pad;		
	int GlyphHeight = ascent_p + descent_p;

	int TotalWidth = TextWidth(str)+Pad*2;
	Widths[n] = TotalWidth;
	TxtrWidth[n] = MAX(64, NextPowerOfTwo(TotalWidth));
		
	// Find the character starting points and counts
	TxtrHeight[n] = MAX(64, NextPowerOfTwo(GlyphHeight));
		
		
	// Render the font glyphs into the SDL surface
	SDL_Surface* s = SDL_CreateRGBSurface(SDL_SWSURFACE, TxtrWidth[n], TxtrHeight[n], 32, 0xff0000, 0x00ff00, 0x0000ff, 0);
	if (s == NULL)
		return;
	// Set background to black
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 0, 0, 0));
	Uint32 White = SDL_MapRGB(s->format, 0xFF, 0xFF, 0xFF);
		
	// Copy to surface
	::draw_text(s, str, strlen(str), 1, ascent_p, White, Info, Style);
		
	OGL_Texture[n] = new uint8[GetTxtrSize(n)*2];
	// Copy the SDL surface into the OpenGL texture
	uint8 *PixBase = (uint8 *)s->pixels;
	int Stride = s->pitch;
 	
	for (int k=0; k<TxtrHeight[n]; k++)
	{
		uint8 *SrcPxl = PixBase + k*Stride + 1;	// Use one of the middle channels (red or green or blue)
		uint8 *DstPxl = OGL_Texture[n] + 2*k*TxtrWidth[n];
		for (int m=0; m<TxtrWidth[n]; m++)
		{
			*(DstPxl++) = 0xff;	// Base color: white (will be modified with glColorxxx())
			*(DstPxl++) = *SrcPxl;
			SrcPxl += 4;
		}
	}
	
	// Clean up
	SDL_FreeSurface(s);
				
	// OpenGL stuff starts here 	
	// Load texture
	glBindTexture(GL_TEXTURE_2D,TxtrID[n]);

		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, 
								 TxtrWidth[n], TxtrHeight[n],
								 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, OGL_Texture[n]);
		
		// Allocate and create display lists of rendering commands

		GLfloat TWidNorm = GLfloat(1)/TxtrWidth[n];
		GLfloat THtNorm = GLfloat(1)/TxtrHeight[n];
		GLfloat Bottom = (THtNorm*GlyphHeight);
		GLfloat Right = TWidNorm*Widths[n];
		glNewList(DispList+n, GL_COMPILE);
 			
		// Move to the current glyph's (padded) position
		glTranslatef(-Pad,0,0);
 			
		// Draw the glyph rectangle
		// Due to a bug in MacOS X Classic OpenGL, glVertex2s() was changed to glVertex2f()
		glBegin(GL_POLYGON); 			
			glTexCoord2f(0,0); glVertex2d(0,-ascent_p);
			glTexCoord2f(Right,0); glVertex2d(Widths[n],-ascent_p);
			glTexCoord2f(Right,Bottom); glVertex2d(Widths[n],descent_p);
			glTexCoord2f(0,Bottom); glVertex2d(0,descent_p);
		glEnd();
		
		// Move to the next glyph's position
		glTranslated(Widths[n]-Pad,0,0);
		
		glEndList();
		
}
// Reset the OpenGL fonts; its arg indicates whether this is for starting an OpenGL session
// (this is to avoid texture and display-list memory leaks and other such things)
void FontSpecifier::OGL_Reset(bool IsStarting)
{
	// Don't delete these if there is no valid texture;
	// that indicates that there are no valid texture and display-list ID's.
	if (!IsStarting && OGL_Texture[1] )	
	{
		glDeleteTextures(256,TxtrID);
		glDeleteLists(DispList,256);
		OGL_Deregister(this);
		for(int n = 0; n < 256; ++n ) {
			// Invalidates whatever texture had been present
			if (OGL_Texture[n])
			{
				delete [] OGL_Texture[n];
				OGL_Texture[n] = NULL;
			}
		}
	}
	textMap.clear();
			
	if (!IsStarting)
			return;
	glGenTextures(256,TxtrID);
	DispList = glGenLists(256);
	OGL_Register(this);
	// Put some padding around each glyph so as to avoid clipping i
	for(int n = 1; n < 128; ++n ) {
		char str[] = { n, 0 };
		render_text_(n, str);
	}
}

#include "converter.h"
// Renders a C-style string in OpenGL.
// assumes screen coordinates and that the left baseline point is at (0,0).
// Alters the modelview matrix so that the next characters will be drawn at the proper place.
// One can surround it with glPushMatrix() and glPopMatrix() to remember the original.
void FontSpecifier::OGL_Render(const char *Text)
{
	const char* tp = Text;

	// Bug out if no texture to render
	if (!OGL_Texture[33])
	{
		OGL_Reset(true);
		if (!OGL_Texture[33]) return;
	}
	glPushAttrib(GL_ENABLE_BIT);
			
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	while(*tp) {
		if( (unsigned char)*tp < 128 ) {
			glBindTexture(GL_TEXTURE_2D,TxtrID[*tp]);
			glCallList(DispList+*tp);
			tp++;
		} else {
			std::string buffer("");
			unsigned char tc, tc2;
			do {
				buffer += *tp;
				tc = *tp++;
				tc2 = *tp;
				char tcc = *tp;
				if( isJChar(tc) && is2ndJChar(tc2) ) {
					buffer += tcc;
					tp++;
				}
			} while( *tp && tc > 127 ) ;

			if( int re = textMap[buffer] ) {
				// Already rendered				
				glBindTexture(GL_TEXTURE_2D,TxtrID[re]);
				glCallList(DispList+re);
			} else {
				if( textMap.size() == 127 ) {
					// Buffer is full; clear it
					textMap.clear();
					glDeleteLists(DispList+128,128);
					for(int n = 0; n < 128; ++n ) {
						delete [] OGL_Texture[128+n];
						OGL_Texture[128+n] = NULL;
					}
				}
				int pm = 128 + textMap.size();
				textMap[buffer] = pm;
				render_text_(pm, buffer.c_str());
				glCallList(DispList+pm);
			}
		}
	}
	glPopAttrib();
}


// Renders text a la _draw_screen_text() (see screen_drawing.h), with
// alignment and wrapping. Modelview matrix is unaffected.
void FontSpecifier::OGL_DrawText(const char *text, const screen_rectangle &r, short flags)
{
	// Copy the text to draw
	char text_to_draw[256];
	strncpy(text_to_draw, text, 256);
	text_to_draw[255] = 0;

	int t_width = TextWidth(text_to_draw);

	// Horizontal positioning
	int x, y;
	if (flags & _center_horizontal)
		x = r.left + ((RECTANGLE_WIDTH(&r) - t_width) / 2);
	else if (flags & _right_justified)
		x = r.right - t_width;
	else
		x = r.left;

	// Vertical positioning
	if (flags & _center_vertical) {
		if (Height > RECTANGLE_HEIGHT(&r))
			y = r.top;
		else {
			y = r.bottom;
			int offset = RECTANGLE_HEIGHT(&r) - Height;
			y -= (offset / 2) + (offset & 1) + 1;
		}
	} else if (flags & _top_justified) {
		if (Height > RECTANGLE_HEIGHT(&r))
			y = r.bottom;
		else
			y = r.top + Height;
	} else
		y = r.bottom;

	// Draw text
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(x, y, 0);
	OGL_Render(text_to_draw);
	glPopMatrix();
}

void FontSpecifier::OGL_ResetFonts(bool IsStarting)
{
	if (!m_font_registry)
			return;
		
	set<FontSpecifier*>::iterator it;
	if (IsStarting)
	{
		for (it = m_font_registry->begin();
			 it != m_font_registry->end();
			 ++it)
			(*it)->OGL_Reset(IsStarting);
	}
	else
	{
		for (it = m_font_registry->begin();
			 it != m_font_registry->end();
			 it = m_font_registry->begin())
			(*it)->OGL_Reset(IsStarting);
	}
}

void FontSpecifier::OGL_Register(FontSpecifier *F)
{
	if (!m_font_registry)
		m_font_registry = new set<FontSpecifier*>;
	m_font_registry->insert(F);
}

void FontSpecifier::OGL_Deregister(FontSpecifier *F)
{
	if (m_font_registry)
		m_font_registry->erase(F);
	// we could delete registry here, but why bother?
}

#endif // def HAVE_OPENGL


// Draw text without worrying about OpenGL vs. SDL mode.
int FontSpecifier::DrawText(SDL_Surface *s, const char *text, int x, int y, uint32 pixel, bool utf8)
{
	if (!s)
		return 0;
	if (!(s->flags & SDL_OPENGL))
		return draw_text(s, text, x, y, pixel, this->Info, this->Style, utf8);

#ifdef HAVE_OPENGL
		
	uint8 r, g, b;
	SDL_GetRGB(pixel, s->format, &r, &g, &b);
	glColor4ub(r, g, b, 255);
	
	// draw into both buffers
	for (int i = 0; i < 2; i++)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, 0);
		this->OGL_Render(text);
		glPopMatrix();	
		SDL_GL_SwapBuffers();
	}	
	return 1;
#else
	return 0;
#endif
}
	
// Given a pointer to somewhere in a name set, returns the pointer
// to the start of the next name, or NULL if it did not find any
char *FontSpecifier::FindNextName(char *NamePtr)
{
	char *NextNamePtr = NamePtr;
	char c;
	
	// Continue as long as one's in the string
	while((c = *NextNamePtr) != 0)
	{
		// dprintf("Nxt %c",c);
		// Check for whitespace and commas and semicolons
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == ',' || c == ';')
		{
			NextNamePtr++;
			continue;
		}
		return NextNamePtr;
	}
	return NULL;
}

// Given a pointer to the beginning of a name, finds the pointer to the character
// just after the end of that name
char *FontSpecifier::FindNameEnd(char *NamePtr)
{
	char *NameEndPtr = NamePtr;
	char c;
	
	// Continue as long as one's in the string
	while((c = *NameEndPtr) != 0)
	{
		// dprintf("End %c",c);
		// Delimiter: comma or semicolon
		if (c == ',' || c == ';') break;
		NameEndPtr++;
	}
	return NameEndPtr;
}


// Font-parser object:
class XML_FontParser: public XML_ElementParser
{
	FontSpecifier TempFont;
	short Index;
	bool IsPresent[5];

public:
	FontSpecifier *FontList;
	int NumFonts;
	
	bool Start();
	bool HandleAttribute(const char *Tag, const char *Value);
	bool AttributesDone();
	
	XML_FontParser(): XML_ElementParser("font"), FontList(NULL) {}
};

bool XML_FontParser::Start()
{
	for (int k=0; k<5; k++)
		IsPresent[k] = false;
	return true;
}

bool XML_FontParser::HandleAttribute(const char *Tag, const char *Value)
{
	if (NumFonts > 0)
	{
	if (StringsEqual(Tag,"index"))
	{
		if (ReadBoundedInt16Value(Value,Index,0,NumFonts-1))
		{
			IsPresent[3] = true;
			return true;
		}
		else return false;
	}
	}
	if (StringsEqual(Tag,"name"))
	{
		IsPresent[0] = true;
		strncpy(TempFont.NameSet,Value,FontSpecifier::NameSetLen);
		TempFont.NameSet[FontSpecifier::NameSetLen-1] = 0;	// For making the set always a C string
		return true;
	}
	else if (StringsEqual(Tag,"size"))
	{
		if (ReadInt16Value(Value,TempFont.Size))
		{
			IsPresent[1] = true;
			return true;
		}
		else return false;
	}
	else if (StringsEqual(Tag,"style"))
	{
		if (ReadInt16Value(Value,TempFont.Style))
		{
			IsPresent[2] = true;
			return true;
		}
		else return false;
	}
	else if (StringsEqual(Tag,"file"))
	{
		IsPresent[4] = true;
		strncpy(TempFont.File,Value,FontSpecifier::NameSetLen);
		TempFont.File[FontSpecifier::NameSetLen-1] = 0;	// For making the set always a C string
		return true;
	}
	UnrecognizedTag();
	return false;
}

bool XML_FontParser::AttributesDone()
{
	// Verify...
	//bool AllPresent = true;
	if (NumFonts <= 0)
	{
		IsPresent[3] = true;	// Convenient fakery: no index -- always present
		Index = 0;
	}	
	if (!IsPresent[3])
	{
		AttribsMissing();
		return false;
	}
	
	// Put into place and update if necessary
	assert(FontList);
	bool DoUpdate = false;
	if (IsPresent[0])
	{
		strncpy(FontList[Index].NameSet,TempFont.NameSet,FontSpecifier::NameSetLen);
		DoUpdate = true;
	}
	if (IsPresent[1])
	{
		FontList[Index].Size = TempFont.Size;
		DoUpdate = true;
	}
	if (IsPresent[2])
	{
		FontList[Index].Style = TempFont.Style;
		DoUpdate = true;
	}
	if (IsPresent[4])
	{
		strncpy(FontList[Index].File,TempFont.File,FontSpecifier::NameSetLen);
		DoUpdate = true;
	}
	if (DoUpdate) FontList[Index].Update();
	return true;
}

static XML_FontParser FontParser;



// Returns a parser for the colors;
// several elements may have colors, so this ought to be callable several times.
XML_ElementParser *Font_GetParser() {return &FontParser;}

// This sets the array of colors to be read into.
// Its args are the pointer to that array and the number of colors in it.
// If that number is <= 0, then the color value is assumed to be non-indexed,
// and no "index" attribute will be searched for.
void Font_SetArray(FontSpecifier *FontList, int NumFonts)
{FontParser.FontList = FontList; FontParser.NumFonts = NumFonts;}
