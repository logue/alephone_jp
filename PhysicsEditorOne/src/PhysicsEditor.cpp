// PhysicsEditor.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "PhysicsEditorDlg.h"
#include "monster_definitions.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhysicsEditorApp

BEGIN_MESSAGE_MAP(CPhysicsEditorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPhysicsEditorApp �R���X�g���N�V����

void splitString(CString src, const char* sep, CStringArray &array){
    int pos;
    
    while(1){
        pos = src.Find(CString(sep));
        if(pos == -1){
            array.Add(src);
            break;
        }else if(pos == 0){
            //continue;
        }else{
            array.Add(src.Left(pos));
        }
        src = src.Mid(pos + (int)strlen(sep));
    }
}

CPhysicsEditorApp::CPhysicsEditorApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
    //�����X�^�[�f�t�H���g�ݒ���R�s�[
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

    //error messages
    //loadInformations("data/ErrorMessages.txt", NUMBER_OF_ERROR_MESSAGE_INFORMATIONS,
    //    errorMessageInformations);

    //Information
    //�R���N�V����
    this->loadInformations("data/Collections.txt", NUMBER_OF_COLLECTIONS, this->collectionInformations);

    //�����X�^�[�^�C�v
    this->loadInformations("data/MonsterTypes.txt", NUMBER_OF_MONSTER_TYPES, this->monsterInformations);

    //�A�C�e��
    this->loadInformations("data/DefinedItems.txt", NUMBER_OF_DEFINED_ITEMS, this->definedItemInformations);

    //����
    this->loadInformations("data/Weapons.txt", MAXIMUM_NUMBER_OF_WEAPONS, this->weaponInformations);

    //�G�t�F�N�g
    this->loadInformations("data/Effects.txt", NUMBER_OF_EFFECT_TYPES, this->effectInformations);

    //�v���W�F�N�e�B��
    this->loadInformations("data/Projectiles.txt", NUMBER_OF_PROJECTILE_TYPES, this->projectileInformations);

    //�T�E���h
    this->loadInformations("data/Sounds.txt", NUMBER_OF_SOUND_DEFINITIONS, this->soundInformations);
    
    //�_���[�W
    this->loadInformations("data/Damages.txt", NUMBER_OF_DAMAGE_TYPES, this->damageInformations);

    int monsterClassBinds[]={
        _class_player, _class_human_civilian, _class_madd, _class_possessed_hummer,
        _class_defender,
        _class_fighter, _class_trooper, _class_hunter, _class_enforcer, _class_juggernaut,
        _class_compiler, _class_cyborg, _class_assimilated_civilian,
        _class_hummer, _class_tick, _class_yeti
    };
    loadBindInformations("data/MonsterClasses.txt", NUMBER_OF_CLASS_INFORMATIONS,
        monsterClassInformations, monsterClassBinds);

    //�N������
    loadInformations("data/MonsterActivates.txt", NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS,
        monsterActivateInformations);

    //���x
    int speedBinds[]={
        _speed_slow, _speed_medium, _speed_almost_fast, _speed_fast,
        _speed_superfast1, _speed_superfast2, _speed_superfast3, 
        _speed_superfast4, _speed_superfast5, 
        _speed_blinding, _speed_insane
    };
    loadBindInformations("data/Speeds.txt", NUMBER_OF_SPEED_INFORMATIONS,
        speeds, speedBinds);

    //�h�A�J�}�X�N
    int monsterDoorRetryMaskBinds[]={
        _slow_door_retry_mask, _normal_door_retry_mask,
        _fast_door_retry_mask, _vidmaster_door_retry_mask
    };
    loadBindInformations("data/MonsterDoorRetryMasks.txt", NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS,
        monsterDoorRetryMasks, monsterDoorRetryMaskBinds);

    //�m�\
    int monsterIntelligenceBinds[]={
        _intelligence_low, _intelligence_average, _intelligence_high
    };
    loadBindInformations("data/MonsterIntelligences.txt", NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS,
        monsterIntelligences, monsterIntelligenceBinds);

    //�����X�^�[�t���O
    monsterFlags[0].bindId  = _monster_is_omniscent;
    monsterFlags[1].bindId  = _monster_flys;
    monsterFlags[2].bindId  = _monster_is_alien;
    monsterFlags[3].bindId  = _monster_major;
    monsterFlags[4].bindId  = _monster_minor;
    monsterFlags[5].bindId  = _monster_cannot_be_dropped;
    monsterFlags[6].bindId  = _monster_floats;
    monsterFlags[7].bindId  = _monster_cannot_attack;
    monsterFlags[8].bindId  = _monster_uses_sniper_ledges;
    monsterFlags[9].bindId  = _monster_is_invisible;
    monsterFlags[10].bindId  = _monster_is_subtly_invisible;
    monsterFlags[11].bindId  = _monster_is_kamakazi;
    monsterFlags[12].bindId  = _monster_is_berserker;
    monsterFlags[13].bindId  = _monster_is_enlarged;
    monsterFlags[14].bindId  = _monster_has_delayed_hard_death;
    monsterFlags[15].bindId  = _monster_fires_symmetrically;
    monsterFlags[16].bindId  = _monster_has_nuclear_hard_death;
    monsterFlags[17].bindId  = _monster_cant_fire_backwards;
    monsterFlags[18].bindId  = _monster_can_die_in_flames;
    monsterFlags[19].bindId  = _monster_waits_with_clear_shot;
    monsterFlags[20].bindId  = _monster_is_tiny;
    monsterFlags[21].bindId  = _monster_attacks_immediately;
    monsterFlags[22].bindId  = _monster_is_not_afraid_of_water;
    monsterFlags[23].bindId  = _monster_is_not_afraid_of_sewage;
    monsterFlags[24].bindId  = _monster_is_not_afraid_of_lava;
    monsterFlags[25].bindId  = _monster_is_not_afraid_of_goo;
    monsterFlags[26].bindId  = _monster_can_teleport_under_media;
    monsterFlags[27].bindId  = _monster_chooses_weapons_randomly;

    effectFlagInformations[0].bindId = _end_when_animation_loops;
    effectFlagInformations[1].bindId = _end_when_transfer_animation_loops;
    effectFlagInformations[2].bindId = _sound_only;
    effectFlagInformations[3].bindId = _make_twin_visible;
    effectFlagInformations[4].bindId = _media_effect;

    //����t���O
    weaponFlagInformations[0].bindId = _weapon_is_automatic;
    weaponFlagInformations[1].bindId = _weapon_disappears_after_use;
    weaponFlagInformations[2].bindId = _weapon_plays_instant_shell_casing_sound;
    weaponFlagInformations[3].bindId = _weapon_overloads;
    weaponFlagInformations[4].bindId = _weapon_has_random_ammo_on_pickup;
    weaponFlagInformations[5].bindId = _powerup_is_temporary;
    weaponFlagInformations[6].bindId = _weapon_reloads_in_one_hand;
    weaponFlagInformations[7].bindId = _weapon_fires_out_of_phase;
    weaponFlagInformations[8].bindId = _weapon_fires_under_media;
    weaponFlagInformations[9].bindId = _weapon_triggers_share_ammo;
    weaponFlagInformations[10].bindId = _weapon_secondary_has_angular_flipping;
    
    //����N���X
    loadInformations("data/WeaponClasses.txt", NUMBER_OF_WEAPON_CLASS_INFORMATIONS,
        weaponClassInformations);

    //��䰃^�C�v
    loadInformations("data/ShellCasingTypes.txt", NUMBER_OF_SHELL_CASING_TYPES,
        weaponShellCasingInformations);

    //�����^�C�v
    loadInformations("data/PhysicsTypes.txt", NUMBER_OF_PHYSICS_MODELS,
        physicsInformations);

    //projectile flags
    projectileFlagInformations[0].bindId = _guided;
    projectileFlagInformations[1].bindId = _stop_when_animation_loops;
    projectileFlagInformations[2].bindId = _persistent;
    projectileFlagInformations[3].bindId = _alien_projectile;
    projectileFlagInformations[4].bindId = _affected_by_gravity;
    projectileFlagInformations[5].bindId = _no_horizontal_error;
    projectileFlagInformations[6].bindId = _no_vertical_error;
    projectileFlagInformations[7].bindId = _can_toggle_control_panels;
    projectileFlagInformations[8].bindId = _positive_vertical_error;
    projectileFlagInformations[9].bindId = _melee_projectile;
    projectileFlagInformations[10].bindId = _persistent_and_virulent;
    projectileFlagInformations[11].bindId = _usually_pass_transparent_side;
    projectileFlagInformations[12].bindId = _sometimes_pass_transparent_side;
    projectileFlagInformations[13].bindId = _doubly_affected_by_gravity;
    projectileFlagInformations[14].bindId = _rebounds_from_floor;
    projectileFlagInformations[15].bindId = _penetrates_media;
    projectileFlagInformations[16].bindId = _becomes_item_on_detonation;
    projectileFlagInformations[17].bindId = _bleeding_projectile;
    projectileFlagInformations[18].bindId = _horizontal_wander;
    projectileFlagInformations[19].bindId = _vertical_wander;
    projectileFlagInformations[20].bindId = _affected_by_half_gravity;
    projectileFlagInformations[21].bindId = _penetrates_media_boundary;

    
}

