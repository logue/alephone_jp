#include "stdafx.h"
/*
PROJECTILES.C

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

Friday, May 27, 1994 10:54:44 AM

Friday, July 15, 1994 12:28:36 PM
	added maximum range.
Monday, February 6, 1995 2:46:08 AM  (Jason')
	persistent/virulent projectiles; media detonation effects.
Tuesday, June 13, 1995 12:07:00 PM  (Jason)
	non-melee projectiles must start above media.
Monday, June 26, 1995 8:52:32 AM  (Jason)
	bouncing projectiles
Tuesday, August 1, 1995 3:31:08 PM  (Jason)
	guided projectiles bite on low levels
Thursday, August 17, 1995 9:35:13 AM  (Jason)
	wandering projectiles
Thursday, October 5, 1995 10:19:48 AM  (Jason)
	until we fix it, calling translate_projectile() is too time consuming on high levels.
Friday, October 6, 1995 8:35:04 AM  (Jason)
	simpler guided projectile model.

Feb 4, 2000 (Loren Petrich):
	Added effects of "penetrates media boundary" flag;
	assuming it to be like "penetrates media" flag until I can figure out
	the difference between the two.
	
	Changed halt() to assert(false) for better debugging
	
	Determined that "penetrates media boundary" means
	making a splash but nevertheless continuing

Feb 6, 2000 (Loren Petrich):
	Added access to size of projectile-definition structure.

Feb 9, 2000 (Loren Petrich):
	Put in handling of "penetrates media boundary" flag

Feb 13, 2000 (Loren Petrich):
	Fixed bug in setting will_go_through when hitting a media boundary;
	this banishes the floating-mine effect.

Feb 14, 2000 (Loren Petrich):
	Added workaround for Pfhorte bug: if there is no polygon on the other side
	of a non-solid line, then treat the line as if it was solid.

Feb 16, 2000 (Loren Petrich):
	Improved the handling of "penetrates media boundary" -- if the rocket has that,
	it will explode on the surface, and then afterward on something it hits.

Feb 17, 2000 (Loren Petrich):
	Fixed stuff near GUESS_HYPOTENUSE() to be long-distance-friendly

Feb 19, 2000 (Loren Petrich):
	Added growable lists of indices of objects to be checked for collisions

Jul 1, 2000 (Loren Petrich):
	Added Benad's changes

Aug 30, 2000 (Loren Petrich):
	Added stuff for unpacking and packing
	
Oct 13, 2000 (Loren Petrich)
	Converted the intersected-objects list into a Standard Template Library vector
*/

/*#include "cseries.h"
#include "interface.h"
*/
#include "map.h"
#include "effects.h"
#include "monsters.h"
#include "projectiles.h"
#include "player.h"
#include "mysound.h"
/*#include "scenery.h"
#include "media.h"
#include "items.h"
*/
// LP additions
#include "dynamic_limits.h"
#include "Packing.h"

//#include "lua_script.h"

/*
//translate_projectile() must set _projectile_hit_landscape bit
*/

#ifdef env68k
#pragma segment objects
#endif

/* ---------- constants */

enum
{
	GRAVITATIONAL_ACCELERATION= 1, // per tick
	
	WANDER_MAGNITUDE= WORLD_ONE/TICKS_PER_SECOND,
	
	MINIMUM_REBOUND_VELOCITY= GRAVITATIONAL_ACCELERATION*TICKS_PER_SECOND/3
};

enum /* translate_projectile() flags */
{
	_flyby_of_current_player= 0x0001,
	_projectile_hit= 0x0002,
	_projectile_hit_monster= 0x0004, // monster_index in *obstruction_index
	_projectile_hit_floor= 0x0008, // polygon_index in *obstruction_index
	_projectile_hit_media= 0x0010, // polygon_index in *obstruction_index
	_projectile_hit_landscape= 0x0020,
	_projectile_hit_scenery= 0x0040
};

enum /* things the projectile can hit in detonate_projectile() */
{
	_hit_nothing,
	_hit_floor,
	_hit_media,
	_hit_ceiling,
	_hit_wall,
	_hit_monster,
	_hit_scenery
};

#define MAXIMUM_PROJECTILE_ELEVATION (QUARTER_CIRCLE/2)

/* ---------- structures */

/* ---------- private prototypes */

/* ---------- globals */

