/*
RENDER.C

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

Thursday, September 8, 1994 1:58:20 PM  (Jason')

Friday, September 9, 1994 1:36:15 PM  (Jason')
	on the quads, in the sun.
Sunday, September 11, 1994 7:32:49 PM  (Jason')
	the clock on the 540 was wrong, yesterday was Saturday (not Friday).  on quads again, but
	back home now.  something will draw before i go to bed tonight.  dinner at the nile?
Tuesday, September 13, 1994 2:54:56 AM  (Jason')
	no fair!—— it’s still monday, really.  with the aid of some graphical debugging the clipping
	all works now and i’m trying to have the entire floor/ceiling thing going tonight (the nile
	was closed by the time i got around to taking a shower and heading out).
Friday, September 16, 1994 4:06:17 AM  (Jason')
	walls, floors and ceilings texture, wobble, etc.  contemplating objects ... maybe this will
	work after all.
Monday, September 19, 1994 11:03:49 AM  (Jason')
	unified xz_clip_vertical_polygon() and z_clip_horizontal_polygon() to get rid of the last
	known whitespace problem.  can’t wait to see what others i have.  objects now respect the
	clipping windows of all nodes they cross.
Monday, October 24, 1994 4:35:38 PM (Jason)
	fixed render sorting problem with objects of equal depth (i.e., parasitic objects). 
Tuesday, October 25, 1994 5:14:27 PM  (Jason')
	fixed object sort order with respect to nodes and height.
Wednesday, October 26, 1994 3:18:59 PM (Jason)
	fixed half of the object sort order back so that it worked: in order to correctly handle
	objects below the viewer projecting into higher polygons we need to sort objects inside
	nodes (to be draw after their walls and ceilings but before their floors).
Wednesday, November 2, 1994 3:49:57 PM (Jason)
	the bottom panel of short split sides sometimes takes on the ceiling lightsource.
Tuesday, November 8, 1994 5:29:12 PM  (Jason')
	implemented new transfer modes: _slide, _wander.  _render_effect_earthquake doesn’t work
	yet because the player can shake behind his own shape.
Thursday, December 15, 1994 12:15:55 AM  (Jason)
	the object depth sort order problem ocurrs with multiple objects in the same polygon,
	is some function of relative depths and overlap, and does not seem to involve objects at
	the same depth.  also, it seems to sort many further objects in front of a single closer
	one.
Monday, January 23, 1995 6:53:26 AM  (Jason')
	the way to fix the render object sorting problem is to ignore overlap and sort everything
	by depth, regardless.  imagine: two, far, non-overlapping objects; by the old algorithm their
	drawing order is irrelevant.  when a closer object which overlaps both of them is sorted, it
	only attempts to lie in front of the closest of the two (leaving the farthest one in an
	uncertain position).  unfortunately this will cause us to do unnecessary promotion and might
	look stupid.
Sunday, March 26, 1995 12:57:39 AM  (Jason')
	media modifications for marathon2; the object sort order problem still exists (the above
	solution indeed looked stupid).
Thursday, March 30, 1995 11:23:35 PM  (Jason')
	tried to fix object sort problem by attempting to assure that objects are always drawn in
	depth-order within a node.
Monday, June 5, 1995 8:37:42 AM  (Jason)
	blood and fire (baby).

Jan 30, 2000 (Loren Petrich):
	Added some typecasts
	Increased MAXIMUM_NODE_ALIASES to 32
	Added an "assert" for when DEBUG is off in aliases-building section in sort_render_tree().

Feb 1, 2000 (Loren Petrich):
	Added growable list of node aliases; replaced static-list node-alias code
	
Feb 4, 2000 (Loren Petrich):
	Changed halt() to assert(false) for better debugging

Feb 5, 2000 (Loren Petrich):
	Added growable lists of nodes and also clips for endpoints and lines.

Feb 6, 2000 (Loren Petrich):
	Doing initial allocations of the growable lists of various quantities as a defensive measure
	against memory leaks that seem to occur.

Feb 9, 2000 (Loren Petrich):
	Suppressed ambiguous-clip-flag debugging statement;
	it gets activated only for excessively distant objects

Feb 10, 2000 (Loren Petrich):
	Added dynamic-limits setting of MAXIMUM_RENDER_OBJECTS

Feb 14, 2000 (Loren Petrich):
	Added test for other-side polygon to LINE_IS_TRANSPARENT() check in next_polygon_along_line()

Feb 16, 2000 (Loren Petrich):
	Put in handling of overflow digits for the purpose of doing long distance correctly;
	also turning several horizontal-coordinate short integers into long ones.

Feb 17, 2000 (Loren Petrich):
	Made the sprites long-distance-friendly; there is a bug where they flip around when they
	go past half the world size, but that's a short-integer wraparound, and the relevant routine
	is in map.c.

Feb 18, 2000 (Loren Petrich):
	Added support for conditional display of weapons-in-hand; so as to support third-person
	as well as first-person view.

Feb 21, 2000 (Loren Petrich):
	Idiot-proofed next_polygon_along_line(), making it quit a loop if it searches a whole circle.

Feb 24, 2000 (Loren Petrich):
	Added animated-texture support

Mar 3, 2000 (Loren Petrich):
	Set view to normal in initialize_view_data();
	squashed persistent-extravision bug.

Mar 5, 2000 (Loren Petrich):
	Moved extravision-persistence bug fix out of this file.

Mar 9, 2000 (Loren Petrich):
	Sorted the nodes by polygon index in sort_render_tree() and used them to speed up searches
	for nodes with the same polygon index; maps with slowed-down visibility calculations,
	such as Desla, can become twice as fast.

Mar 12, 2000 (Loren Petrich):
	Added OpenGL support

Mar 14, 2000 (Loren Petrich):
	Modified data transmitted to OpenGL renderer; it's now collection/color/frame for
	both walls and sprites. Also added transmission of view data.

Mar 24, 2000 (Loren Petrich):
	Added landscape_yaw calculation; this is the yaw of the landscapes' left edges

Mar 30, 2000 (Loren Petrich):
	Inspired by Rhys Hill's work, I've created a second tree to contain the visibility nodes;
	in addition to their visibility tree, they have a polygon-sort tree.
	This tree is implemented by setting up some additional members of node_data
	for indicating its structure; there are members for polygon >, polygon <,
	and the next member of a chain that shares polygon-index values.
	As a result, the node-aliases list can now be abolished once and for all.

Jun 11, 2000 (Loren Petrich):
	Added support for see-through liquids; this requires several changes.
	The rendering of each map polygon had to be changed so that there would be a
	separate liquid surface; it would no longer replace the floor or the ceiling.
	Next, the inhabitant objects had to be done in two passes, one other side, and one view side.
	Also, whether there is void on the other side had to be indicated, so that
	waterfalls and the like may look right.

Jun 28, 2000 (Loren Petrich):
	Fixed Aaron Davies bug; if a polygon is completely below a liquid, it will not be rendered
	if the viewpoint is above the liquid; the bug was that it was not rendered if the viewpoint
	was below the liquid. This only happened if semitransparent liquid surfaces was turned off.

Jul 10, 2000 (Loren Petrich):
	Fixed liquid visibility bug in render_tree() that happens when liquid surfaces are not semitransparent;
	rendering is skipped if the viewpoint is under a liquid and the polygon is high and dry,
	or else if the viewpoint is above a liquid and the polygon is submerged.

Jul 17, 2000 (Loren Petrich):
	Suppressed view-effect resetting in initialize_view_data(),
	in order to make teleport view-stretching work correctly.

Aug 9, 2000 (Loren Petrich):
	Moved most of the rendering code here into separate files with these classes:
	
	RenderVisTreeClass --
		creates the visibility tree (which polygons can be seen from which other ones)
	RenderSortPolyClass --
		uses that tree to sort the polygons into appropriate depth order
	RenderPlaceObjsClass --
		finds which objects are visible and places them into appropriately sorted order
	RenderRasterize --
		handles the clipping of each object and requests those objects' rasterization
	
	Added a rasterizer class; currently, it does everything from the base class,
	though what it does will be moved into subclasses.

Sep 2, 2000 (Loren Petrich):
	Added some idiot-proofing, since the shapes accessor now returns NULL for nonexistent bitmaps

Nov 12, 2000 (Loren Petrich):
	Added automap reset before rendering

Nov 29, 2000 (Loren Petrich):
	Made teleport static/fold effect optional

Jan 17, 2001 (Loren Petrich):
	Added vertical flipping
*/


