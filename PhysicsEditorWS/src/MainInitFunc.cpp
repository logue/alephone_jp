#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

#include <stdarg.h>

int windowType = Windows::Monster;
int selectedMonsterType;
int selectedEffectType;
int selectedProjectileType;
int selectedPhysicsType;
int selectedWeaponType;
int selectIndex;

struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];
struct effect_definition effect_default_definitions[NUMBER_OF_EFFECT_TYPES];
struct projectile_definition projectile_default_definitions[NUMBER_OF_PROJECTILE_TYPES];
struct physics_constants physics_default_models[NUMBER_OF_PHYSICS_MODELS];
struct weapon_definition weapon_default_definitions[MAXIMUM_NUMBER_OF_WEAPONS];

std::vector<std::string> stockCollections;
std::vector<std::string> stockMonsterClasses;
std::vector<std::string> stockSpeeds;
std::vector<std::string> stockItemTypes;
std::vector<std::string> stockEffects;
std::vector<std::string> stockProjectiles;
std::vector<std::string> stockSounds;
std::vector<std::string> stockDamages;
std::vector<std::string> stockMonsterActivates;
std::vector<std::string> stockMonsterDoorRetryMasks;
std::vector<std::string> stockWeaponClasses;
std::vector<std::string> stockShellCasingTypes;
std::vector<std::string> stockPhysicsTypes;
std::vector<std::string> stockMonsterFlags;
std::vector<std::string> stockProjectileFlags;
std::vector<std::string> stockWeaponFlags;

//モンスター区分
int valueMonsterClasses[NUMBER_OF_CLASS_INFORMATIONS]={
    _class_player, _class_human_civilian, _class_madd, _class_possessed_hummer,
    _class_defender,
    _class_fighter, _class_trooper, _class_hunter, _class_enforcer, _class_juggernaut,
    _class_compiler, _class_cyborg, _class_assimilated_civilian,
    _class_hummer, _class_tick, _class_yeti
};
//速度の規定値
int valueSpeed[NUMBER_OF_SPEED_INFORMATIONS]={
    _speed_slow, _speed_medium, _speed_almost_fast, _speed_fast,
    _speed_superfast1, _speed_superfast2, _speed_superfast3, 
    _speed_superfast4, _speed_superfast5, 
    _speed_blinding, _speed_insane
};
int valueIntelligences[NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS]={
    _intelligence_low, _intelligence_average, _intelligence_high
};
//ドアマスク
int valueMonsterDoorRetryMask[NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS]={
    _slow_door_retry_mask, _normal_door_retry_mask,
    _fast_door_retry_mask, _vidmaster_door_retry_mask
};
//モンスターフラグ
int valueMonsterFlags[NUMBER_OF_MONSTER_FLAG_INFORMATIONS]={
	_monster_is_omniscent,
    _monster_flys,
    _monster_is_alien,
    _monster_major,
    _monster_minor,
    _monster_cannot_be_dropped,
    _monster_floats,
    _monster_cannot_attack,
    _monster_uses_sniper_ledges,
    _monster_is_invisible,
    _monster_is_subtly_invisible,
    _monster_is_kamakazi,
    _monster_is_berserker,
    _monster_is_enlarged,
    _monster_has_delayed_hard_death,
    _monster_fires_symmetrically,
    _monster_has_nuclear_hard_death,
    _monster_cant_fire_backwards,
    _monster_can_die_in_flames,
    _monster_waits_with_clear_shot,
    _monster_is_tiny,
    _monster_attacks_immediately,
    _monster_is_not_afraid_of_water,
    _monster_is_not_afraid_of_sewage,
    _monster_is_not_afraid_of_lava,
    _monster_is_not_afraid_of_goo,
    _monster_can_teleport_under_media,
    _monster_chooses_weapons_randomly
};
//エフェクトフラグ
int valueEffectFlags[NUMBER_OF_EFFECT_FLAG_INFORMATIONS]={
	_end_when_animation_loops,
    _end_when_transfer_animation_loops,
    _sound_only,
    _make_twin_visible,
    _media_effect
};
int valueWeaponFlags[NUMBER_OF_WEAPON_FLAG_INFORMATIONS]={
	_weapon_is_automatic,
    _weapon_disappears_after_use,
    _weapon_plays_instant_shell_casing_sound,
    _weapon_overloads,
    _weapon_has_random_ammo_on_pickup,
    _powerup_is_temporary,
    _weapon_reloads_in_one_hand,
    _weapon_fires_out_of_phase,
    _weapon_fires_under_media,
    _weapon_triggers_share_ammo,
    _weapon_secondary_has_angular_flipping
};
int valueProjectileFlags[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS]={
	 _guided,
    _stop_when_animation_loops,
    _persistent,
    _alien_projectile,
    _affected_by_gravity,
    _no_horizontal_error,
    _no_vertical_error,
    _can_toggle_control_panels,
    _positive_vertical_error,
    _melee_projectile,
    _persistent_and_virulent,
    _usually_pass_transparent_side,
    _sometimes_pass_transparent_side,
    _doubly_affected_by_gravity,
    _rebounds_from_floor,
    _penetrates_media,
    _becomes_item_on_detonation,
    _bleeding_projectile,
    _horizontal_wander,
    _vertical_wander,
    _affected_by_half_gravity,
    _penetrates_media_boundary
};

void messageBox(const char* format, ...)
{
    char message[1024];

    va_list maker;
    va_start(maker, format);
    vsprintf(message, format, maker);

	WSCmessageDialog* msg = WSGIappMessageDialog(); //(G)
	msg->setProperty(WSNwidth,500);									//(H)
	msg->setProperty(WSNheight,120);								//(I)
	msg->setProperty(WSNdefaultPosition,True);			//(J)
	msg->setProperty(WSNlabelString, message);
	msg->popup();
}