void CPhysicsEditorApp::loadInformations(const char* filename, int num, Information* informations){
    const int LENGTH = 1024*10;
    char cstr[LENGTH];

    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < num; i ++){
        informations[i].jname = array.GetAt(i);
    }
    f.Close();
}
void CPhysicsEditorApp::loadBindInformations(const char* filename, int num,
                                             BindInformation* informations,
                                             int* binds){
    const int LENGTH = 1024*10;
    char cstr[LENGTH];

    CFile f;
    if(!f.Open(CString(filename), CFile::modeRead)){
        CString errMsg = CString("Couldn't open:");
        errMsg += L"[" + CString(filename) + L"]";
        MessageBox(NULL, errMsg, L"Error", MB_OK);
        exit(-1);
    }
    f.Read(cstr, LENGTH);
    CString str = CString(cstr);
    CStringArray array;
    splitString(str, "\r\n", array);
    for(int i = 0; i < num; i ++){
        informations[i].jname = array.GetAt(i);
        informations[i].bindId = binds[i];
    }
    f.Close();
}

// �B��� CPhysicsEditorApp �I�u�W�F�N�g�ł��B

CPhysicsEditorApp theApp;


// CPhysicsEditorApp ������

BOOL CPhysicsEditorApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
    this->accel = LoadAccelerators(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("�A�v���P�[�V���� �E�B�U�[�h�Ő������ꂽ���[�J�� �A�v���P�[�V����"));

    //�l�ȂǏ�����
    theApp.editMonsterTypeId = 0;
    theApp.editEffectTypeId = 0;
    theApp.editProjectileTypeId = 0;
    theApp.editWeaponTypeId = 0;


	CPhysicsEditorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <�L�����Z��> �ŏ����ꂽ���̃R�[�h��
		//  �L�q���Ă��������B
	}

	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	//  �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];