#ifdef QUICKDRAW_DEBUG
#include "macintosh_cseries.h"
#else
//#include "cseries.h"
#include "header.h"
#endif

#include "map.h"
#include "render.h"
#include "interface.h"
#include "lightsource.h"
#include "media.h"
#include "weapons.h"

// LP additions
#include "dynamic_limits.h"
//#include "AnimatedTextures.h"
//#include "OGL_Render.h"

#ifdef QUICKDRAW_DEBUG
#include "shell.h"
extern WindowPtr screen_window;
#endif

#include <math.h>
#include <string.h>
#include <stdlib.h>

// LP additions for decomposition of this code:
/*#include "RenderVisTree.h"
#include "RenderSortPoly.h"
#include "RenderPlaceObjs.h"
#include "RenderRasterize.h"
#include "Rasterizer_SW.h"
#include "Rasterizer_OGL.h"
*/
#ifdef env68k
#pragma segment render
#endif

/* use native alignment */
#if defined (powerc) || defined (__powerc)
#pragma options align=power
#endif

/*
//render transparent walls (if a bit is set or if the transparent texture is non-NULL?)
//use side lightsources instead of taking them from their polygons
//respect dark side bit (darken light intensity by k)
//fix solid/opaque endpoint confusion (solidity does not imply opacity)

there exists a problem where an object can overlap into a polygon which is clipped by something
	behind the object but that will clip the object because clip windows are subtractive; how
	is this solved?
it’s still possible to get ambiguous clip flags, usually in very narrow (e.g., 1 pixel) windows
the renderer has a maximum range beyond which it shits bricks yet which it allows to be exceeded
it’s still possible, especially in high-res full-screen, for points to end up (slightly) off
	the screen (usually discarding these has no noticable effect on the scene)
whitespace results when two adjacent polygons are clipped to different vertical windows.  this
	is not trivially solved with the current implementation, and may be acceptable (?)

//build_base_polygon_index_list() should discard lower polygons for objects above the viewer and
//	higher polygons for objects below the viewer because we certainly don’t sort objects
//	correctly in these cases
//in strange cases, objects are sorted out of order.  this seems to involve players in some way
//	(i.e., parasitic objects).
*/