std::string getOptionItemListFromVectorString(std::vector<std::string>& stocks)
{
	std::string itemList;
	itemList += stocks[0] + ":1:DummyEp";
	char buf[10];
	for(int i = 1; i < stocks.size(); i ++){
		itemList += ",";
		sprintf(buf, "%d", i + 1);
		itemList += stocks[i] + ":";
		itemList += std::string(buf) + ":DummyEp";
	}
	return itemList;
}

void setDefinitionsToDefault()
{
    //モンスター情報
    memcpy(monster_definitions, monster_default_definitions, sizeof(struct monster_definition) * NUMBER_OF_MONSTER_TYPES);
    memcpy(effect_definitions, effect_default_definitions, sizeof(struct effect_definition) * NUMBER_OF_EFFECT_TYPES);
    memcpy(projectile_definitions, projectile_default_definitions, sizeof(struct projectile_definition) * NUMBER_OF_PROJECTILE_TYPES);
    memcpy(physics_models, physics_default_models, sizeof(struct physics_constants) * NUMBER_OF_PHYSICS_MODELS);
    memcpy(weapon_definitions, weapon_default_definitions, sizeof(struct weapon_definition) * MAXIMUM_NUMBER_OF_WEAPONS);
}

WSCbase* getObject(const char* class_name, const char* obj_name)
{
	WSCbase* obj = WSGIappObjectList()->getInstance((char*)class_name,(char*)obj_name);
	if(obj == NULL){
		messageBox("ClassName[%s], ObjectName[%s] the Instance not found",
			class_name, obj_name);
		exit(1);
	}
	return obj;
}

WSCbase* getChild(WSCbase* parent, const char* obj_name)
{
	WSCbase* child = parent->getChildInstance((char*)obj_name);
	if(child == NULL){
		messageBox("ObjectName[%s] the Child Instance not found",
			obj_name);
		exit(1);
	}
	return child;
}

void setInteger(WSCbase* obj, int num)
{
	if(obj == NULL){
		messageBox("NULL OBJECT! @ setInteger");
		exit(1);
	}
	//vitality
	obj->setProperty(WSNlabelString, (long)num);
}

/*
int getSelectedValue(WSCoption *opt)
{
	WSCbool* status = opt->getSelectStatus();
	int max = opt->getItems();
	for(int i = 0; i < max; i ++){
		if(status[i]){
			return i;
		}
	}
	return 0;
}

void setSelectedValue(WSCoption *opt, int index)
{
	WSCbool* status = opt->getSelectStatus();
	int max = opt->getItems();
	for(int i = 0; i < max; i ++){
		bool st = false;
		if(i == index){
			st = true;
		}
		status[i] = st;
	}
}
*/

/*
	@return -1 when not found
*/
int getIndexFromValueArray(int *arr, int max, int target)
{
	for(int i = 0; i < max; i ++){
		if(arr[i] == target){
			return i;
		}
	}
	return -1;
}

long getInteger(WSCbase* obj)
{
	if(obj == NULL){
		messageBox("NULL (getInteger())");
	}
	long num = obj->getProperty(WSNlabelString);
	return num;
}