/* import projectile definition structures, constants and globals */
#include "projectile_definitions.h"

/* if copy-protection fails, these are replaced externally with the rocket and the rifle bullet, respectively */
short alien_projectile_override= NONE;
short human_projectile_override= NONE;

// LP addition: growable list of intersected objects
static vector<short> IntersectedObjects;

/* ---------- private prototypes */

static short adjust_projectile_type(world_point3d *origin, short polygon_index, short type,
	short owner_index, short owner_type, short intended_target_index, _fixed damage_scale);

static void update_guided_projectile(short projectile_index);

// LP change: added a location of hitting something;
// it may be different from the new location,
// as may happen for a "penetrates media boundary" projectile.
static uint16 translate_projectile(short type, world_point3d *old_location, short old_polygon_index,
	world_point3d *new_location, short *new_polygon_index, short owner_index,
	short *obstruction_index);

/*static*/ projectile_definition *get_projectile_definition(
	short type);

/* ---------- code */



uint8 *unpack_projectile_data(uint8 *Stream, projectile_data* Objects, size_t Count)
{
	uint8* S = Stream;
	projectile_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->type);
		
		StreamToValue(S,ObjPtr->object_index);
		
		StreamToValue(S,ObjPtr->target_index);
		
		StreamToValue(S,ObjPtr->elevation);
		
		StreamToValue(S,ObjPtr->owner_index);
		StreamToValue(S,ObjPtr->owner_type);
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->ticks_since_last_contrail);
		StreamToValue(S,ObjPtr->contrail_count);
		
		StreamToValue(S,ObjPtr->distance_travelled);
		
		StreamToValue(S,ObjPtr->gravity);
		
		StreamToValue(S,ObjPtr->damage_scale);
		
		StreamToValue(S,ObjPtr->permutation);
		
		S += 2*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_projectile_data));
	return S;
}

uint8 *pack_projectile_data(uint8 *Stream, projectile_data* Objects, size_t Count)
{
	uint8* S = Stream;
	projectile_data* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->type);
		
		ValueToStream(S,ObjPtr->object_index);
		
		ValueToStream(S,ObjPtr->target_index);
		
		ValueToStream(S,ObjPtr->elevation);
		
		ValueToStream(S,ObjPtr->owner_index);
		ValueToStream(S,ObjPtr->owner_type);
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->ticks_since_last_contrail);
		ValueToStream(S,ObjPtr->contrail_count);
		
		ValueToStream(S,ObjPtr->distance_travelled);
		
		ValueToStream(S,ObjPtr->gravity);
		
		ValueToStream(S,ObjPtr->damage_scale);
		
		ValueToStream(S,ObjPtr->permutation);
		
		S += 2*2;
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_projectile_data));
	return S;
}


uint8 *unpack_projectile_definition(uint8 *Stream, projectile_definition *Objects, size_t Count)
{
	uint8* S = Stream;
	projectile_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		StreamToValue(S,ObjPtr->collection);
		StreamToValue(S,ObjPtr->shape);
		StreamToValue(S,ObjPtr->detonation_effect);
		StreamToValue(S,ObjPtr->media_detonation_effect);
		StreamToValue(S,ObjPtr->contrail_effect);
		StreamToValue(S,ObjPtr->ticks_between_contrails);
		StreamToValue(S,ObjPtr->maximum_contrails);
		StreamToValue(S,ObjPtr->media_projectile_promotion);
		
		StreamToValue(S,ObjPtr->radius);
		StreamToValue(S,ObjPtr->area_of_effect);
		S = unpack_damage_definition(S,&ObjPtr->damage,1);
		
		StreamToValue(S,ObjPtr->flags);
		
		StreamToValue(S,ObjPtr->speed);
		StreamToValue(S,ObjPtr->maximum_range);
		
		StreamToValue(S,ObjPtr->sound_pitch);
		StreamToValue(S,ObjPtr->flyby_sound);
		StreamToValue(S,ObjPtr->rebound_sound);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_projectile_definition));
	return S;
}

uint8 *unpack_projectile_definition(uint8 *Stream, size_t Count)
{
	return unpack_projectile_definition(Stream,projectile_definitions,Count);
}


