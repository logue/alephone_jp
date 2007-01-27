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
#include "RenderVisTree.h"
#include "RenderSortPoly.h"
#include "RenderPlaceObjs.h"
#include "RenderRasterize.h"
#include "Rasterizer_SW.h"
/*#include "Rasterizer_OGL.h"
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

static RenderVisTreeClass RenderVisTree;			// Visibility-tree object
static RenderSortPolyClass RenderSortPoly;			// Polygon-sorting object
static RenderPlaceObjsClass RenderPlaceObjs;		// Object-placement object
static RenderRasterizerClass RenderRasterize;		// Clipping and rasterization class

static Rasterizer_SW_Class Rasterizer_SW;			// Software rasterizer
#ifdef HAVE_OPENGL
static Rasterizer_OGL_Class Rasterizer_OGL;			// OpenGL rasterizer
#endif


/* ---------- private prototypes */
static void update_view_data(struct view_data *view);
static void render_viewer_sprite_layer(view_data *view, RasterizerClass *RasPtr);
/*
static void update_render_effect(struct view_data *view);
static void shake_view_origin(struct view_data *view, world_distance delta);

static void position_sprite_axis(short *x0, short *x1, short scale_width, short screen_width,
	short positioning_mode, _fixed position, bool flip, world_distance world_left, world_distance world_right);


#ifdef QUICKDRAW_DEBUG
static void debug_flagged_points(flagged_world_point2d *points, short count);
static void debug_flagged_points3d(flagged_world_point3d *points, short count);
static void debug_vector(world_vector2d *v);
static void debug_x_line(world_distance x);
#endif

/* ---------- code */
void allocate_render_memory(
	void)
{
	assert(NUMBER_OF_RENDER_FLAGS<=16);
    printf("NUMBER_OF_RENDER_FLAGS:%d\n", NUMBER_OF_RENDER_FLAGS);
	RenderFlagList.resize(RENDER_FLAGS_BUFFER_SIZE);
    for(int i = 0; i < RENDER_FLAGS_BUFFER_SIZE; i ++){
        RenderFlagList.push_back(0);
    }
	// LP addition: check out pointer-arithmetic hack
	assert(sizeof(void *) == sizeof(POINTER_DATA));
	
	// LP change: do max allocation
	RenderVisTree.Resize(MAXIMUM_ENDPOINTS_PER_MAP,MAXIMUM_LINES_PER_MAP);
	RenderSortPoly.Resize(MAXIMUM_POLYGONS_PER_MAP);
	
	// LP change: set up pointers
	RenderSortPoly.RVPtr = &RenderVisTree;
	RenderPlaceObjs.RVPtr = &RenderVisTree;
	RenderPlaceObjs.RSPtr = &RenderSortPoly;
	RenderRasterize.RSPtr = &RenderSortPoly;
}

/* just in case anyone was wondering, standard_screen_width will usually be the same as
	screen_width.  the renderer assumes that the given field_of_view matches the standard
	width provided (so if the actual width provided is larger, you'll be able to see more;
	if it's smaller you'll be able to see less).  this allows the destination bitmap to not
	only grow and shrink while maintaining a constant aspect ratio, but to also change in
	geometry without effecting the image being projected onto it.  if you don't understand
	this, pass standard_width==width *
    */
void initialize_view_data(
struct view_data *view){
	double two_pi= 8.0*atan(1.0);
	double half_cone= view->field_of_view*(two_pi/360.0)/2;
	double adjusted_half_cone= View_FOV_FixHorizontalNotVertical() ?
		half_cone :
		asin(view->screen_width*sin(half_cone)/view->standard_screen_width);
	double world_to_screen;
	
	view->half_screen_width= view->screen_width/2;
	view->half_screen_height= view->screen_height/2;
	
	/* if there’s a round-off error in half_cone, we want to make the cone too big (so when we clip
		lines ‘to the edge of the screen’ they’re actually off the screen, thus +1.0) */
	view->half_cone= (angle) (adjusted_half_cone*((double)NUMBER_OF_ANGLES)/two_pi+1.0);
	
	// LP change: find the adjusted yaw for the landscapes;
	// this is the effective yaw value for the left edge.
	// A landscape rotation can also be added if desired.
	view->landscape_yaw = view->yaw - view->half_cone;