/* ---------- constants */

#define EXPLOSION_EFFECT_RANGE (WORLD_ONE/12)

/* ---------- clip buffer */
// Not used for anything
#define CLIP_INDEX_BUFFER_SIZE 4096

vector<uint16> RenderFlagList;

// uint16 *render_flags;

// LP additions: decomposition of the rendering code into various objects

/*static RenderVisTreeClass RenderVisTree;			// Visibility-tree object
static RenderSortPolyClass RenderSortPoly;			// Polygon-sorting object
static RenderPlaceObjsClass RenderPlaceObjs;		// Object-placement object
static RenderRasterizerClass RenderRasterize;		// Clipping and rasterization class

static Rasterizer_SW_Class Rasterizer_SW;			// Software rasterizer
#ifdef HAVE_OPENGL
static Rasterizer_OGL_Class Rasterizer_OGL;			// OpenGL rasterizer
#endif


/* ---------- private prototypes */
/*
static void update_view_data(struct view_data *view);
static void update_render_effect(struct view_data *view);
static void shake_view_origin(struct view_data *view, world_distance delta);

static void render_viewer_sprite_layer(view_data *view, RasterizerClass *RasPtr);
static void position_sprite_axis(short *x0, short *x1, short scale_width, short screen_width,
	short positioning_mode, _fixed position, bool flip, world_distance world_left, world_distance world_right);


#ifdef QUICKDRAW_DEBUG
static void debug_flagged_points(flagged_world_point2d *points, short count);
static void debug_flagged_points3d(flagged_world_point3d *points, short count);
static void debug_vector(world_vector2d *v);
static void debug_x_line(world_distance x);
#endif

/* ---------- code */
/*
void allocate_render_memory(
	void)

/* just in case anyone was wondering, standard_screen_width will usually be the same as
	screen_width.  the renderer assumes that the given field_of_view matches the standard
	width provided (so if the actual width provided is larger, you'll be able to see more;
	if it's smaller you'll be able to see less).  this allows the destination bitmap to not
	only grow and shrink while maintaining a constant aspect ratio, but to also change in
	geometry without effecting the image being projected onto it.  if you don't understand
	this, pass standard_width==width *
void initialize_view_data(
	struct view_data *view)
{

/* origin,origin_polygon_index,yaw,pitch,roll,etc. have probably changed since last call *
void render_view(
	struct view_data *view,
	struct bitmap_definition *destination)

void start_render_effect(
	struct view_data *view,
	short effect)
{
	view->effect= effect;
	view->effect_phase= NONE;
}

/* ---------- private code */
/*
static void update_view_data(
	struct view_data *view)
static void update_render_effect(
	struct view_data *view)
/* ---------- transfer modes */