uint8 *pack_projectile_definition(uint8 *Stream, projectile_definition *Objects, size_t Count)
{
	uint8* S = Stream;
	projectile_definition* ObjPtr = Objects;
	
	for (size_t k = 0; k < Count; k++, ObjPtr++)
	{
		ValueToStream(S,ObjPtr->collection);
		ValueToStream(S,ObjPtr->shape);
		ValueToStream(S,ObjPtr->detonation_effect);
		ValueToStream(S,ObjPtr->media_detonation_effect);
		ValueToStream(S,ObjPtr->contrail_effect);
		ValueToStream(S,ObjPtr->ticks_between_contrails);
		ValueToStream(S,ObjPtr->maximum_contrails);
		ValueToStream(S,ObjPtr->media_projectile_promotion);
		
		ValueToStream(S,ObjPtr->radius);
		ValueToStream(S,ObjPtr->area_of_effect);
		S = pack_damage_definition(S,&ObjPtr->damage,1);
		
		ValueToStream(S,ObjPtr->flags);
		
		ValueToStream(S,ObjPtr->speed);
		ValueToStream(S,ObjPtr->maximum_range);
		
		ValueToStream(S,ObjPtr->sound_pitch);
		ValueToStream(S,ObjPtr->flyby_sound);
		ValueToStream(S,ObjPtr->rebound_sound);
	}
	
	assert((S - Stream) == static_cast<ptrdiff_t>(Count*SIZEOF_projectile_definition));
	return S;
}

uint8 *pack_projectile_definition(uint8 *Stream, size_t Count)
{
	return pack_projectile_definition(Stream,projectile_definitions,Count);
}

struct projectile_definition projectile_definitions[NUMBER_OF_PROJECTILE_TYPES]=
{
	{	/* player’s rocket */
		_collection_rocket, 0, /* collection number, shape number */
		_effect_rocket_explosion, NONE, /* detonation effect, media_detonation_effect */
		_effect_rocket_contrail, 1, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
			
		WORLD_ONE/8, /* radius */
		WORLD_ONE+WORLD_ONE_HALF, /* area-of-effect */
		{_damage_explosion, 0, 250, 50}, /* damage */
		
		_can_toggle_control_panels|_guided, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		_snd_rocket_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* player’s grenade */
		_collection_rocket, 3, /* collection number, shape number */
		_effect_grenade_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_grenade_contrail, 1, 8, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
		
		0, /* radius */
		WORLD_THREE_FOURTHS, /* area-of-effect */
		{_damage_explosion, 0, 80, 20}, /* damage */
		
		_affected_by_gravity|_can_toggle_control_panels, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		_snd_grenade_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* player’s pistol bullet */
		NONE, 0, /* collection number, shape number */
		_effect_bullet_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_projectile, 0, 20, 8}, /* damage */
		
