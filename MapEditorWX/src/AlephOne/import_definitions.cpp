/*
IMPORT_DEFINITIONS.C

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

Sunday, October 2, 1994 1:25:23 PM  (Jason')

Aug 12, 2000 (Loren Petrich):
	Using object-oriented file handler

Aug 31, 2000 (Loren Petrich):
	Added unpacking code for the physics models
*/

//#include "cseries.h"
#include <string.h>

#include "tags.h"
#include "map.h"
#include "interface.h"
#include "game_wad.h"
#include "wad.h"
#include "game_errors.h"
/*
#include "shell.h"
#include "preferences.h"
*/
#include "FileHandler.h"
//#include "shell.h"
//#include "preferences.h"

// LP: get all the unpacker definitions
#include "monsters.h"
#include "effects.h"
#include "projectiles.h"
#include "player.h"
#include "weapons.h"

#include "monster_definitions.h"
#include "effect_definitions.h"
#include "projectile_definitions.h"
#include "physics_models.h"
#include "weapon_definitions.h"
#include "crc.h"

/* ---------- globals */

#define IMPORT_STRUCTURE
#include "extensions.h"
#define CURRENT_PREF_WADFILE_VERSION 0
#define MARATHON_INFINITY_DATA_VERSION 2

/* ---------- local globals */
static FileSpecifier PhysicsFileSpec;
static struct wad_header storedHeader;
static size_t monsterCount, effectCount, physicsCount, projectileCount, weaponCount;

/* ---------- local prototype */
static struct wad_data *get_physics_wad_data(bool *bungie_physics);
static void import_physics_wad_data(struct wad_data *wad);
static struct wad_data *export_physics_wad_data();
/* ---------- code */
void set_physics_file(FileSpecifier& File)
{
	PhysicsFileSpec = File;
}

void set_to_default_physics_file(
	void)
{
	get_default_physics_spec(PhysicsFileSpec);
//	dprintf("Set to: %d %d %.*s", physics_file.vRefNum, physics_file.parID, physics_file.name[0], physics_file.name+1);
}

void import_definition_structures(
	void)
{
	struct wad_data *wad;
	bool bungie_physics;
	static bool warned_about_physics= false;

	wad= get_physics_wad_data(&bungie_physics);
	if(wad)
	{
		//if(!bungie_physics && !warned_about_physics && environment_preferences->non_bungie_warning)
		if (0)
		{
			/* warn the user that external physics models are Bad Thingｪ */
			//alert_user(infoError, strERRORS, warningExternalPhysicsModel, 0);

			warned_about_physics= true;
		}
		
		/* Actually load it in.. */		
		import_physics_wad_data(wad);
		
		free_wad(wad);
    }else{
//        MessageBox(NULL, L"読み込み失敗(get_physics_wad_data)", L"エラー", MB_OK | MB_ICONEXCLAMATION);
    }
}

