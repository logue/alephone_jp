#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCbaseList.h>
#include <WSCwindow.h>
#include <WSCindexForm.h>
#include <WSCvifield.h>
#include <WSCmessageDialog.h>

#include "General.h"

int windowType = Windows::Monster;
int selectedMonsterType;
int selectedEffectType;
int selectedProjectileType;
int selectedPhysicsType;
int selectedWeaponType;

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


int valueMonsterClasses[NUMBER_OF_CLASS_INFORMATIONS]={
    _class_player, _class_human_civilian, _class_madd, _class_possessed_hummer,
    _class_defender,
    _class_fighter, _class_trooper, _class_hunter, _class_enforcer, _class_juggernaut,
    _class_compiler, _class_cyborg, _class_assimilated_civilian,
    _class_hummer, _class_tick, _class_yeti
};
int valueSpeed[NUMBER_OF_SPEED_INFORMATIONS]={
    _speed_slow, _speed_medium, _speed_almost_fast, _speed_fast,
    _speed_superfast1, _speed_superfast2, _speed_superfast3, 
    _speed_superfast4, _speed_superfast5, 
    _speed_blinding, _speed_insane
};
int valueIntelligences[NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS]={
    _intelligence_low, _intelligence_average, _intelligence_high
};
int valueMonsterDoorRetryMask[NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS]={
    _slow_door_retry_mask, _normal_door_retry_mask,
    _fast_door_retry_mask, _vidmaster_door_retry_mask
};
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
	return obj;
}