void setupTrigger(int triggerIndex, const char* addon, WSCbase* parent)
{
	int type = selectedWeaponType;
	int index = 0;
	std::string wstr = std::string("W") + addon;
	setInteger(getChild(parent, (wstr + "RoundPerMagEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].rounds_per_magazine);
	//ammo item(btn)
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].ammunition_type;
	if(index < 0 || index == UNONE){index = stockItemTypes.size() - 1;}
	getChild(parent, (wstr + "AmmoItemBtn").c_str())->setProperty(WSNlabelString,
		stockItemTypes[index].c_str());
	setInteger(getChild(parent, (wstr + "TicksPerRoundEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].ticks_per_round);
	setInteger(getChild(parent, (wstr + "RecovTicksEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].recovery_ticks);
	setInteger(getChild(parent, (wstr + "ChargingTicksEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].charging_ticks);
	setInteger(getChild(parent, (wstr + "RecoilMagnitudeEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].recoil_magnitude);
	//sounds(btn)
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].firing_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "FiringSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].click_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "ClickSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].charging_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "ChargingSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].shell_casing_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "ShellCasingSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].reloading_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "ReloadSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].charged_sound;
	if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
	getChild(parent, (wstr + "ChargedSndBtn").c_str())->setProperty(WSNlabelString,
		stockSounds[index].c_str());
	
	//projectile(btn)
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].projectile_type;
	if(index < 0 || index == UNONE){index = stockProjectiles.size() - 1;}
	if(index == _projectile_ball_dropped){index = stockProjectiles.size() -2;}
	getChild(parent, (wstr + "ProjectileBtn").c_str())->setProperty(WSNlabelString,
		stockProjectiles[index].c_str());
	setInteger(getChild(parent, (wstr + "ErrorEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].theta_error);
	setInteger(getChild(parent, (wstr + "dxEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].dx);
	setInteger(getChild(parent, (wstr + "dzEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].dz);
	//shell casing (option)
	index = weapon_definitions[type].weapons_by_trigger[triggerIndex].shell_casing_type;
	if(index < 0 || index == UNONE){index = stockShellCasingTypes.size() - 1;}
	getChild(parent, (wstr + "ShellCasingOption").c_str())->setProperty(WSNlabelString,
		stockShellCasingTypes[index].c_str());
	
	setInteger(getChild(parent, (wstr + "BurstCountEdit").c_str()),
		weapon_definitions[type].weapons_by_trigger[triggerIndex].burst_count);
}

void setupDialog()//WSCbase* object)
{
	if(windowType == Windows::Monster){
		//form
		WSCform* wnd = (WSCform*)getObject("WSCform", "FrmMonster");
		int type = selectedMonsterType;
		if(type >= 0 && type < NUMBER_OF_MONSTER_TYPES){
			//設定
			int16 collection = monster_definitions[type].collection;
			int16 col = GET_COLLECTION(collection);
			int16 clut = GET_COLLECTION_CLUT(collection);
			
			//index
			WSCindexForm* indextab = (WSCindexForm*)getChild(wnd, "Maiinde_012");
			//clut
			WSCvifield* clutField = (WSCvifield*)getChild(indextab, "PalletEdit");
			clutField->setProperty(WSNlabelString, (long)clut);
			//collection
			getChild(indextab, "CollectionBtn")->setProperty(WSNlabelString,
				stockCollections[col].c_str());
			
			//vitality
			char buf[256];
			setInteger(getChild(indextab, "VitalityEdit"), monster_definitions[type].vitality);
			//class
			int classIndex = getIndexFromValueArray(valueMonsterClasses, NUMBER_OF_CLASS_INFORMATIONS,
				monster_definitions[type]._class);
			if(classIndex >= 0){
				WSCbase* opt = getChild(indextab, "ClassCombo");
				opt->setProperty(WSNvalue, (classIndex+1));
				opt->setProperty(WSNlabelString, stockMonsterClasses[classIndex].c_str());
			}else{
				sprintf(buf, "class combo failure:%d", monster_definitions[type]._class);
				MessageBox(NULL, buf, "", MB_OK);
			}
			//setSelectedValue((WSCoption*)getChild(indextab, "ClassCombo"),
			//	(monster_definitions[type]._class));
			//radius
			setInteger(getChild(indextab, "RadiusEdit"), monster_definitions[type].radius);
			//height
			setInteger(getChild(indextab, "HeightEdit"), monster_definitions[type].height);
			//hover
			setInteger(getChild(indextab, "HoverEdit"), monster_definitions[type].preferred_hover_height);
			//minledge
			setInteger(getChild(indextab, "MinLedgeEdit"), monster_definitions[type].minimum_ledge_delta);
			//maxledge
			setInteger(getChild(indextab, "MaxLedgeEdit"), monster_definitions[type].maximum_ledge_delta);
			//extvelscale
			setInteger(getChild(indextab, "ExtVelScaleEdit"), monster_definitions[type].external_velocity_scale);
			
		//	sprintf(buf, "carry item:%d", monster_definitions[type].carrying_item_type);
		//	MessageBox(NULL, buf, "", MB_OK);
			//carryitem
			int carryIndex = monster_definitions[type].carrying_item_type;
			if(carryIndex < 0){
				carryIndex = stockItemTypes.size() -1;
			}
			getChild(indextab, "CarryItemBtn")->setProperty(WSNlabelString,
				stockItemTypes[carryIndex].c_str());
			//halfvisualarc
			setInteger(getChild(indextab, "HalfVisualArcEdit"), monster_definitions[type].half_visual_arc);
			//vertvisualarc
			setInteger(getChild(indextab, "VertVisualArcEdit"), monster_definitions[type].half_vertical_visual_arc);
			//interlligence
			WSCoption* opt = (WSCoption*)getChild(indextab, "IntelligenceCombo");
			long intelli = monster_definitions[type].intelligence;
			char* intelligences[10]={"Low", "Average", "High"};
			int intelliIndex = getIndexFromValueArray(valueIntelligences, NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS,
				intelli);
			if(intelliIndex >= 0){
		//		opt->onValueChange(intelliIndex);
				getChild(indextab, "IntelligenceCombo")->setProperty(WSNvalue, 
					intelliIndex+1);//WSNlabelString
				getChild(indextab, "IntelligenceCombo")->setProperty(WSNlabelString,
					intelligences[intelliIndex]);//WSNlabelString
			}else{
			}
			
			//opt->update();
			//setSelectedValue((WSCoption*)getChild(indextab, "IntelligenceCombo"),
			//	monster_definitions[type].intelligence);
			//speed
			int speed = monster_definitions[type].speed;
			setInteger(getChild(indextab, "SpeedEdit"), speed);
			int speedIndex = getIndexFromValueArray(valueSpeed, NUMBER_OF_SPEED_INFORMATIONS,
				speed);
			if(speedIndex >= 0){
				//
				getChild(indextab, "SpeedEdit")->setProperty(WSNlabelString,
					stockSpeeds[speedIndex].c_str());
			}
			//getChild(indextab, "SpeedCombo")->setProperty(WSNvalue, );
			//gravity
			setInteger(getChild(indextab, "GravityEdit"), monster_definitions[type].gravity);
			
			////////////
			//sequences
			setInteger(getChild(indextab, "SeqStationaly"),
				monster_definitions[type].stationary_shape);
			setInteger(getChild(indextab, "SeqMoving"),
				monster_definitions[type].moving_shape);
			setInteger(getChild(indextab, "SeqSoftDying"),
				monster_definitions[type].soft_dying_shape);
			setInteger(getChild(indextab, "SeqSoftDead"),
				monster_definitions[type].soft_dead_shapes);
			setInteger(getChild(indextab, "SeqHardDying"),
				monster_definitions[type].hard_dying_shape);
			setInteger(getChild(indextab, "SeqHardDead"),
				monster_definitions[type].hard_dead_shapes);
			setInteger(getChild(indextab, "SeqHitting"),
				monster_definitions[type].hit_shapes);
			setInteger(getChild(indextab, "SeqTeleportIn"),
				monster_definitions[type].teleport_in_shape);
			setInteger(getChild(indextab, "SeqTeleportOut"),
				monster_definitions[type].teleport_out_shape);
			
			//shapnel damage!
			setInteger(getChild(indextab, "ShapnelRadiusEdit"),
				monster_definitions[type].shrapnel_radius);
			setInteger(getChild(indextab, "ShapnelBaseEdit"),
				monster_definitions[type].shrapnel_damage.base);
			setInteger(getChild(indextab, "ShapnelRndEdit"),
				monster_definitions[type].shrapnel_damage.random);
			setInteger(getChild(indextab, "ShapnelScaleEdit"),
				monster_definitions[type].shrapnel_damage.scale);
			//shrapnel
			int shrapnelDamageTypeIndex = monster_definitions[type].shrapnel_damage.type;
			if(shrapnelDamageTypeIndex < 0 || shrapnelDamageTypeIndex >= stockDamages.size()){
				getChild(indextab, "ShapnelTypeBtn")->setProperty(WSNlabelString,
					"");
			}else{
				getChild(indextab, "ShapnelTypeBtn")->setProperty(WSNlabelString,
					stockDamages[shrapnelDamageTypeIndex].c_str());//WSNlabelString
			}
			//check box
			WSCbool status = False;
			if(monster_definitions[type].shrapnel_damage.flags & _alien_damage){
				status = True;
			}
			((WSCvradio*)getChild(indextab, "ShapnelAlienCheck"))->setStatus(status);
			
			//sounds
			setInteger(getChild(indextab, "SoundPitchEdit"),
				monster_definitions[type].sound_pitch);
			setInteger(getChild(indextab, "RandomSndMaskEdit"),
				monster_definitions[type].random_sound_mask);
			int index = monster_definitions[type].activation_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "ActivationSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].friendly_activation_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "FriendActSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].clear_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "ClearSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].kill_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "KillSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].apology_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "ApologySndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].friendly_fire_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "FriendFireSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].flaming_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "FlamingSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = monster_definitions[type].random_sound;
			if(index < 0 || index == UNONE){index = stockSounds.size() - 1;}
			getChild(indextab, "RandomSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			
			index = monster_definitions[type].impact_effect;
			if(index < 0 || index == UNONE){index = stockEffects.size() - 1;}
			getChild(indextab, "ImpactEffectBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());
			index = monster_definitions[type].melee_impact_effect;
			if(index < 0 || index == UNONE){index = stockEffects.size() - 1;}
			getChild(indextab, "MeleeEffectBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());
			index = monster_definitions[type].contrail_effect;
			if(index < 0 || index == UNONE){index = stockEffects.size() - 1;}
			getChild(indextab, "ContrailEffectBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());

			/////////////////////////////////////////
			//tab index 2(flags)
			//immunities
			WSCcheckGroup* lstImmunities = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListImmunities");
			WSCcheckGroup* lstWeaknesses = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListWeakness");
			int immunities = monster_definitions[type].immunities;
			int weaknesses = monster_definitions[type].weaknesses;
			for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
				WSCvradio* immunity = (WSCvradio*)lstImmunities->getItem(i);
				WSCvradio* weakness = (WSCvradio*)lstWeaknesses->getItem(i);
				if(immunity == NULL || weakness == NULL){
					messageBox("NULL id[%d], immunity[%x], weakness[%x]", i, immunity, weakness);
					exit(1);
				}
				if(immunities & FLAG(i)){
					immunity->setStatus(True);
				}else{
					//lstFlags
					immunity->setStatus(False);
				}
				if(weaknesses & FLAG(i)){
					weakness->setStatus(True);
				}else{
					weakness->setStatus(False);
				}
			}
			
			//enemies & friends
			WSCcheckGroup* lstEnemies = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListEnemies");
			WSCcheckGroup* lstFriends = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListFriends");
			int enemies = monster_definitions[type].enemies;
			int friends = monster_definitions[type].friends;
			for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
				WSCvtoggle* enemy = (WSCvtoggle*)lstEnemies->getItem(i);
				WSCvtoggle* _friend = (WSCvtoggle*)lstFriends->getItem(i);
				if(enemies & FLAG(i)){
					enemy->setStatus(True);
				}else{
					//lstFlags
					enemy->setStatus(False);
				}
				if(friends & FLAG(i)){
					_friend->setStatus(True);
				}else{
					_friend->setStatus(False);
				}
			}
			WSCcheckGroup* lstFlags = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListFlags");
			int nflags = monster_definitions[type].flags;
			for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
				WSCvtoggle* flags = (WSCvtoggle*)lstFlags->getItem(i);
				if(nflags & FLAG(i)){
					flags->setStatus(True);
				}else{
					//lstFlags
					flags->setStatus(False);
				}
			}
			
			///////////////////////////////////////
			// Attacks!
			setInteger(getChild(indextab, "FrequencyEdit"),
				monster_definitions[type].attack_frequency);
			//melee
			index = monster_definitions[type].melee_attack.type;
			if(index < 0 || index == UNONE){index = stockProjectiles.size() - 1;}
			getChild(indextab, "BtnMeleeType")->setProperty(WSNlabelString,
				stockProjectiles[index].c_str());
			setInteger(getChild(indextab, "MeleeRepetitionsEdit"),
				monster_definitions[type].melee_attack.repetitions);
			setInteger(getChild(indextab, "MeleeErrorEdit"),
				monster_definitions[type].melee_attack.error);
			setInteger(getChild(indextab, "MeleeRangeEdit"),
				monster_definitions[type].melee_attack.range);
			setInteger(getChild(indextab, "MeleeSequenceEdit"),
				monster_definitions[type].melee_attack.attack_shape);
			setInteger(getChild(indextab, "MeleedxEdit"),
				monster_definitions[type].melee_attack.dx);
			setInteger(getChild(indextab, "MeleedyEdit"),
				monster_definitions[type].melee_attack.dy);
			setInteger(getChild(indextab, "MeleedzEdit"),
				monster_definitions[type].melee_attack.dz);
			//ranged
			index = monster_definitions[type].ranged_attack.type;
			if(index < 0 || index == UNONE){index = stockProjectiles.size() - 1;}
			getChild(indextab, "BtnRangedType")->setProperty(WSNlabelString,
				stockProjectiles[index].c_str());
			setInteger(getChild(indextab, "RangedRepetitionsEdit"),
				monster_definitions[type].ranged_attack.repetitions);
			setInteger(getChild(indextab, "RangedErrorEdit"),
				monster_definitions[type].ranged_attack.error);
			setInteger(getChild(indextab, "RangedRangeEdit"),
				monster_definitions[type].ranged_attack.range);
			setInteger(getChild(indextab, "RangedSequenceEdit"),
				monster_definitions[type].ranged_attack.attack_shape);
			setInteger(getChild(indextab, "RangeddxEdit"),
				monster_definitions[type].ranged_attack.dx);
			setInteger(getChild(indextab, "RangeddyEdit"),
				monster_definitions[type].ranged_attack.dy);
			setInteger(getChild(indextab, "RangeddzEdit"),
				monster_definitions[type].ranged_attack.dz);
		}
	}else if(windowType == Windows::Effect){
		//form
		WSCform* wnd = (WSCform*)getObject("WSCform", "FrmEffect");
		int type = selectedEffectType;
		if(type >= 0 && type < NUMBER_OF_EFFECT_TYPES){
			int16 collection = effect_definitions[type].collection;
			int16 col = GET_COLLECTION(collection);
			int16 clut = GET_COLLECTION_CLUT(collection);
			//collection(btn)
			getChild(wnd, "BtnEffectCollection")->setProperty(WSNlabelString,
				stockCollections[col].c_str());
			//clut
			setInteger(getChild(wnd, "EffectPalletEdit"),
				clut);
			
			//sequence
			setInteger(getChild(wnd, "EffectSequenceEdit"),
				effect_definitions[type].shape);
			//sound pitch
			setInteger(getChild(wnd, "EffectSoundPitchEdit"),
				effect_definitions[type].sound_pitch);
			//delay
			setInteger(getChild(wnd, "EffectDelayEdit"),
				effect_definitions[type].delay);
			//delay sound(btn)
			int index = effect_definitions[type].delay_sound;
			if(index < 0){index = stockSounds.size() - 1;}
			getChild(wnd, "BtnEffectDelaySound")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			
			//check group
			WSCcheckGroup* flags = (WSCcheckGroup*)getChild(wnd, "EffectFlagsCheckGroup");
			int nflag = effect_definitions[type].flags;
			for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
				WSCvtoggle* toggle = (WSCvtoggle*)flags->getItem(i);
				if(nflag & valueEffectFlags[i]){
					//ON
					toggle->setStatus(True);
				}else{
					//OFF
					toggle->setStatus(False);
				}
			}
		}
	}else if(windowType == Windows::Projectile){
		WSCform* wnd = (WSCform*)getObject("WSCform", "FrmProjectile");
		int type = selectedProjectileType;
		if(type >= 0 && type < NUMBER_OF_PROJECTILE_TYPES){
			int16 collection = projectile_definitions[type].collection;
			int16 col = GET_COLLECTION(collection);
			int16 clut = GET_COLLECTION_CLUT(collection);
			//collection(btn)
			getChild(wnd, "ProjCollectionBtn")->setProperty(WSNlabelString,
				stockCollections[col].c_str());
			//clut
			setInteger(getChild(wnd, "ProjPalletEdit"),
				clut);
			//sequence
			setInteger(getChild(wnd, "ProjSequenceEdit"),
				projectile_definitions[type].shape);
			//detonation effect(btn)
			int index = projectile_definitions[type].detonation_effect;
			if(index < 0){index = stockEffects.size() - 1;}
			getChild(wnd, "ProjDetonationEfBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());
			//detonation media effect(btn)
			index = projectile_definitions[type].media_detonation_effect;
			if(index < 0){index = stockEffects.size() - 1;}
			getChild(wnd, "ProjDetMediaEfBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());
			//contrail effect(btn)
			index = projectile_definitions[type].contrail_effect;
			if(index < 0){index = stockEffects.size() - 1;}
			getChild(wnd, "ProjContrailEfBtn")->setProperty(WSNlabelString,
				stockEffects[index].c_str());
			//Ticks between Contrail
			setInteger(getChild(wnd, "ProjTicksBetContrailEdit"),
				projectile_definitions[type].ticks_between_contrails);
			//max contrail
			setInteger(getChild(wnd, "ProjMaxContrailEdit"),
				projectile_definitions[type].maximum_contrails);
			//media promo
			setInteger(getChild(wnd, "ProjMediaPromoEdit"),
				projectile_definitions[type].media_projectile_promotion);
			//radius
			setInteger(getChild(wnd, "ProjRadiusEdit"),
				projectile_definitions[type].radius);
			//area of effect
			setInteger(getChild(wnd, "ProjAreaOfEfEdit"),
				projectile_definitions[type].area_of_effect);
			
			//damages
			//type(btn)
			index = projectile_definitions[type].damage.type;
			if(index < 0){index = stockDamages.size() - 1;}
			getChild(wnd, "ProjDamageTypeBtn")->setProperty(WSNlabelString,
				stockDamages[index].c_str());
			//base
			setInteger(getChild(wnd, "ProjDamageBaseEdit"),
				projectile_definitions[type].damage.base);
			//random
			setInteger(getChild(wnd, "ProjDamageRandomEdit"),
				projectile_definitions[type].damage.random);
			//scale
			setInteger(getChild(wnd, "ProjDamageScaleEdit"),
				projectile_definitions[type].damage.scale);
			//alian(chk box)
			WSCbool status = False;
			if(projectile_definitions[type].damage.flags & _alien_damage){
				status = True;
			}
			((WSCvradio*)getChild(wnd, "ProjDamageFlags"))->setStatus(status);
			
			//
			WSCcheckGroup* flags = (WSCcheckGroup*)getChild(wnd, "ListProjFlags");
			int nflags = projectile_definitions[type].flags;
			for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
				WSCvtoggle* toggle = (WSCvtoggle*)flags->getItem(i);
				WSCbool status = False;
				if(nflags & valueProjectileFlags[i]){
					status = True;
				}
				toggle->setStatus(status);
			}
			setInteger(getChild(wnd, "ProjSpeedEdit"),
				projectile_definitions[type].speed);
			setInteger(getChild(wnd, "ProjMaxRangeEdit"),
				projectile_definitions[type].maximum_range);
			setInteger(getChild(wnd, "ProjSoundPitchEdit"),
				projectile_definitions[type].sound_pitch);
			//sounds(btn)
			index = projectile_definitions[type].flyby_sound;
			if(index < 0){index = stockSounds.size() - 1;}
			getChild(wnd, "ProjFlyBySoundBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
			index = projectile_definitions[type].rebound_sound;
			if(index < 0){index = stockSounds.size() - 1;}
			getChild(wnd, "ProjReboundSndBtn")->setProperty(WSNlabelString,
				stockSounds[index].c_str());
		}
	}else if(windowType == Windows::Physics){
		WSCform* wnd = (WSCform*)getObject("WSCform", "FrmPhysics");
		int type = selectedPhysicsType;
		if(type >= 0 && type < NUMBER_OF_PHYSICS_MODELS){
			setInteger(getChild(wnd, "PhyMaxForwardEdit"),
				physics_models[type].maximum_forward_velocity);
			setInteger(getChild(wnd, "PhyMaxBackwardEdit"),
				physics_models[type].maximum_backward_velocity);
			setInteger(getChild(wnd, "PhyMaxPerpendEdit"),
				physics_models[type].maximum_perpendicular_velocity);
			setInteger(getChild(wnd, "PhyAccelEdit"),
				physics_models[type].acceleration);
			setInteger(getChild(wnd, "PhyDecelEdit"),
				physics_models[type].deceleration);
			setInteger(getChild(wnd, "PhyAirDecelEdit"),
				physics_models[type].airborne_deceleration);
			setInteger(getChild(wnd, "PhyGravityAccelEdit"),
				physics_models[type].gravitational_acceleration);
			setInteger(getChild(wnd, "PhyClimbAccelEdit"),
				physics_models[type].climbing_acceleration);
			setInteger(getChild(wnd, "PhyTerminalAccelEdit"),
				physics_models[type].terminal_velocity);
			setInteger(getChild(wnd, "PhyExtDecEdit"),
				physics_models[type].external_deceleration);

			setInteger(getChild(wnd, "PhyAngularAccelEdit"),
				physics_models[type].angular_acceleration);
			setInteger(getChild(wnd, "PhyAngularDecelEdit"),
				physics_models[type].angular_deceleration);
			setInteger(getChild(wnd, "PhyMaxAngularVelEdit"),
				physics_models[type].maximum_angular_velocity);
			setInteger(getChild(wnd, "PhyAngularRecenterEdit"),
				physics_models[type].fast_angular_velocity);
			setInteger(getChild(wnd, "PhyFastAngularVelEdit"),
				physics_models[type].fast_angular_maximum);
			setInteger(getChild(wnd, "PhyMaxElevationEdit"),
				physics_models[type].maximum_elevation);
			setInteger(getChild(wnd, "PhyExtAngularDecelEdit"),
				physics_models[type].external_angular_deceleration);
			setInteger(getChild(wnd, "PhyStepDeltaEdit"),
				physics_models[type].step_delta);
			setInteger(getChild(wnd, "PhyStepAmpEdit"),
				physics_models[type].step_amplitude);
			setInteger(getChild(wnd, "PhyRadiusEdit"),
				physics_models[type].radius);

			setInteger(getChild(wnd, "PhyHeightEdit"),
				physics_models[type].height);
			setInteger(getChild(wnd, "PhyDeadHeightEdit"),
				physics_models[type].dead_height);
			setInteger(getChild(wnd, "PhyCameraHeightEdit"),
				physics_models[type].camera_height);
			setInteger(getChild(wnd, "PhySplashHeightEdit"),
				physics_models[type].splash_height);
			setInteger(getChild(wnd, "PhyHalfCamSepEdit"),
				physics_models[type].half_camera_separation);
		}
	}else if(windowType == Windows::Weapon){
		WSCform* wnd = (WSCform*)getObject("WSCform", "FrmWeapon");
		int type = selectedWeaponType;
		if(type >= 0 && type < MAXIMUM_NUMBER_OF_WEAPONS){
			//collection (btn)
			int16 collection = weapon_definitions[type].collection;
			int16 col = GET_COLLECTION(collection);
			int16 clut = GET_COLLECTION_CLUT(collection);
			//collection(btn)
			getChild(wnd, "WCollectionBtn")->setProperty(WSNlabelString,
				stockCollections[col].c_str());
			//clut
			setInteger(getChild(wnd, "WPalletEdit"),
				col);
			setInteger(getChild(wnd, "WIdleSeqEdit"),
				weapon_definitions[type].idle_shape);
			setInteger(getChild(wnd, "WFiringSeqEdit"),
				weapon_definitions[type].firing_shape);
			setInteger(getChild(wnd, "WReloadSeqEdit"),
				weapon_definitions[type].reloading_shape);
			setInteger(getChild(wnd, "WChargingSeqEdit"),
				weapon_definitions[type].charging_shape);
			setInteger(getChild(wnd, "WChargedSeqEdit"),
				weapon_definitions[type].charged_shape);
			//item(btn)
			int index = weapon_definitions[type].item_type;
			if(index < 0 || index == UNONE){index = stockItemTypes.size() - 1;}
			getChild(wnd, "WItemBtn")->setProperty(WSNlabelString,
				stockItemTypes[index].c_str());
			//class(option)
			getChild(wnd, "WClassOption")->setProperty(WSNlabelString,
				stockWeaponClasses[weapon_definitions[type].weapon_class].c_str());

			setInteger(getChild(wnd, "WLightIntensityEdit"),
				weapon_definitions[type].firing_light_intensity);
			setInteger(getChild(wnd, "WIntensityDecayEdit"),
				weapon_definitions[type].firing_intensity_decay_ticks);
			setInteger(getChild(wnd, "WIdleWidthEdit"),
				weapon_definitions[type].idle_width);
			setInteger(getChild(wnd, "WIdleHeightEdit"),
				weapon_definitions[type].idle_height);
			setInteger(getChild(wnd, "WFiringHeightEdit"),
				weapon_definitions[type].kick_height);
			setInteger(getChild(wnd, "WReloadingHeighEdit"),
				weapon_definitions[type].reload_height);
			setInteger(getChild(wnd, "WHorAmpEdit"),
				weapon_definitions[type].horizontal_amplitude);
			setInteger(getChild(wnd, "WUserAmpEdit"),
				weapon_definitions[type].bob_amplitude);
			setInteger(getChild(wnd, "WReadyEdit"),
				weapon_definitions[type].ready_ticks);
			setInteger(getChild(wnd, "WAwaitReloadEdit"),
				weapon_definitions[type].await_reload_ticks);
			setInteger(getChild(wnd, "WLoadingEdit"),
				weapon_definitions[type].loading_ticks);
			setInteger(getChild(wnd, "WLoadedEdit"),
				weapon_definitions[type].finish_loading_ticks);

			//flags
			WSCcheckGroup* flags = (WSCcheckGroup*)getObject("WSCcheckGroup", "WFlagsCheckGroup");
			int nflags = weapon_definitions[type].flags;
			for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
				WSCvtoggle* toggle = (WSCvtoggle*)flags->getItem(i);
				if(nflags & valueWeaponFlags[i]){
					//ON
					toggle->setStatus(True);
				}else{
					//OFF
					toggle->setStatus(False);
				}
			}
			
			///////////////////////
			//triggers
			WSCbase* primary = getChild(wnd, "WPrimaryGroup");
			setupTrigger(0, "", primary);
			WSCbase* secondary = getChild(wnd, "WSecondaryGroup");
			setupTrigger(1, "S", secondary);
		}
	}
	getObject("WSCmainWindow", "MainWindow")->update();
}

//空文字を消します。
std::vector<std::string> killSpaceOfList(std::vector<std::string>& lst)
{
	std::vector<std::string> dest;
	for(int i = 0; i < lst.size(); i ++){
		if(lst[i].compare("") != 0){
			dest.push_back(lst[i]);
		}
	}
	return dest;
}

//カンマでつなぎます
std::string getCommaItemList(std::vector<std::string>& lst)
{
	std::string str;
	if(lst.size() > 0){
		str += lst[0];
	}
	for(int i = 1; i < lst.size(); i ++){
		str += ",";
		str += lst[i];
	}
	return str;
}

void changeForm(int wtype)
{
	bool visible;
	windowType = wtype;
	visible = wtype == Windows::Monster;
	getObject("WSCform", "FrmMonster")->setVisible(visible);
	getObject("WSCvbtn", "BtnMonster")->setProperty(WSNreverseFlag, visible);
	visible = wtype == Windows::Effect;
	getObject("WSCform", "FrmEffect")->setVisible(visible);
	getObject("WSCvbtn", "BtnEffect")->setProperty(WSNreverseFlag, visible);
	visible = wtype == Windows::Projectile;
	getObject("WSCform", "FrmProjectile")->setVisible(visible);
	getObject("WSCvbtn", "BtnProjectile")->setProperty(WSNreverseFlag, visible);
	visible = wtype == Windows::Physics;
	getObject("WSCform", "FrmPhysics")->setVisible(visible);
	getObject("WSCvbtn", "BtnPhysics")->setProperty(WSNreverseFlag, visible);
	visible = wtype == Windows::Weapon;
	getObject("WSCform", "FrmWeapon")->setVisible(visible);
	getObject("WSCvbtn", "BtnWeapon")->setProperty(WSNreverseFlag, visible);
	
	setupDialog();
}

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainInitFunc(WSCbase* object){
  //do something...
	//definitions -> backup
    memcpy(monster_default_definitions, monster_definitions,
        sizeof(struct monster_definition) * NUMBER_OF_MONSTER_TYPES);
    memcpy(effect_default_definitions, effect_definitions,
        sizeof(struct effect_definition) * NUMBER_OF_EFFECT_TYPES);
    memcpy(projectile_default_definitions, projectile_definitions,
        sizeof(struct projectile_definition) * NUMBER_OF_PROJECTILE_TYPES);
    memcpy(physics_default_models, physics_models,
        sizeof(struct physics_constants) * NUMBER_OF_PHYSICS_MODELS);
    memcpy(weapon_default_definitions, weapon_definitions,
        sizeof(struct weapon_definition) * MAXIMUM_NUMBER_OF_WEAPONS);

	//load
	{
		std::vector<std::string> lst = hpl::string::loadFromFile("data/Collections.txt");
		stockCollections = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/MonsterClasses.txt");
		stockMonsterClasses = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/Speeds.txt");
		stockSpeeds = killSpaceOfList(lst);
		stockSpeeds.push_back("*other*");
		lst = hpl::string::loadFromFile("data/DefinedItems.txt");
		stockItemTypes = killSpaceOfList(lst);
		stockItemTypes.push_back("*none*");
		lst = hpl::string::loadFromFile("data/Effects.txt");
		stockEffects = killSpaceOfList(lst);
		stockEffects.push_back("*none*");
		lst = hpl::string::loadFromFile("data/Projectiles.txt");
		stockProjectiles = killSpaceOfList(lst);
		stockProjectiles.push_back("*ball drop*");
		stockProjectiles.push_back("*none*");
		lst = hpl::string::loadFromFile("data/Sounds.txt");
		stockSounds = killSpaceOfList(lst);
		stockSounds.push_back("*none*");
		lst = hpl::string::loadFromFile("data/Damages.txt");
		stockDamages = killSpaceOfList(lst);
		stockDamages.push_back("*none*");
		lst = hpl::string::loadFromFile("data/MonsterActivates.txt");
		stockMonsterActivates = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/MonsterDoorRetryMasks.txt");
		stockMonsterDoorRetryMasks = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/WeaponClasses.txt");
		stockWeaponClasses = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/ShellCasingTypes.txt");
		stockShellCasingTypes = killSpaceOfList(lst);
		stockShellCasingTypes.push_back("*none*");
		lst = hpl::string::loadFromFile("data/PhysicsTypes.txt");
		stockPhysicsTypes = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/MonsterFlags.txt");
		stockMonsterFlags = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/WSProjectileFlags.txt");
		stockProjectileFlags = killSpaceOfList(lst);
		lst = hpl::string::loadFromFile("data/WSWeaponFlags.txt");
		stockWeaponFlags = killSpaceOfList(lst);
	}
	

	//setup window's combo
	//object->getChildInstance("WndMonster")->
	//getChildInstance("Maiinde_012")->getChildInstance("CollectionCombo")->setProperty(WSNmenuItems, itemList.c_str());
	/*long ret = object->getChildInstance("WndSelect")->popup();
	if(ret == WS_DIALOG_OK){
	}else{
	}*/
	//モンスターのクラスに補充
	std::string itemList = getOptionItemListFromVectorString(stockMonsterClasses);
	getChild(getChild(getChild(object, "FrmMonster"), "Maiinde_012"), "ClassCombo")->
		setProperty(WSNmenuItems, itemList.c_str());
	itemList = getOptionItemListFromVectorString(stockShellCasingTypes);
	getObject("WSCoption", "WShellCasingOption")->setProperty(WSNmenuItems,
		itemList.c_str());
	itemList = getOptionItemListFromVectorString(stockSpeeds);
	getObject("WSCoption", "SpeedCombo")->setProperty(WSNmenuItems,
		itemList.c_str());
	
	//モンスターの耐性リストを設定
	// ダメージ名称をカンマでつなげる
	itemList = getCommaItemList(stockDamages);
	getObject("WSCcheckGroup", "ListImmunities")->setProperty(WSNmenuItems,
		itemList.c_str());
	getObject("WSCcheckGroup", "ListWeakness")->setProperty(WSNmenuItems,
		itemList.c_str());
	itemList = getCommaItemList(stockMonsterClasses);
	getObject("WSCcheckGroup", "ListEnemies")->setProperty(WSNmenuItems,
		itemList.c_str());
	getObject("WSCcheckGroup", "ListFriends")->setProperty(WSNmenuItems,
		itemList.c_str());
	itemList = getCommaItemList(stockMonsterFlags);
	getObject("WSCcheckGroup", "ListFlags")->setProperty(WSNmenuItems,
		itemList.c_str());
	//proj flags
	itemList = getCommaItemList(stockProjectileFlags);
	getObject("WSCcheckGroup", "ListProjFlags")->setProperty(WSNmenuItems,
		itemList.c_str());
	//weapon flags
	itemList = getCommaItemList(stockWeaponFlags);
	getObject("WSCcheckGroup", "WFlagsCheckGroup")->setProperty(WSNmenuItems,
		itemList.c_str());

	/////////////////////
	//表示
	//フレームの表示
	WSCwindow* obj = (WSCwindow*)getObject("WSCform", "FrmMonster");
	obj->setVisible(true);
	selectedMonsterType = selectedEffectType = selectedProjectileType = 0;
	selectedPhysicsType = selectedWeaponType = 0;
	//モンスター種類リストで選択変更
	WSClist* lst = (WSClist*)getObject("WSClist", "ListMonsterTypes");
	lst->setSelectPos(selectedMonsterType);
	windowType = Windows::Monster;

	setDefinitionsToDefault();
	//更新
	setupDialog();
}
static WSCfunctionRegister  op("MainInitFunc",(void*)MainInitFunc);