		_bleeding_projectile|_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* player’s rifle bullet */
		NONE, 0, /* collection number, shape number */
		_effect_bullet_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_projectile, 0, 9, 6}, /* damage */
		
		_bleeding_projectile|_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* player’s shotgun bullet */
		NONE, 0, /* collection number, shape number */
		_effect_bullet_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_shotgun_projectile, 0, 20, 4}, /* damage */
		
		_bleeding_projectile|_can_toggle_control_panels|_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* electrical melee staff */
		NONE, 0, /* collection number, shape number */
		_effect_fighter_melee_detonation, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_electrical_staff, _alien_damage, 20, 5}, /* damage */
		
		_sometimes_pass_transparent_side|_alien_projectile|_melee_projectile|_penetrates_media, /* flags */
		
		WORLD_ONE_HALF, /* speed */
		WORLD_ONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* electrical melee staff projectile */
		BUILD_COLLECTION(_collection_fighter, 2), 9, /* collection number, shape number */
		_effect_fighter_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_electrical_staff, _alien_damage, 30, 5}, /* damage */
		
		_sometimes_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_fighter_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* player’s flame thrower burst */
		_collection_rocket, 6, /* collection number, shape number */
		NONE, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
		
		WORLD_ONE/3, /* radius */
		0, /* area-of-effect */
		{_damage_flame, 0, 8, 4}, /* damage */
		
		_sometimes_pass_transparent_side|_stop_when_animation_loops|_persistent, /* flags */
		
		WORLD_ONE/3, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_compiler_bolt_minor */
		BUILD_COLLECTION(_collection_compiler, 0), 4, /* collection number, shape number */
		_effect_compiler_bolt_minor_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_compiler_bolt, _alien_damage, 40, 10}, /* damage */
		
		_sometimes_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_compiler_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_compiler_bolt_major */
		BUILD_COLLECTION(_collection_compiler, 1), 4, /* collection number, shape number */
		_effect_compiler_bolt_major_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_compiler_bolt_major_contrail, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_compiler_bolt, _alien_damage, 40, 10}, /* damage */
		
		_sometimes_pass_transparent_side|_alien_projectile|_guided, /* flags */
		
		WORLD_ONE/12, /* speed */
		NONE, /* maximum range */

		_higher_frequency, /* sound pitch */
		_snd_compiler_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* alien weapon */
		_collection_rocket, 22, /* collection number, shape number */
		_effect_alien_weapon_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/10, /* radius */
		0, /* area-of-effect */
		{_damage_alien_projectile, _alien_damage, 20, 8}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile|_can_toggle_control_panels, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */

		_snd_enforcer_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* _projectile_fusion_minor */
		_collection_rocket, 11, /* collection number, shape number */
		_effect_minor_fusion_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		_projectile_minor_fusion_dispersal, /* media projectile promotion */

		WORLD_ONE/20, /* radius */
		0, /* area-of-effect */
		{_damage_fusion_bolt, 0, 30, 10}, /* damage */
		
		_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_fusion_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_fusion_major */
		_collection_rocket, 12, /* collection number, shape number */
		_effect_major_fusion_detonation, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_major_fusion_contrail, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		_projectile_major_fusion_dispersal, /* media projectile promotion */

		WORLD_ONE/10, /* radius */
		0, /* area-of-effect */
		{_damage_fusion_bolt, 0, 80, 20}, /* damage */
		
		_sometimes_pass_transparent_side|_can_toggle_control_panels, /* flags */
		
		WORLD_ONE/3, /* speed */
		NONE, /* maximum range */

		_higher_frequency, /* sound pitch */
		_snd_fusion_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_hunter */
		BUILD_COLLECTION(_collection_hunter, 0), 5, /* collection number, shape number */
		_effect_hunter_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_hunter_bolt, 0, 15, 5}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_hunter_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_fist */
		NONE, 0, /* collection number, shape number */
		_effect_fist_detonation, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/4, /* radius */
		0, /* area-of-effect */
		{_damage_fist, 0, 50, 10}, /* damage (will be scaled by player’s velocity) */
		
		_usually_pass_transparent_side|_can_toggle_control_panels|_melee_projectile|_penetrates_media, /* flags */
		
		(3*WORLD_ONE)/4, /* speed */
		(3*WORLD_ONE)/4, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_armageddon_sphere */
		0
	},

	{	/* _projectile_armageddon_electricity */
		0
	},

	{ /* _projectile_juggernaut_rocket */
		_collection_rocket, 0, /* collection number, shape number */
		_effect_rocket_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_rocket_contrail, 1, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
		
		WORLD_ONE/8, /* radius */
		WORLD_ONE+WORLD_ONE_HALF, /* area-of-effect */
		{_damage_explosion, _alien_damage, 250, 50}, /* damage */
		
		_guided|_can_toggle_control_panels, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{ /* _projectile_trooper_bullet */
		NONE, 0, /* collection number, shape number */
		_effect_bullet_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_projectile, _alien_damage, 15, 4}, /* damage */
		
		_bleeding_projectile|_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
	
	{ /* _projectile_trooper_grenade */
		_collection_trooper, 5, /* collection number, shape number */
		_effect_grenade_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_grenade_contrail, 1, 8, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
		
		0, /* radius */
		WORLD_THREE_FOURTHS, /* area-of-effect */
		{_damage_explosion, _alien_damage, 40, 20}, /* damage */
		
		_affected_by_gravity|_can_toggle_control_panels, /* flags */
		
		WORLD_ONE/5, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
	
	{ /* _projectile_minor_defender */
		BUILD_COLLECTION(_collection_defender, 0), 4, /* collection number, shape number */
		_effect_minor_defender_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/4, /* radius */
		0, /* area-of-effect */
		{_damage_defender, 0, 30, 8}, /* damage */
		
		_usually_pass_transparent_side, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_defender_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	{ /* _projectile_major_defender */
		BUILD_COLLECTION(_collection_defender, 1), 4, /* collection number, shape number */
		_effect_major_defender_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/4, /* radius */
		0, /* area-of-effect */
		{_damage_defender, 0, 30, 8}, /* damage */
		
		_usually_pass_transparent_side|_guided, /* flags */
		
		WORLD_ONE/6, /* speed */
		NONE, /* maximum range */

		_higher_frequency, /* sound pitch */
		_snd_defender_flyby, NONE, /* flyby sound, rebound sound */
	},

	{ /* _projectile_juggernaut_missile */
		_collection_juggernaut, 4, /* collection number, shape number */
		_effect_grenade_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_juggernaut_missile_contrail, 2, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */
		
		0, /* radius */
		WORLD_THREE_FOURTHS, /* area-of-effect */
		{_damage_explosion, _alien_damage, 40, 20}, /* damage */
		
		_affected_by_half_gravity|_can_toggle_control_panels|_guided|_positive_vertical_error, /* flags */
		
		WORLD_ONE/5, /* speed */
		NONE, /* maximum range */
		
		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_minor_energy_drain */
		NONE, 0, /* collection number, shape number */
		NONE, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/8, /* radius */
		0, /* area-of-effect */
		{_damage_energy_drain, 0, 4, 0}, /* damage (will be scaled by player’s velocity) */
		
		_melee_projectile|_penetrates_media, /* flags */
		
		(3*WORLD_ONE)/4, /* speed */
		(3*WORLD_ONE)/4, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_major_energy_drain */
		NONE, 0, /* collection number, shape number */
		NONE, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/8, /* radius */
		0, /* area-of-effect */
		{_damage_energy_drain, 0, 8, 0}, /* damage (will be scaled by player’s velocity) */
		
		_melee_projectile|_penetrates_media, /* flags */
		
		(3*WORLD_ONE)/4, /* speed */
		(3*WORLD_ONE)/4, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_oxygen_drain */
		NONE, 0, /* collection number, shape number */
		NONE, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/8, /* radius */
		0, /* area-of-effect */
		{_damage_oxygen_drain, 0, 4, 0}, /* damage (will be scaled by player’s velocity) */
		
		_melee_projectile|_penetrates_media, /* flags */
		
		(3*WORLD_ONE)/4, /* speed */
		(3*WORLD_ONE)/4, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_hummer_slow */
		BUILD_COLLECTION(_collection_hummer, 0), 5, /* collection number, shape number */
		_effect_minor_hummer_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_hummer_bolt, 0, 15, 5}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_hummer_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_hummer_fast */
		BUILD_COLLECTION(_collection_hummer, 1), 5, /* collection number, shape number */
		_effect_major_hummer_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_hummer_bolt, 0, 15, 5}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/6, /* speed */
		NONE, /* maximum range */

		_higher_frequency, /* sound pitch */
		_snd_hummer_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_hummer_durandal */
		BUILD_COLLECTION(_collection_hummer, 1), 5, /* collection number, shape number */
		_effect_durandal_hummer_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_hummer_bolt, 0, 15, 5}, /* damage */
		
		_guided|_usually_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_lower_frequency, /* sound pitch */
		_snd_hummer_projectile_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_minor_cyborg_ball */
		BUILD_COLLECTION(_collection_cyborg, 0), 6, /* collection number, shape number */
		_effect_grenade_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_grenade_contrail, 1, 8, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/8, /* radius */
		WORLD_ONE, /* area-of-effect */
		{_damage_explosion, 0, 20, 10}, /* damage */
		
		_can_toggle_control_panels|_sometimes_pass_transparent_side|_alien_projectile|_rebounds_from_floor|_doubly_affected_by_gravity, /* flags */
		
		WORLD_ONE/10, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_cyborg_projectile_flyby, _snd_cyborg_projectile_bounce, /* flyby sound, rebound sound */
	},

	{	/* _projectile_major_cyborg_ball */
		BUILD_COLLECTION(_collection_cyborg, 1), 6, /* collection number, shape number */
		_effect_grenade_explosion, _medium_media_detonation_effect, /* detonation effect, media_detonation_effect */
		_effect_grenade_contrail, 1, 8, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/8, /* radius */
		WORLD_ONE, /* area-of-effect */
		{_damage_explosion, 0, 40, 10}, /* damage */
		
		_guided|_can_toggle_control_panels|_sometimes_pass_transparent_side|_alien_projectile|_rebounds_from_floor|_doubly_affected_by_gravity, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_lower_frequency, /* sound pitch */
		_snd_cyborg_projectile_flyby, _snd_cyborg_projectile_bounce, /* flyby sound, rebound sound */
	},

	{	/* _projectile_ball */
		BUILD_COLLECTION(_collection_player, 0), 0, /* collection number, shape number */
		NONE, NONE, /* detonation effect, media_detonation_effect */
		NONE, 1, 8, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/4, /* radius */
		NONE, /* area-of-effect */
		{NONE, 0, 40, 10}, /* damage */
		
		_persistent_and_virulent|_penetrates_media|_becomes_item_on_detonation|_can_toggle_control_panels|_rebounds_from_floor|_doubly_affected_by_gravity|_penetrates_media, /* flags */
		
		0, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, _snd_ball_bounce, /* flyby sound, rebound sound */
	},

	{	/* _projectile_minor_fusion_dispersal */
		_collection_rocket, 11, /* collection number, shape number */
		_effect_minor_fusion_dispersal, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/20, /* radius */
		WORLD_ONE, /* area-of-effect */
		{_damage_fusion_bolt, 0, 30, 10}, /* damage */
		
		0, /* flags */
		
		WORLD_ONE/4, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_fusion_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_major_fusion_dispersal */
		_collection_rocket, 12, /* collection number, shape number */
		_effect_major_fusion_dispersal, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/10, /* radius */
		2*WORLD_ONE, /* area-of-effect */
		{_damage_fusion_bolt, 0, 80, 20}, /* damage */
		
		0, /* flags */
		
		WORLD_ONE/3, /* speed */
		NONE, /* maximum range */

		_higher_frequency, /* sound pitch */
		_snd_fusion_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_overloaded_fusion_dispersal */
		_collection_rocket, 12, /* collection number, shape number */
		_effect_overloaded_fusion_dispersal, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		WORLD_ONE/10, /* radius */
		4*WORLD_ONE, /* area-of-effect */
		{_damage_fusion_bolt, 0, 500, 0}, /* damage */
		
		0, /* flags */
		
		WORLD_ONE/3, /* speed */
		NONE, /* maximum range */

		_lower_frequency, /* sound pitch */
		_snd_fusion_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_yeti */
		NONE, 0, /* collection number, shape number */
		_effect_yeti_melee_detonation, NONE, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_yeti_claws, _alien_damage, 20, 5}, /* damage */
		
		_sometimes_pass_transparent_side|_alien_projectile|_melee_projectile|_penetrates_media, /* flags */
		
		WORLD_ONE_HALF, /* speed */
		WORLD_ONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
	
	{	/* _projectile_sewage_yeti */
		BUILD_COLLECTION(_collection_yeti, 0), 10, /* collection number, shape number */
		_effect_sewage_yeti_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_yeti_projectile, 0, 15, 5}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile|_affected_by_half_gravity, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_yeti_projectile_sewage_flyby, NONE, /* flyby sound, rebound sound */
	},

	{	/* _projectile_lava_yeti */
		BUILD_COLLECTION(_collection_yeti, 2), 6, /* collection number, shape number */
		_effect_lava_yeti_projectile_detonation, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, NONE, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_flame, 0, 30, 10}, /* damage */
		
		_usually_pass_transparent_side|_alien_projectile, /* flags */
		
		WORLD_ONE/8, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		_snd_yeti_projectile_lava_flyby, NONE, /* flyby sound, rebound sound */
	},
	
	// LP addition: SMG bullet is a clone of the rifle one, except for entering/exiting liquids
	{	/* player’s smg bullet */
		NONE, 0, /* collection number, shape number */
		_effect_bullet_ricochet, _small_media_detonation_effect, /* detonation effect, media_detonation_effect */
		NONE, 0, 0, /* contrail effect, ticks between contrails, maximum contrails */
		NONE, /* media projectile promotion */

		0, /* radius */
		0, /* area-of-effect */
		{_damage_projectile, 0, 9, 6}, /* damage */
		
		_bleeding_projectile|_usually_pass_transparent_side|_penetrates_media_boundary, /* flags */
		
		WORLD_ONE, /* speed */
		NONE, /* maximum range */

		_normal_frequency, /* sound pitch */
		NONE, NONE, /* flyby sound, rebound sound */
	},
};
