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
//  Device context.
//
//	TODO:  the SDL_ChildWindow code can be updated to use this.
////////////////////////////////////////////////////

#include "SDLToWin32.h"

SDLToWindows::SDLToWindows(HWND parent, RECT size){

	bitmap=0;
	surface=0;
	owner=parent;
	if(parent=0) return;
	createSurface(parent, size);
}


void SDLToWindows::createSurface(HWND hwnd, RECT size){

	HDC dc=GetDC(hwnd);

	BITMAPINFO *bmi;
	BITMAPINFOHEADER bh;
	int bmsize;
	
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;

	//make an sdl surface
	surface=SDL_CreateRGBSurface(SDL_SWSURFACE, size.right+size.left, size.top+size.bottom, 32, rmask, gmask, bmask, amask);

	if(surface==NULL) return;


	bmsize=sizeof(BITMAPINFO);
	if(surface->format->palette){
		//paletised mode, this is not handled properly at the moment
		//since a 32 bit SDL_Surface is created, I am hoping palettes will not be used.
		/*TODO allocate palette.  See SDL_dibvideo.c */

			bmsize+=surface->format->palette->ncolors *
			sizeof(RGBQUAD);
	}
	else{

		//no palette
		bmsize+=3*sizeof(DWORD);
	}

	bmi = (BITMAPINFO *)malloc(bmsize);
	//clear struct
	memset((void*)&bh, 0, sizeof(BITMAPINFOHEADER));

	bh.biSize = sizeof(BITMAPINFOHEADER);
	bh.biWidth = surface->w;
	bh.biHeight = -surface->h;	/* -ve for topdown bitmap */
	bh.biPlanes = 1;
	bh.biSizeImage = surface->h * surface->pitch;
	bh.biXPelsPerMeter = 0;
	bh.biYPelsPerMeter = 0;
	bh.biClrUsed = 0;
	bh.biClrImportant = 0;
	bh.biBitCount = surface->format->BitsPerPixel;
	bh.biCompression = BI_BITFIELDS;

	bmi->bmiHeader=bh;

	((Uint32*)bmi->bmiColors)[0]=surface->format->Rmask;
	((Uint32*)bmi->bmiColors)[1]=surface->format->Gmask;
	((Uint32*)bmi->bmiColors)[2]=surface->format->Bmask;

	bitmap=CreateDIBSection(dc, bmi, DIB_RGB_COLORS,
											(void **)(&surface->pixels), NULL, 0);

	free(bmi);
	
	ReleaseDC(hwnd, dc);
}


SDLToWindows::SDLToWindows(HWND parent){
		//use entire client area

	RECT client;
	GetClientRect(parent, &client);
	SDLToWindows::SDLToWindows(parent, client);

}


SDLToWindows::~SDLToWindows(){

	cleanUp();
	
}

void SDLToWindows::cleanUp(){
	SDL_FreeSurface(surface);
	surface=0;		
	if(bitmap!=0){
		DeleteObject(bitmap);
		bitmap=0;
	}
}

//when the window re-sizes, this must be called, uses entire client area
void SDLToWindows::resize(){



	RECT client;
	GetClientRect(owner, &client);
	resize(client);

}

//when the window re-sizes, this must be called
void SDLToWindows::resize(RECT size){
	
	//only re-size if the window is larger than current

	if(size.top+size.bottom>surface->h && size.left+size.right>surface->w){
		cleanUp();
		createSurface(owner, size);
	}
}

void SDLToWindows::paint(unsigned int x_pos,  unsigned int y_pos){
	if(owner==NULL) return;
	
	HDC memdc;
	HDC hdc=GetDC(owner);
	RECT client;
	GetClientRect(owner, &client);

	memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, bitmap);
	BitBlt(hdc, x_pos, y_pos, client.left+client.right,
					  client.bottom+client.top,
					memdc, 0, 0, SRCCOPY);
	
	DeleteDC(memdc);
	ReleaseDC(owner, hdc);
}

void SDLToWindows::paint(){
	

	paint(0,0);
}