	/* calculate world_to_screen; we could calculate this with standard_screen_width/2 and
		the old half_cone and get the same result */
	world_to_screen= view->half_screen_width/tan(adjusted_half_cone);
	view->world_to_screen_x= view->real_world_to_screen_x= (short) ((world_to_screen/view->horizontal_scale)+0.5);
	view->world_to_screen_y= view->real_world_to_screen_y= (short) ((world_to_screen/view->vertical_scale)+0.5);
	
	/* calculate the vertical cone angle; again, overflow instead of underflow when rounding */
	view->half_vertical_cone= (angle) (NUMBER_OF_ANGLES*atan(((double)view->half_screen_height*view->vertical_scale)/world_to_screen)/two_pi+1.0);

	/* calculate left edge vector */
	view->untransformed_left_edge.i= view->world_to_screen_x;
	view->untransformed_left_edge.j= - view->half_screen_width;

	/* calculate right edge vector (negative, so it clips in the right direction) */
	view->untransformed_right_edge.i= - view->world_to_screen_x;
	view->untransformed_right_edge.j= - view->half_screen_width;

	/* reset any active effects */
	// LP: this is now called in render_screen(), so we need to disable the initializing
}
//* origin,origin_polygon_index,yaw,pitch,roll,etc. have probably changed since last call *
void render_view(
	struct view_data *view,
    struct bitmap_definition *destination){
	update_view_data(view);

	/* clear the render flags */
    //if(RenderFlagList.size() > 0){
    	objlist_clear(render_flags, RENDER_FLAGS_BUFFER_SIZE);
    //}

	//ResetOverheadMap();
/*
#ifdef AUTOMAP_DEBUG
	memset(automap_lines, 0, (dynamic_world->line_count/8+((dynamic_world->line_count%8)?1:0)*sizeof(byte)));
	memset(automap_polygons, 0, (dynamic_world->polygon_count/8+((dynamic_world->polygon_count%8)?1:0)*sizeof(byte)));
#endif
*/
	
	if(view->terminal_mode_active)
	{
		/* Render the computer interface. */
		//render_computer_interface(view);
	}
	else
	{
		// LP: the render objects have a pointer to the current view in them,
		// so that one can get rid of redundant references to it in them.
		
		// LP: now from the visibility-tree class
		/* build the render tree, regardless of map mode, so the automap updates while active */
		RenderVisTree.view = view;
		RenderVisTree.build_render_tree();
		
		if (view->overhead_map_active)
		{
			//* if the overhead map is active, render it *
			//render_overhead_map(view);
		}
		else //* do something complicated and difficult to explain *
		{			
			// LP: now from the polygon-sorter class
			//* sort the render tree (so we have a depth-ordering of polygons) and accumulate
			//	clipping information for each polygon *
			RenderSortPoly.view = view;
			RenderSortPoly.sort_render_tree();
			
			// LP: now from the object-placement class
			//* build the render object list by looking at the sorted render tree *
			RenderPlaceObjs.view = view;
			RenderPlaceObjs.build_render_object_list();
			
			// LP addition: set the current rasterizer to whichever is appropriate here
			RasterizerClass *RasPtr;
#ifdef HAVE_OPENGL
			if (OGL_IsActive())
				RasPtr = &Rasterizer_OGL;
			else
			{
#endif
				// The software renderer needs this but the OpenGL one doesn't...
				Rasterizer_SW.screen = destination;
				RasPtr = &Rasterizer_SW;
#ifdef HAVE_OPENGL
			}
#endif
			
			// Set its view:
			RasPtr->SetView(*view);
			
			// Start rendering main view
			RasPtr->Begin();
			
			// LP: now from the clipping/rasterizer class
			//* render the object list, back to front, doing clipping on each surface before passing
			//	it to the texture-mapping code *
			RenderRasterize.view = view;
			RenderRasterize.RasPtr = RasPtr;
			RenderRasterize.render_tree();
			
			// LP: won't put this into a separate class
			//* render the player’s weapons, etc. *	
			render_viewer_sprite_layer(view, RasPtr);
			
			// Finish rendering main view
			RasPtr->End();
            
		}
	}
}

/*
void start_render_effect(
	struct view_data *view,
	short effect)
{
	view->effect= effect;
	view->effect_phase= NONE;
}

/* ---------- private code */


static void update_view_data(
	struct view_data *view)
{
	angle theta;

	// LP change: doing all the FOV changes here:
	View_AdjustFOV(view->field_of_view,view->target_field_of_view);
	
