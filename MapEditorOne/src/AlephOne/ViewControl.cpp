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

	May 22, 2000 (Loren Petrich)
	
	The work of the view controller.

Oct 13, 2000 (Loren Petrich)
	Using the STL for the landscape-option-data container

Nov 29, 2000 (Loren Petrich):
	Added making view-folding effect optional
	Added making teleport static/fold effect optional

Dec 17, 2000 (Loren Petrich:
	Added teleport-sound control for Marathon 1 compatibility
*/

#include <vector>
#include <string.h>
#include "cseries.h"
#include "world.h"
#include "mysound.h"
#include "ViewControl.h"


struct view_settings_definition {
	bool MapActive;
	bool DoFoldEffect;
	bool DoStaticEffect;
};

// Defaults:
struct view_settings_definition view_settings = {
	true, // overhead map is active
	true, // do the view folding effect (stretch horizontally, squeeze vertically) when teleporting,
	true  // also do the static effect / folding effect on viewed teleported objects
};

// Accessors:
bool View_MapActive() {return view_settings.MapActive;}
bool View_DoFoldEffect() {return view_settings.DoFoldEffect;}
bool View_DoStaticEffect() {return view_settings.DoStaticEffect;}


// This frame value means that a landscape option will be applied to any frame in a collection:
const int AnyFrame = -1;

// Field-of-view stuff with defaults:
struct FOV_settings_definition {
	float Normal;
	float ExtraVision;
	float TunnelVision;
	float ChangeRate;	// this is 50 degrees/s
	bool FixHorizontalNotVertical;
};

struct FOV_settings_definition FOV_settings = {
	80,
	130,
	30,
	1.66666667F,	// this is 50 degrees/s
	false
};

#define FOV_Normal FOV_settings.Normal
#define FOV_ExtraVision FOV_settings.ExtraVision
#define FOV_TunnelVision FOV_settings.TunnelVision
#define FOV_ChangeRate FOV_settings.ChangeRate
#define FOV_FixHorizontalNotVertical FOV_settings.FixHorizontalNotVertical


//static FontSpecifier OnScreenFont = {"Monaco", 12, styleNormal, "#4"};
//static bool ScreenFontInited = false;

// Accessors:
float View_FOV_Normal() {return FOV_Normal;}
float View_FOV_ExtraVision() {return FOV_ExtraVision;}
float View_FOV_TunnelVision() {return FOV_TunnelVision;}

/*FontSpecifier& GetOnScreenFont()
{
	// Init the font the first time through; accessor functions are very convenient :-)
	if (!ScreenFontInited)
	{
		OnScreenFont.Init();
		ScreenFontInited = true;
	}
	return OnScreenFont;
}*/

// Move field-of-view value closer to some target value:
bool View_AdjustFOV(float& FOV, float FOV_Target)
{
	bool Changed = false;
	if (FOV_ChangeRate < 0) FOV_ChangeRate *= -1;
	
	if (FOV > FOV_Target)
	{
		FOV -= FOV_ChangeRate;
		FOV = MAX(FOV,FOV_Target);
		Changed = true;
	}
	else if (FOV < FOV_Target)
	{
		FOV += FOV_ChangeRate;
		FOV = MIN(FOV,FOV_Target);
		Changed = true;
	}
	
	return Changed;
}

// Indicates whether to fix the horizontal or the vertical field-of-view angle
// (default: fix vertical FOV angle)
bool View_FOV_FixHorizontalNotVertical() {return FOV_FixHorizontalNotVertical;}

// Landscape stuff: this is for being able to return a pointer to the default one
static LandscapeOptions DefaultLandscape;


// Store landscape stuff as a vector member
struct LandscapeOptionsEntry
{
	// Which frame to apply to (default: 0, since there is usually only one)
	short Frame;
	
	// Make a member for more convenient access
	LandscapeOptions OptionsData;
	
	LandscapeOptionsEntry(): Frame(0) {}
};

// Separate landscape-texture sequence lists for each collection ID,
// to speed up searching.
static vector<LandscapeOptionsEntry> LOList[NUMBER_OF_COLLECTIONS];

// Deletes a collection's landscape-texture sequences
static void LODelete(int c)
{
	LOList[c].clear();
}

// Deletes all of them
static void LODeleteAll()
{
	for (int c=0; c<NUMBER_OF_COLLECTIONS; c++) LODelete(c);
}


LandscapeOptions *View_GetLandscapeOptions(shape_descriptor Desc)
{
	// Pull out frame and collection ID's:
	short Frame = GET_DESCRIPTOR_SHAPE(Desc);
	short CollCT = GET_DESCRIPTOR_COLLECTION(Desc);
	short Collection = GET_COLLECTION(CollCT);
	
	vector<LandscapeOptionsEntry>& LOL = LOList[Collection];
	for (vector<LandscapeOptionsEntry>::iterator LOIter = LOL.begin(); LOIter < LOL.end(); LOIter++)
	{
		if (LOIter->Frame == Frame || LOIter->Frame == AnyFrame)
		{
			// Get a pointer from the iterator in order to return it
			return &(LOIter->OptionsData);
		}
	}
	
	// Return the default if no matching entry was found
	return &DefaultLandscape;
}


// Field-of-view parser
struct FOV_settings_definition *original_FOV_settings = NULL;
