#include "PhysicsEditorOneWX.h"
#include "MainFrame.h"

//実体を持たせます
IMPLEMENT_APP(PhysicsEditorOneWX)

static char* DEFAULT_PHYSICS_FILE_PATH = "Physics.phyA";


bool PhysicsEditorOneWX::OnInit()
{
	this->init();

	this->frame = new MainFrame();
	frame->Create(NULL, wxID_ANY);
	//各種設定
	this->setNewAndChanged(true, false);

	//デフォルトデータとしてファイルから読み込んでおく
	this->loadDefaultPhysicsFile();

	frame->Show(true);

	return TRUE;
}

/**
	wxWidgetsに依存しない初期設定
*/
void PhysicsEditorOneWX::init()
{
	//load names from text

	//general
	//	collections
	hpl::aleph::loadInformation("data/Collections.txt", NUMBER_OF_COLLECTIONS,
		collectionInfo);
	//	sounds
	hpl::aleph::loadInformation("data/Sounds.txt", NUMBER_OF_SOUND_DEFINITIONS,
		soundInfo);
	//damages
	hpl::aleph::loadInformation("data/Damages.txt", NUMBER_OF_DAMAGE_TYPES,
		damageInfo);
	//items
	hpl::aleph::loadInformation("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS,
		itemInfo);
	//speeds (preset)
	hpl::aleph::loadInformation("data/Speeds.txt", NUMBER_OF_SPEED_INFORMATIONS,
		speedBind);
    int speedBinds[]={
        _speed_slow, _speed_medium, _speed_almost_fast, _speed_fast,
        _speed_superfast1, _speed_superfast2, _speed_superfast3, 
        _speed_superfast4, _speed_superfast5, 
        _speed_blinding, _speed_insane
    };
	hpl::aleph::setInformationBind(NUMBER_OF_SPEED_INFORMATIONS,
		speedBind, speedBinds);

	//monster
	//	types
	hpl::aleph::loadInformation("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES,
		monsterInfo);
	//	activates
	hpl::aleph::loadInformation("data/MonsterActivates.txt", NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS,
		monsterActivateInfo);
	//	classes
	hpl::aleph::loadInformation("data/MonsterClasses.txt", NUMBER_OF_CLASS_INFORMATIONS,
		monsterClassBind);
    int monsterClassBinds[]={
        _class_player, _class_human_civilian, _class_madd, _class_possessed_hummer,
        _class_defender,
        _class_fighter, _class_trooper, _class_hunter, _class_enforcer, _class_juggernaut,
        _class_compiler, _class_cyborg, _class_assimilated_civilian,
        _class_hummer, _class_tick, _class_yeti
    };
	hpl::aleph::setInformationBind(NUMBER_OF_CLASS_INFORMATIONS,
		monsterClassBind, monsterClassBinds);
	//	intelligence
	hpl::aleph::loadInformation("data/MonsterIntelligences.txt", NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS,
		monsterIntelligenceBind);
    int monsterIntelligenceBinds[]={
        _intelligence_low, _intelligence_average, _intelligence_high
    };
	hpl::aleph::setInformationBind(NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS,
		monsterIntelligenceBind, monsterIntelligenceBinds);
	//	door retly
	hpl::aleph::loadInformation("data/MonsterDoorRetryMasks.txt", NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS,
		monsterDoorRetryMaskBind);
    int monsterDoorRetryMaskBinds[]={
        _slow_door_retry_mask, _normal_door_retry_mask,
        _fast_door_retry_mask, _vidmaster_door_retry_mask
    };
	hpl::aleph::setInformationBind(NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS,
		monsterDoorRetryMaskBind, monsterClassBinds);
	//	flags
    int monsterFlagsBinds[]={
		//0
        _monster_is_omniscent,
		_monster_flys,
        _monster_is_alien,
		_monster_major,
		_monster_minor,

		//5
		_monster_cannot_be_dropped,
		_monster_floats,
		_monster_cannot_attack,
		_monster_uses_sniper_ledges,
		_monster_is_invisible,

		//10
		_monster_is_subtly_invisible,
		_monster_is_kamakazi,
		_monster_is_berserker,
		_monster_is_enlarged,
		_monster_has_delayed_hard_death,
		
		//15
		_monster_fires_symmetrically,
		_monster_has_nuclear_hard_death,
		_monster_cant_fire_backwards,
		_monster_can_die_in_flames,
		_monster_waits_with_clear_shot,

		//20
		_monster_is_tiny,
		_monster_attacks_immediately,
		_monster_is_not_afraid_of_water,
		_monster_is_not_afraid_of_sewage,
		_monster_is_not_afraid_of_lava,

		//25
		_monster_is_not_afraid_of_goo,
		_monster_can_teleport_under_media,
		_monster_chooses_weapons_randomly
    };
	hpl::aleph::setInformationBind(NUMBER_OF_MONSTER_FLAG_INFORMATIONS,
		monsterFlagsBind, monsterFlagsBinds);
	hpl::aleph::loadInformation("data/MonsterFlags.txt", NUMBER_OF_MONSTER_FLAG_INFORMATIONS,
		monsterFlagsBind);

	////////////////
	//projectiles
	//	types
	hpl::aleph::loadInformation("data/Projectiles.txt", NUMBER_OF_PROJECTILE_TYPES,
		projectileInfo);
	//	flags
	int projectileFlagsBinds[] = {
		//0
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

		//20
		_affected_by_half_gravity,
		_penetrates_media_boundary
	};
	hpl::aleph::setInformationBind(NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS,
		projectileFlagsBind, projectileFlagsBinds);

	/////////////////////////
	//effects
	//	types
	hpl::aleph::loadInformation("data/Effects.txt", NUMBER_OF_EFFECT_TYPES,
		effectInfo);
	//	flags
	int effectFlagsBinds[] = {
		_end_when_animation_loops,
		_end_when_transfer_animation_loops,
		_sound_only,
		_make_twin_visible,
		_media_effect
	};
	hpl::aleph::setInformationBind(NUMBER_OF_EFFECT_FLAG_INFORMATIONS,
		effectFlagsBind, effectFlagsBinds);

	////////////////////
	//physics
	//	types
	hpl::aleph::loadInformation("data/PhysicsTypes.txt", NUMBER_OF_EFFECT_TYPES,
		effectInfo);

	/////////////////////
	//weapons
	//	types
	hpl::aleph::loadInformation("data/Weapons.txt", MAXIMUM_NUMBER_OF_WEAPONS,
		weaponInfo);
	//	classes
	hpl::aleph::loadInformation("data/WeaponClasses.txt", NUMBER_OF_WEAPON_CLASS_INFORMATIONS,
		weaponClassInfo);
	//	flags
	int weaponFlagsBinds[] = {
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
	hpl::aleph::setInformationBind(NUMBER_OF_WEAPON_FLAG_INFORMATIONS,
		weaponFlagsBind, weaponFlagsBinds);
	//	shell casing
	hpl::aleph::loadInformation("data/ShellCasingTypes.txt", NUMBER_OF_SHELL_CASING_TYPES,
		weaponShellCasingInfo);

	this->editingMonsterIndex = 0;
	this->editingEffectIndex = 0;
	this->editingProjectileIndex = 0;
	this->editingPhysicsIndex = 0;
	this->editingWeaponIndex = 0;
}

/**
	更新があったかどうか
*/
void PhysicsEditorOneWX::setNewAndChanged(bool new_, bool changed)
{
	//前の状態
	bool prevChanged = this->isChanged();

	//状態更新
	this->isChanged_ = changed;
	this->isNew_ = new_;

	if(changed){
		//変更していない状態から変更状態へ移った
		if(this->isNew()){
			//タイトルバーの文字列を TITLE + " *" にする
			frame->SetTitle(wx::string::getString("%s *", TITLE));
		}else{
			//タイトルバーの文字列を TITLE + " " + saveFilePath + " *" にする
			frame->SetTitle(wx::string::getString("%s %s *", TITLE, this->getSaveFilePath().c_str()));
		}
	}else if(!changed){
		//変更状態から保存状態、新規状態に移った
		if(this->isNew()){
			//タイトルバーの文字列を TITLE にする
			frame->SetTitle(wx::string::getString("%s", TITLE));
		}else{
			//タイトルバーの文字列を TITLE + " " + saveFilePath にする
			frame->SetTitle(wx::string::getString("%s %s", TITLE, this->getSaveFilePath().c_str()));
		}
	}
}
bool PhysicsEditorOneWX::isChanged()
{
	return this->isChanged_;
}
/**
	新規データか
*/
bool PhysicsEditorOneWX::isNew()
{
	return this->isNew_;
}

/**
	デフォルト設定の取り出し
*/
PhysicsDefaultValues* PhysicsEditorOneWX::getDefaultValues()
{
	return &this->defaultValues;
}

/**
	ライブラリに依存しない物理ファイル読み込み処理
*/
static void independentLoadPhysicsFile(const char* filePath)
{
	//物理ファイル名設定
	FileSpecifier phy = FileSpecifier(filePath);
	//対象に設定
	set_physics_file(phy);
    //読み込み
	import_definition_structures();
}
/**
	PhysicsFileを読み込みます
*/
void PhysicsEditorOneWX::loadPhysicsFile(const char* filePath)
{
	independentLoadPhysicsFile(filePath);
	//読み込みファイル名設定
	this->setSaveFilePath(filePath);
	//状態設定
	this->setNewAndChanged(false, false);

}
void PhysicsEditorOneWX::loadDefaultPhysicsFile()
{
	independentLoadPhysicsFile(DEFAULT_PHYSICS_FILE_PATH);
	this->setNewAndChanged(true, false);
}

/**
	読み込んだあるいは保存先のファイルパスを設定
	存在しない場合にこれを呼ぶというのは処理がおかしいことになる。
	それのチェックも兼ねる
*/
void PhysicsEditorOneWX::setSaveFilePath(const char* filePath)
{
	this->saveFilePath = std::string(filePath);
}
std::string PhysicsEditorOneWX::getSaveFilePath()
{
	//まだ読み込んでいないのに呼ばれたら処理がおかしい
	wxASSERT(!this->isNew());
	return this->saveFilePath;
}
/**
	Save and/or create PhysicsFile
*/
void PhysicsEditorOneWX::savePhysicsFile(const char* filePath)
{
	wxASSERT(strcmp(filePath, DEFAULT_PHYSICS_FILE_PATH) != 0);
	export_definition_structures(filePath);

	//更新・新規設定
	this->setNewAndChanged(false, false);
}

/**
	現在編集中のモンスターインデックスを取得
*/
int PhysicsEditorOneWX::getEditingMonsterIndex()
{
	return editingMonsterIndex;
}
int PhysicsEditorOneWX::getEditingEffectIndex()
{
	return editingEffectIndex;
}
int PhysicsEditorOneWX::getEditingProjectileIndex()
{
	return editingProjectileIndex;
}
int PhysicsEditorOneWX::getEditingPhysicsIndex()
{
	return editingPhysicsIndex;
}
int PhysicsEditorOneWX::getEditingWeaponIndex()
{
	return editingWeaponIndex;
}
void PhysicsEditorOneWX::setEditingMonsterIndex(int index)
{
	editingMonsterIndex = index;
}
void PhysicsEditorOneWX::setEditingEffectIndex(int index)
{
	editingEffectIndex = index;
}
void PhysicsEditorOneWX::setEditingProjectileIndex(int index)
{
	editingProjectileIndex = index;
}
void PhysicsEditorOneWX::setEditingPhysicsIndex(int index)
{
	editingPhysicsIndex = index;
}
void PhysicsEditorOneWX::setEditingWeaponIndex(int index)
{
	editingWeaponIndex = index;
}