	if (view->effect==NONE)
	{
		view->world_to_screen_x= view->real_world_to_screen_x;
		view->world_to_screen_y= view->real_world_to_screen_y;
	}
	else
	{
		//update_render_effect(view);
	}
	
	view->untransformed_left_edge.i= view->world_to_screen_x;
	view->untransformed_right_edge.i= - view->world_to_screen_x;
	
	/* calculate world_to_screen_y*tan(pitch) */
	view->dtanpitch= (view->world_to_screen_y*sine_table[view->pitch])/cosine_table[view->pitch];

	/* calculate left cone vector */
	theta= NORMALIZE_ANGLE(view->yaw-view->half_cone);
	view->left_edge.i= cosine_table[theta], view->left_edge.j= sine_table[theta];
	
	/* calculate right cone vector */
	theta= NORMALIZE_ANGLE(view->yaw+view->half_cone);
	view->right_edge.i= cosine_table[theta], view->right_edge.j= sine_table[theta];
	
	/* calculate top cone vector (negative to clip the right direction) */
	view->top_edge.i= - view->world_to_screen_y;
	view->top_edge.j= - (view->half_screen_height + view->dtanpitch); /* ==k */

	/* calculate bottom cone vector */
	view->bottom_edge.i= view->world_to_screen_y;
	view->bottom_edge.j= - view->half_screen_height + view->dtanpitch; /* ==k */

