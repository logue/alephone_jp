#include "PhysicsEditorOneWX.h"
#include "MainFrame.h"

//���̂��������܂�
IMPLEMENT_APP(PhysicsEditorOneWX)

static char* DEFAULT_PHYSICS_FILE_PATH = "Physics.phyA";


bool PhysicsEditorOneWX::OnInit()
{
	this->init();

	this->frame = new MainFrame();
	frame->Create(NULL, wxID_ANY);
	//�e��ݒ�
	this->setNewAndChanged(true, false);

	//�f�t�H���g�f�[�^�Ƃ��ăt�@�C������ǂݍ���ł���
	this->loadDefaultPhysicsFile();

	frame->Show(true);

	return TRUE;
}

/**
	wxWidgets�Ɉˑ����Ȃ������ݒ�
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
	�X�V�����������ǂ���
*/
void PhysicsEditorOneWX::setNewAndChanged(bool new_, bool changed)
{
	//�O�̏��
	bool prevChanged = this->isChanged();

	//��ԍX�V
	this->isChanged_ = changed;
	this->isNew_ = new_;

	if(changed){
		//�ύX���Ă��Ȃ���Ԃ���ύX��Ԃֈڂ���
		if(this->isNew()){
			//�^�C�g���o�[�̕������ TITLE + " *" �ɂ���
			frame->SetTitle(wx::string::getString("%s *", TITLE));
		}else{
			//�^�C�g���o�[�̕������ TITLE + " " + saveFilePath + " *" �ɂ���
			frame->SetTitle(wx::string::getString("%s %s *", TITLE, this->getSaveFilePath().c_str()));
		}
	}else if(!changed){
		//�ύX��Ԃ���ۑ���ԁA�V�K��ԂɈڂ���
		if(this->isNew()){
			//�^�C�g���o�[�̕������ TITLE �ɂ���
			frame->SetTitle(wx::string::getString("%s", TITLE));
		}else{
			//�^�C�g���o�[�̕������ TITLE + " " + saveFilePath �ɂ���
			frame->SetTitle(wx::string::getString("%s %s", TITLE, this->getSaveFilePath().c_str()));
		}
	}
}
bool PhysicsEditorOneWX::isChanged()
{
	return this->isChanged_;
}
/**
	�V�K�f�[�^��
*/
bool PhysicsEditorOneWX::isNew()
{
	return this->isNew_;
}

/**
	�f�t�H���g�ݒ�̎��o��
*/
PhysicsDefaultValues* PhysicsEditorOneWX::getDefaultValues()
{
	return &this->defaultValues;
}

/**
	���C�u�����Ɉˑ����Ȃ������t�@�C���ǂݍ��ݏ���
*/
static void independentLoadPhysicsFile(const char* filePath)
{
	//�����t�@�C�����ݒ�
	FileSpecifier phy = FileSpecifier(filePath);
	//�Ώۂɐݒ�
	set_physics_file(phy);
    //�ǂݍ���
	import_definition_structures();
}
/**
	PhysicsFile��ǂݍ��݂܂�
*/
void PhysicsEditorOneWX::loadPhysicsFile(const char* filePath)
{
	independentLoadPhysicsFile(filePath);
	//�ǂݍ��݃t�@�C�����ݒ�
	this->setSaveFilePath(filePath);
	//��Ԑݒ�
	this->setNewAndChanged(false, false);

}
void PhysicsEditorOneWX::loadDefaultPhysicsFile()
{
	independentLoadPhysicsFile(DEFAULT_PHYSICS_FILE_PATH);
	this->setNewAndChanged(true, false);
}

/**
	�ǂݍ��񂾂��邢�͕ۑ���̃t�@�C���p�X��ݒ�
	���݂��Ȃ��ꍇ�ɂ�����ĂԂƂ����̂͏����������������ƂɂȂ�B
	����̃`�F�b�N�����˂�
*/
void PhysicsEditorOneWX::setSaveFilePath(const char* filePath)
{
	this->saveFilePath = std::string(filePath);
}
std::string PhysicsEditorOneWX::getSaveFilePath()
{
	//�܂��ǂݍ���ł��Ȃ��̂ɌĂ΂ꂽ�珈������������
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

	//�X�V�E�V�K�ݒ�
	this->setNewAndChanged(false, false);
}

/**
	���ݕҏW���̃����X�^�[�C���f�b�N�X���擾
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
