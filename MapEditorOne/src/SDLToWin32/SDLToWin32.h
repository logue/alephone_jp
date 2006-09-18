
/*
* SDLToWindows
* Copyright (C) 2003-2005 Tom Wilson
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/




////////////////////////////////////////////////////
//	Description: An object that can blit it's self to a Win32 DC
//	Author:			Tom Wilson
//	Date:			12/12/03	
//
//	This replaces the SDL_ChildWindow code that I wrote, which was a bit bulky
//	and suffered from message processing problems.
//	Specifically, it was difficult to get mouse messages to the parent window
//	This eliminates that problem by attempting to draw to an existing windows
//  Device context.  The blitting function can be manually called, and the resize function etc
//	in the correct message processing stage.
//
//	TODO:  the SDL_ChildWindow code can be updated to use this.
////////////////////////////////////////////////////

#ifndef __SDL_TO_WIN32_OBJECT_H
#define __SDL_TO_WIN32_OBJECT_H

#ifndef __AFXDLL  //should work with MFC, when using DLL, not static linking
#include <windows.h>
#else
#include "StdAfx.h"
#endif

#include <SDL.h>

//may change this name when I figure out what a good one would be.
class SDLToWindows{
private:

	HBITMAP bitmap;	//windows bitmap which point to the pixels in the surface
	SDL_Surface *surface;
	
	//this is set once. At creation.
	HWND owner;

	//no default c'tor available
	SDLToWindows(){
		surface=0;
		owner=0;
	};

	void createSurface(HWND, RECT);
	void cleanUp();
public:

	SDLToWindows(HWND parent, RECT size);
	SDLToWindows(HWND parent);	//use entire client area
	~SDLToWindows();

	//when the window re-sizes, this must be called, uses entire client area
	void resize();
	//when the window re-sizes, this must be called
	void resize(RECT size);
	

	//specify top corner offset for blitting
	void paint(unsigned int x_pos,  unsigned int y_pos);
	void paint();


	SDL_Surface *getSurface(){ return surface; }
};


#endif //__SDL_TO_WIN32_OBJECT_H