	/* if we’re sitting on one of the endpoints in our origin polygon, move us back slightly (±1) into
		that polygon.  when we split rays we’re assuming that we’ll never pass through a given
		vertex in different directions (because if we do the tree becomes a graph) but when
		we start on a vertex this can happen.  this is a destructive modification of the origin. */
	{
		short i;
		struct polygon_data *polygon= get_polygon_data(view->origin_polygon_index);
		
		for (i= 0;i<polygon->vertex_count;++i)
		{
			struct world_point2d *vertex= &get_endpoint_data(polygon->endpoint_indexes[i])->vertex;
			
			if (vertex->x==view->origin.x && vertex->y==view->origin.y)
			{
				world_point2d *ccw_vertex= &get_endpoint_data(polygon->endpoint_indexes[WRAP_LOW(i, polygon->vertex_count-1)])->vertex;
				world_point2d *cw_vertex= &get_endpoint_data(polygon->endpoint_indexes[WRAP_HIGH(i, polygon->vertex_count-1)])->vertex;
				world_vector2d inset_vector;
				
				inset_vector.i= (ccw_vertex->x-vertex->x) + (cw_vertex->x-vertex->x);
				inset_vector.j= (ccw_vertex->y-vertex->y) + (cw_vertex->y-vertex->y);
				view->origin.x+= SGN(inset_vector.i);
				view->origin.y+= SGN(inset_vector.j);
				
				break;
			}
		}
		
		/* determine whether we are under or over the media boundary of our polygon; we will see all
			other media boundaries from this orientation (above or below) or fail to draw them. */
		if (polygon->media_index==NONE)
		{
			view->under_media_boundary= false;
		}
		else
		{
			struct media_data *media= get_media_data(polygon->media_index);
			
			// LP change: idiot-proofing
			if (media)
			{
				view->under_media_boundary= UNDER_MEDIA(media, view->origin.z);
				view->under_media_index= polygon->media_index;
			} else {
				view->under_media_boundary= false;
			}
		}
	}
}

        /*
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
static void render_viewer_sprite_layer(view_data *view, RasterizerClass *RasPtr)
{
	rectangle_definition textured_rectangle;
	weapon_display_information display_data;
	shape_information_data *shape_information;
//	short count;

	// LP change: bug out if weapons-in-hand are not to be displayed
	if (!view->show_weapons_in_hand) return;
	
	// Need to set this...
	RasPtr->SetForeground();
	
	// No models here, and completely opaque
	textured_rectangle.ModelPtr = NULL;
	textured_rectangle.Opacity = 1;

	/* get_weapon_display_information() returns true if there is a weapon to be drawn.  it
	//	should initially be passed a count of zero.  it returns the weapon’s texture and
	//	enough information to draw it correctly. *
	count= 0;
	while (get_weapon_display_information(&count, &display_data))
	{
		//* fetch relevant shape data *
		// LP: model-setup code is cribbed from 
		// RenderPlaceObjsClass::build_render_object() in RenderPlaceObjs.cpp
#ifdef HAVE_OPENGL
		// Find which 3D model will take the place of this sprite, if any
		short ModelSequence;
		OGL_ModelData *ModelPtr =
			OGL_GetModelData(GET_COLLECTION(display_data.collection),display_data.shape_index,ModelSequence);
#endif
		shape_information= extended_get_shape_information(display_data.collection, display_data.low_level_shape_index);
		// Nonexistent frame: skip
		if (!shape_information) continue;
		// No need for a fake sprite rectangle, since models are foreground objects
		
		// LP change: for the convenience of the OpenGL renderer
		textured_rectangle.ShapeDesc = BUILD_DESCRIPTOR(display_data.collection,0);
		textured_rectangle.LowLevelShape = display_data.low_level_shape_index;
#ifdef HAVE_OPENGL
		textured_rectangle.ModelPtr = ModelPtr;
		if (ModelPtr)
		{
			textured_rectangle.ModelSequence = ModelSequence;
			textured_rectangle.ModelFrame = display_data.Frame;
			textured_rectangle.NextModelFrame = display_data.NextFrame;
			textured_rectangle.MixFrac = display_data.Ticks > 0 ?
				float(display_data.Phase)/float(display_data.Ticks) : 0;
			const world_point3d Zero = {0, 0, 0};
			textured_rectangle.Position = Zero;
			textured_rectangle.Azimuth = 0;
			textured_rectangle.Scale = 1;
			textured_rectangle.LightDepth = 0;
			const GLfloat LightDirection[3] = {0, 1, 0};	// y is forward
			objlist_copy(textured_rectangle.LightDirection,LightDirection,3);
			RasPtr->SetForegroundView(display_data.flip_horizontal);
		}
#endif
		
		if (shape_information->flags&_X_MIRRORED_BIT) display_data.flip_horizontal= !display_data.flip_horizontal;
		if (shape_information->flags&_Y_MIRRORED_BIT) display_data.flip_vertical= !display_data.flip_vertical;

		//* calculate shape rectangle *
		position_sprite_axis(&textured_rectangle.x0, &textured_rectangle.x1, view->screen_height, view->screen_width, display_data.horizontal_positioning_mode,
			display_data.horizontal_position, display_data.flip_horizontal, shape_information->world_left, shape_information->world_right);
		position_sprite_axis(&textured_rectangle.y0, &textured_rectangle.y1, view->screen_height, view->screen_height, display_data.vertical_positioning_mode,
			display_data.vertical_position, display_data.flip_vertical, -shape_information->world_top, -shape_information->world_bottom);
		
		//* set rectangle bitmap and shading table /
		extended_get_shape_bitmap_and_shading_table(display_data.collection, display_data.low_level_shape_index, &textured_rectangle.texture, &textured_rectangle.shading_tables, view->shading_mode);
		if (!textured_rectangle.texture) continue;
		
		textured_rectangle.flags= 0;

		//* initialize clipping window to full screen /
		textured_rectangle.clip_left= 0;
		textured_rectangle.clip_right= view->screen_width;
		textured_rectangle.clip_top= 0;
		textured_rectangle.clip_bottom= view->screen_height;

		// copy mirror flags /
		textured_rectangle.flip_horizontal= display_data.flip_horizontal;
		textured_rectangle.flip_vertical= display_data.flip_vertical;
		
		//* lighting: depth of zero in the camera’s polygon index /
		textured_rectangle.depth= 0;
		textured_rectangle.ambient_shade= get_light_intensity(get_polygon_data(view->origin_polygon_index)->floor_lightsource_index);
		textured_rectangle.ambient_shade= MAX(shape_information->minimum_light_intensity, textured_rectangle.ambient_shade);
		if (view->shading_mode==_shading_infravision) textured_rectangle.flags|= _SHADELESS_BIT;

		// Calculate the object's horizontal position
		// for the convenience of doing teleport-in/teleport-out
		textured_rectangle.xc = (textured_rectangle.x0 + textured_rectangle.x1) >> 1;
		
		//* make the weapon reflect the owner’s transfer mode /
		instantiate_rectangle_transfer_mode(view, &textured_rectangle, display_data.transfer_mode, display_data.transfer_phase);
		
		//* and draw it /
		// LP: added OpenGL support
		RasPtr->texture_rectangle(textured_rectangle);
	}
    */
}
/*
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