void setInteger(WSCbase* obj, int num)
{
	//アプリケーションに1つあらかじめ用意されている
	//メッセージダイアログのインスタンスを取得する。
	WSCmessageDialog* msg = WSGIappMessageDialog(); //(G)
	msg->setProperty(WSNwidth,500);									//(H)
	msg->setProperty(WSNheight,120);								//(I)
	msg->setProperty(WSNdefaultPosition,True);			//(J)

	if(obj == NULL){
		msg->setProperty(WSNlabelString,WSCstring("NULL OBJECT! @ setInteger"));
		msg->popup();
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

void setupDialog(WSCbase* object)
{
	if(windowType == Windows::Monster){
		//window
		WSCwindow* wnd = (WSCwindow*)getObject("WSCwindow", "WndMonster");
		int type = selectedMonsterType;
		if(type >= 0 && type < NUMBER_OF_MONSTER_TYPES){
			//設定
			int16 collection = monster_definitions[type].collection;
			int16 col = GET_COLLECTION(collection);
			int16 clut = GET_COLLECTION_CLUT(collection);
			
			//index
			WSCindexForm* indextab = (WSCindexForm*)wnd->getChildInstance("Maiinde_012");
			//clut
			WSCvifield* clutField = (WSCvifield*)indextab->getChildInstance("PalletEdit");
			clutField->setProperty(WSNlabelString, (long)clut);
			//collection
			indextab->getChildInstance("CollectionBtn")->setProperty(WSNlabelString,
				stockCollections[col].c_str());
			
			//vitality
			char buf[256];
			setInteger(indextab->getChildInstance("VitalityEdit"), monster_definitions[type].vitality);
			//class
			int classIndex = getIndexFromValueArray(valueMonsterClasses, NUMBER_OF_CLASS_INFORMATIONS,
				monster_definitions[type]._class);
			if(classIndex > 0){
				WSCbase* opt = indextab->getChildInstance("ClassCombo");
				opt->setProperty(WSNvalue, (classIndex));
				opt->setProperty(WSNlabelString, stockMonsterClasses[classIndex].c_str());
			}else{
				sprintf(buf, "class combo failure:%d", monster_definitions[type]._class);
				MessageBox(NULL, buf, "", MB_OK);
			}
			//setSelectedValue((WSCoption*)indextab->getChildInstance("ClassCombo"),
			//	(monster_definitions[type]._class));
			//radius
			setInteger(indextab->getChildInstance("RadiusEdit"), monster_definitions[type].radius);
			//height
			setInteger(indextab->getChildInstance("HeightEdit"), monster_definitions[type].height);
			//hover
			setInteger(indextab->getChildInstance("HoverEdit"), monster_definitions[type].preferred_hover_height);
			//minledge
			setInteger(indextab->getChildInstance("MinLedgeEdit"), monster_definitions[type].minimum_ledge_delta);
			//maxledge
			setInteger(indextab->getChildInstance("MaxLedgeEdit"), monster_definitions[type].maximum_ledge_delta);
			//extvelscale
			setInteger(indextab->getChildInstance("ExtVelScaleEdit"), monster_definitions[type].external_velocity_scale);
			
		//	sprintf(buf, "carry item:%d", monster_definitions[type].carrying_item_type);
		//	MessageBox(NULL, buf, "", MB_OK);
			//carryitem
			int carryIndex = monster_definitions[type].carrying_item_type;
			if(carryIndex < 0){
				carryIndex = stockItemTypes.size() -1;
			}
			indextab->getChildInstance("CarryItemBtn")->setProperty(WSNlabelString,
				stockItemTypes[carryIndex].c_str());
			//halfvisualarc
			setInteger(indextab->getChildInstance("HalfVisualArc"), monster_definitions[type].half_visual_arc);
			//vertvisualarc
			setInteger(indextab->getChildInstance("VertVisualArc"), monster_definitions[type].half_vertical_visual_arc);
			//interlligence
			WSCoption* opt = (WSCoption*)indextab->getChildInstance("IntelligenceCombo");
			long intelli = monster_definitions[type].intelligence;
	//		opt->onValueChange(num);
	//		opt->setProperty(WSNvalue, num);
			char* intelligences[10]={"Low", "Average", "High"};
			int intelliIndex = getIndexFromValueArray(valueIntelligences, NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS,
				intelli);
			if(intelliIndex > 0){
				indextab->getChildInstance("IntelligenceCombo")->setProperty(WSNvalue, intelliIndex);//WSNlabelString
				indextab->getChildInstance("IntelligenceCombo")->setProperty(WSNlabelString,
					intelligences[intelliIndex]);//WSNlabelString
			}else{
			}
			
			//opt->update();
			//setSelectedValue((WSCoption*)indextab->getChildInstance("IntelligenceCombo"),
			//	monster_definitions[type].intelligence);
			//speed
			setInteger(indextab->getChildInstance("SpeedEdit"), monster_definitions[type].half_vertical_visual_arc);
			//indextab->getChildInstance("SpeedCombo")->setProperty(WSNvalue, );
			//gravity
			setInteger(indextab->getChildInstance("GravityEdit"), monster_definitions[type].gravity);
			
			////////////
			//sequences
			setInteger(indextab->getChildInstance("SeqStationaly"),
				monster_definitions[type].stationary_shape);
			setInteger(indextab->getChildInstance("SeqMoving"),
				monster_definitions[type].moving_shape);
			setInteger(indextab->getChildInstance("SeqSoftDying"),
				monster_definitions[type].soft_dying_shape);
			setInteger(indextab->getChildInstance("SeqSoftDead"),
				monster_definitions[type].soft_dead_shapes);
			setInteger(indextab->getChildInstance("SeqHardDying"),
				monster_definitions[type].hard_dying_shape);
			setInteger(indextab->getChildInstance("SeqHardDead"),
				monster_definitions[type].hard_dead_shapes);
			setInteger(indextab->getChildInstance("SeqHitting"),
				monster_definitions[type].hit_shapes);
			setInteger(indextab->getChildInstance("SeqTeleportIn"),
				monster_definitions[type].teleport_in_shape);
			setInteger(indextab->getChildInstance("SeqTeleportOut"),
				monster_definitions[type].teleport_out_shape);
		}
	}
	object->update();
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
	stockCollections = hpl::string::loadFromFile("data/Collections.txt");
	stockMonsterClasses = hpl::string::loadFromFile("data/MonsterClasses.txt");
	stockSpeeds = hpl::string::loadFromFile("data/Speeds.txt");
	stockSpeeds.push_back("*other*");
	stockItemTypes = hpl::string::loadFromFile("data/DefinedItems.txt");
	stockItemTypes.push_back("*none*");
	stockEffects = hpl::string::loadFromFile("data/Effects.txt");
	stockEffects.push_back("*none*");
	stockProjectiles = hpl::string::loadFromFile("data/Projectiles.txt");
	stockSounds = hpl::string::loadFromFile("data/Sounds.txt");
	stockSounds.push_back("*none*");
	stockDamages = hpl::string::loadFromFile("data/Damages.txt");
	stockMonsterActivates = hpl::string::loadFromFile("data/MonsterActivates.txt");
	stockMonsterDoorRetryMasks = hpl::string::loadFromFile("data/MonsterDoorRetryMasks.txt");
	stockWeaponClasses = hpl::string::loadFromFile("data/WeaponClasses.txt");
	stockShellCasingTypes = hpl::string::loadFromFile("data/ShellCasingTypes.txt");
	stockPhysicsTypes = hpl::string::loadFromFile("data/PhysicsTypes.txt");
	

	//setup window's combo
	//object->getChildInstance("WndMonster")->
	//getChildInstance("Maiinde_012")->getChildInstance("CollectionCombo")->setProperty(WSNmenuItems, itemList.c_str());
	/*long ret = object->getChildInstance("WndSelect")->popup();
	if(ret == WS_DIALOG_OK){
	}else{
	}*/
	std::string itemList = getOptionItemListFromVectorString(stockMonsterClasses);
	object->getChildInstance("WndMonster")->
		getChildInstance("Maiinde_012")->getChildInstance("ClassCombo")->
		setProperty(WSNmenuItems, itemList.c_str());
	
	//子ウインドウの表示
	char* class_name = "WSCwindow"; //ラベルクラス
	char* obj_name   = "WndMonster";     //newvlab_001 という名称
	WSCwindow* obj = (WSCwindow*)WSGIappObjectList()->getInstance(class_name,obj_name);
	obj->setVisible(true);
	selectedMonsterType = selectedEffectType = selectedProjectileType = 0;
	selectedPhysicsType = selectedWeaponType = 0;
	windowType = Windows::Monster;
	
	setDefinitionsToDefault();
	//更新
	setupDialog(object);
}
static WSCfunctionRegister  op("MainInitFunc",(void*)MainInitFunc);