void export_definition_structures(const char *filename)
{
	struct wad_data *wad;
    if(strcmp(filename, DEFAULT_PHYSICS_FILE_NAME) == 0){
//        MessageBox(NULL, L"そのファイルには保存できません", L"エラー", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
	//格納されているデータをwadデータに流し込み
	wad = export_physics_wad_data();
	if(wad){
		//ファイルへ出力
		FileSpecifier phy = FileSpecifier(filename);

    	struct directory_entry entry;
        struct wad_header head;

        //デフォルトにする
        fill_default_wad_header(phy, 0,
            PHYSICS_DATA_VERSION,
            1, 0l, &head);
        
        //WADの長さ計算
        long wad_length = calculate_wad_length(&head, wad);
        long offset = SIZEOF_wad_header;

        //エントリーデータセット
        set_indexed_directory_offset_and_length(&head, 
			&entry, 0, offset, wad_length, 0);

        //ファイルを開く
		bool writable = true;
		OpenedFile of;
		//phy.Open(of, writable);
        if(!open_wad_file_for_writing(phy, of)){
//            MessageBox(NULL, L"ファイルを開けません", L"エラー", MB_OK | MB_ICONEXCLAMATION);
            return;
        }

		if(write_wad(of, &head, wad, offset)){
//			MessageBox(NULL, L"ファイルの保存に成功しました", L"", MB_OK | MB_ICONINFORMATION);
    	}else{
			//不成功
 //           MessageBox(NULL, L"ファイルの保存に失敗しました", L"エラー", MB_OK | MB_ICONEXCLAMATION);
            return ;
		}

        //新しいヘッダへ更新
        offset+= wad_length;
		head.directory_offset= offset;
        //head.parent_checksum = 0;
		//Header.checksum = calculate_crc_for_opened_file(PhysicsFile);
		//Header.checksum = read_wad_file_checksum( PhysicsFileSpec);
		write_wad_header( of, &head);
		write_directorys( of, &head, &entry);

		//printf("Header.checksum=%d\n",Header.checksum);
		close_wad_file(of);

        //write_wad_header(of, &head);
        //calculate_and_store_wadfile_checksum(of);
	
        /*
        if(open_wad_file_for_reading( phy, of)){
		    //calculate_and_store_wadfile_checksum( PhysicsFile);
		    head.checksum= calculate_crc_for_opened_file(of);
		    //printf("Header.checksum=%d\n",head.checksum);
		    //Header.checksum = read_wad_file_checksum( PhysicsFileSpec);
		    //printf("Header.checksum=%d\n",Header.checksum);

		    close_wad_file(of);
	    }
	    if(open_wad_file_for_writing(phy, of)){
    	    struct directory_entry entry;
		    int offset = sizeof(struct wad_header);
		    write_wad( of, &head, wad, offset);
		    write_wad_header(of, &head);
		    write_directorys( of, &head, &entry);
		    close_wad_file(of);
	    }*/
		free_wad(wad);
    }else{
//		MessageBox(NULL, L"データを作成できませんでした", L"エラー", MB_OK | MB_ICONEXCLAMATION);
    }

}

void *get_network_physics_buffer(
	long *physics_length)
{
	void *data= get_flat_data(PhysicsFileSpec, false, 0);
	
	if(data)
	{
		*physics_length= get_flat_data_length(data);
	} else {
		*physics_length= 0;
	}
	
	return data;
}

void process_network_physics_model(
	void *data)
{
	if(data)
	{
		struct wad_header header;
		struct wad_data *wad;
	
		wad= inflate_flat_data(data, &header);
		if(wad)
		{
			import_physics_wad_data(wad);
			free_wad(wad); /* Note that the flat data points into the wad. */
		}
	}
}

/* --------- local code */
static struct wad_data *get_physics_wad_data(
	bool *bungie_physics)
{
	struct wad_data *wad= NULL;
	
//	dprintf("Open is: %d %d %.*s", physics_file.vRefNum, physics_file.parID, physics_file.name[0], physics_file.name+1);

	OpenedFile PhysicsFile;
	if(open_wad_file_for_reading(PhysicsFileSpec,PhysicsFile))
	{
		struct wad_header header;
		
		if(read_wad_header(PhysicsFile, &header))
		{
			if(header.data_version==BUNGIE_PHYSICS_DATA_VERSION || header.data_version==PHYSICS_DATA_VERSION)
			{
				//memcpy(&storedHeader, &header, sizeof(struct wad_header));

				wad= read_indexed_wad_from_file(PhysicsFile, &header, 0, true);
				if(header.data_version==BUNGIE_PHYSICS_DATA_VERSION)
				{
					*bungie_physics= true;
				} else {
					*bungie_physics= false;
				}
			}
		}

		close_wad_file(PhysicsFile);
	} 
	
	/* Reset any errors that might have occurred.. */
	set_game_error(systemError, errNone);

	return wad;
}

static void import_physics_wad_data(
	struct wad_data *wad)
{
	// LP: this code is copied out of game_wad.c
	size_t data_length;
	byte *data;
	size_t count;
	bool PhysicsModelLoaded = false;
	
	data= (unsigned char *)extract_type_from_wad(wad, MONSTER_PHYSICS_TAG, &data_length);
	count = data_length/SIZEOF_monster_definition;
	assert(count*SIZEOF_monster_definition == data_length);
	assert(count <= NUMBER_OF_MONSTER_TYPES);
	if (data_length > 0)
	{
		monsterCount = count;
		PhysicsModelLoaded = true;
		unpack_monster_definition(data,count);
    }else{
//        MessageBox(NULL, L"モンスター情報がありません", L"エラー", MB_OK | MB_ICONEXCLAMATION);
    }
	
	data= (unsigned char *)extract_type_from_wad(wad, EFFECTS_PHYSICS_TAG, &data_length);
	count = data_length/SIZEOF_effect_definition;
	assert(count*SIZEOF_effect_definition == data_length);
	assert(count <= NUMBER_OF_EFFECT_TYPES);
	if (data_length > 0)
	{
		effectCount = count;
		PhysicsModelLoaded = true;
		unpack_effect_definition(data,count);
	}
	
	data= (unsigned char *)extract_type_from_wad(wad, PROJECTILE_PHYSICS_TAG, &data_length);
	count = data_length/SIZEOF_projectile_definition;
	assert(count*SIZEOF_projectile_definition == data_length);
	assert(count <= NUMBER_OF_PROJECTILE_TYPES);
	if (data_length > 0)
	{
		projectileCount= count;
		PhysicsModelLoaded = true;
		unpack_projectile_definition(data,count);
	}
	
	data= (unsigned char *)extract_type_from_wad(wad, PHYSICS_PHYSICS_TAG,
		&data_length);
	count = data_length/SIZEOF_physics_constants;
	assert(count*SIZEOF_physics_constants == data_length);
	assert(count <= get_number_of_physics_models());
	if (data_length > 0)
	{
		physicsCount = count;
		PhysicsModelLoaded = true;
		unpack_physics_constants(data,count);
	}
	
	data= (unsigned char*) extract_type_from_wad(wad, WEAPONS_PHYSICS_TAG, &data_length);
	count = data_length/SIZEOF_weapon_definition;
	assert(count*SIZEOF_weapon_definition == data_length);
	assert(count <= get_number_of_weapon_types());
	if (data_length > 0)
	{
		weaponCount= count;
		PhysicsModelLoaded = true;
		unpack_weapon_definition(data,count);
	}
}

struct wad_data *export_physics_wad_data(void){
	//空のwadデータ
	struct wad_data *wad = create_empty_wad();
	
    size_t offset = 0;//sizeof(struct wad_header);
    
    size_t alloc_size;
    Uint8* data;
    

    alloc_size = SIZEOF_monster_definition * monsterCount;
    data = new Uint8[alloc_size];
	pack_monster_definition(data, monsterCount);
	append_data_to_wad(wad, MONSTER_PHYSICS_TAG, data, alloc_size, offset);
	offset += alloc_size;
    delete data;

    alloc_size = SIZEOF_effect_definition * effectCount;
    data = new Uint8[alloc_size];
	pack_effect_definition(data, effectCount);
	append_data_to_wad(wad, EFFECTS_PHYSICS_TAG, data, alloc_size, offset);
	offset += alloc_size;
    delete data;

    alloc_size = SIZEOF_projectile_definition * projectileCount;
    data = new Uint8[alloc_size];
	pack_projectile_definition(data, projectileCount);
	append_data_to_wad(wad, PROJECTILE_PHYSICS_TAG, data, alloc_size, offset);
	offset += alloc_size;
    delete data;

    alloc_size = SIZEOF_physics_constants * physicsCount;
    data = new Uint8[alloc_size];
	pack_physics_constants(data, physicsCount);
	append_data_to_wad(wad, PHYSICS_PHYSICS_TAG, data, alloc_size, offset);
	offset += alloc_size;
    delete data;

    alloc_size = SIZEOF_weapon_definition * weaponCount;
    data = new Uint8[alloc_size];
	pack_weapon_definition(data, weaponCount);
	append_data_to_wad(wad, WEAPONS_PHYSICS_TAG, data, alloc_size, offset);
	//offset += alloc_size;
    delete data;

	return wad;
}