/**
    �R���{�{�b�N�X���̐��l�ݒ�
    -1==NONE�̏ꍇ�Ȃ���Ԃ��Z���N�g

*/
void setComboNum(int sel, int none,
                        CEdit* edit, CComboBox* cmb){
    char cstr[256];
    sprintf(cstr, "%d", sel);
    CString str = CString(cstr);
    edit->SetWindowTextW(str);
    if( sel == -1){
        sel = none;
    }
    cmb->SetCurSel(sel);
}

/**
    �G�f�B�b�g�{�b�N�X�ɐ����������܂�
*/
void setIntegerNum(int num, CEdit* edit){
    char cstr[256];
    sprintf(cstr, "%d", num);
    edit->SetWindowText(CString(cstr));
}
/**
    �G�f�B�b�g�{�b�N�X���琮�����擾���܂�
*/
int getIntegerNum(CEdit* edit){
    int type = theApp.editMonsterTypeId;
    char cstr[256];
    CString str;
    edit->GetWindowTextW(str);
    strToChar(str, cstr);
    int num = atoi(cstr);
    return num;
}

/**
    @param bindId ���蓖�Ă�ꂽ�l
*/
void setComboNumBinded(int bindId, int max,
                       BindInformation* bindInformations,
                       CEdit* edit, CComboBox* cmb){
    char cstr[256];
    sprintf(cstr, "%d", bindId);
    CString str = CString(cstr);
    edit->SetWindowTextW(str);
    //�R���{�{�b�N�X
    int sel = -1;
    for(int i = 0; i < max; i ++){
        if( bindInformations[i].bindId == bindId){
            sel = i;
        }
    }
    if(sel == -1 || bindId == -1){
        sel = max;
    }
    cmb->SetCurSel(sel);
}

BOOL CPhysicsEditorApp::ProcessMessageFilter(int code, LPMSG lpMsg)
{
    if(accel!= NULL){
        if(::TranslateAccelerator(m_pMainWnd -> m_hWnd, accel, lpMsg)){
            return TRUE;                                                  
        }
    }
    return CWinApp::ProcessMessageFilter(code, lpMsg);
}