/* given a transfer mode and phase, cause whatever changes it should cause to a rectangle_definition
	structure *
void instantiate_rectangle_transfer_mode(
	view_data *view,
	rectangle_definition *rectangle,
	short transfer_mode,
	_fixed transfer_phase)

/* given a transfer mode and phase, cause whatever changes it should cause to a polygon_definition
	structure (unfortunately we need to know whether this is a horizontal or vertical polygon) *
void instantiate_polygon_transfer_mode(
	struct view_data *view,
	struct polygon_definition *polygon,
	short transfer_mode,
	bool horizontal)


/* ---------- viewer sprite layer (i.e., weapons) */
/*
static void render_viewer_sprite_layer(view_data *view, RasterizerClass *RasPtr)
{

static void position_sprite_axis(
	short *x0,
	short *x1,
	short scale_width,
	short screen_width,
	short positioning_mode,
	_fixed position,
	bool flip,
	world_distance world_left,
	world_distance world_right)
static void shake_view_origin(
	struct view_data *view,
	world_distance delta)

// LP: begin no-compile
#if 0

/* ---------- mac-specific debugging calls */
/*
#ifdef QUICKDRAW_DEBUG

#define SCALEF 5

static void debug_flagged_points(
	flagged_world_point2d *points,
	short count)
{
	short i;
	
	SetPort(screen_window);
	PenSize(1, 1);
	RGBForeColor(&rgb_black);
	RGBBackColor(&rgb_white);
	EraseRect(&screen_window->portRect);
	SetOrigin(-640/2, -480/2);
	MoveTo(-320, 0); LineTo(320, 0);
	MoveTo(0, 240); LineTo(0, -240);
	PenSize(2, 2);
	MoveTo(points[count-1].y>>SCALEF, - (points[count-1].x>>SCALEF));
	for (i=0;i<count;++i)
	{
		LineTo(points[i].y>>SCALEF, - (points[i].x>>SCALEF));
		psprintf(ptemporary, "%d", i);
		DrawString(temporary);
		MoveTo(points[i].y>>SCALEF, - (points[i].x>>SCALEF));
	}
}

static void debug_flagged_points3d(
	flagged_world_point3d *points,
	short count)
{
	short i;
	
	SetPort(screen_window);
	PenSize(1, 1);
	RGBForeColor(&rgb_black);
	RGBBackColor(&rgb_white);
	EraseRect(&screen_window->portRect);
	SetOrigin(-640/2, -480/2);
	MoveTo(-320, 0); LineTo(320, 0);
	MoveTo(0, 240); LineTo(0, -240);
	PenSize(2, 2);
	MoveTo(points[count-1].z>>SCALEF, - (points[count-1].x>>SCALEF));
	for (i=0;i<count;++i)
	{
		LineTo(points[i].z>>SCALEF, - (points[i].x>>SCALEF));
		psprintf(ptemporary, "%d", i);
		DrawString(temporary);
		MoveTo(points[i].z>>SCALEF, - (points[i].x>>SCALEF));
	}
}

static void debug_vector(
	world_vector2d *v)
{
	PenSize(1, 1);
	MoveTo(0, 0);
	LineTo(v->j, - v->i);
	MoveTo(0, 0);
	LineTo(- v->j, v->i);
	
	while (!Button()); while (Button());
}

static void debug_x_line(
	world_distance x)
{
	PenSize(1, 1);
	MoveTo(-320, - x>>SCALEF);
	LineTo(320, - x>>SCALEF);
	
	while (!Button()); while (Button());
}

#endif /* QUICKDRAW DEBUG *

// LP: end no-compile
#endif
*/