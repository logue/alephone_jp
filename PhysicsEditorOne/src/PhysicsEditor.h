// PhysicsEditor.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "monsters.h"
#include "effects.h"
#include "physics_models.h"
#include "projectiles.h"
#include "items.h"
#include "mysound.h"
#include "weapons.h"
#include "monster_definitions.h"
#include "effect_definitions.h"
#include "projectile_definitions.h"
#include "weapon_definitions.h"

// CPhysicsEditorApp:
// このクラスの実装については、PhysicsEditor.cpp を参照してください。
//

const int NUMBER_OF_CLASS_INFORMATIONS = 16;
const int NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS = 4;
const int NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS = 3;
const int NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS = 4;
const int NUMBER_OF_MONSTER_FLAG_INFORMATIONS = 28;
const int NUMBER_OF_SPEED_INFORMATIONS = 11;
const int NUMBER_OF_EFFECT_FLAG_INFORMATIONS = 5;
const int NUMBER_OF_WEAPON_CLASS_INFORMATIONS = 5;
const int NUMBER_OF_WEAPON_FLAG_INFORMATIONS = 11;
const int NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS = 22;
const int NUMBER_OF_ERROR_MESSAGE_INFORMATIONS = 3;

/**
    表記情報
    名前だけバージョン
*/
typedef struct Information_tag{
    /**日本語名*/
    CString jname;
}Information;

typedef struct BindInformation_tag{
    CString jname;
    /**対応する実際の番号*/
    int bindId;
}BindInformation;


class CPhysicsEditorApp : public CWinApp
{
public:
	CPhysicsEditorApp();
    //HACCEL accel;

// オーバーライド
	public:
	virtual BOOL InitInstance();
    virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
    //BOOL PreTranslateMessage(MSG* pMsg);
    HACCEL accel;
// 実装

	DECLARE_MESSAGE_MAP()
public:
// 変数
    /**選択・編集しているモンスターの種類ID*/
    int editMonsterTypeId;
    int editEffectTypeId;
    int editProjectileTypeId;
    int editPhysicsTypeId;
    int editWeaponTypeId;
    //BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

    void loadInformations(const char* filename, int num, Information* informations);
    void loadBindInformations(const char* filename, int num,
        BindInformation* informations, int *binds);

    struct monster_definition monster_default_definitions[NUMBER_OF_MONSTER_TYPES];
    struct effect_definition effect_default_definitions[NUMBER_OF_EFFECT_TYPES];
    struct projectile_definition projectile_default_definitions[NUMBER_OF_PROJECTILE_TYPES];
    struct physics_constants physics_default_models[NUMBER_OF_PHYSICS_MODELS];
    struct weapon_definition weapon_default_definitions[MAXIMUM_NUMBER_OF_WEAPONS];

    Information collectionInformations[NUMBER_OF_COLLECTIONS];
    Information monsterInformations[NUMBER_OF_MONSTER_TYPES];
    Information monsterActivateInformations[NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS];
    Information effectInformations[NUMBER_OF_EFFECT_TYPES];
    Information soundInformations[NUMBER_OF_SOUND_DEFINITIONS];
    Information weaponInformations[MAXIMUM_NUMBER_OF_WEAPONS];
    Information definedItemInformations[NUMBER_OF_DEFINED_ITEMS];
    BindInformation monsterClassInformations[NUMBER_OF_CLASS_INFORMATIONS];
    BindInformation monsterIntelligences[NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS];
    BindInformation monsterDoorRetryMasks[NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS];
    BindInformation monsterFlags[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];
    BindInformation speeds[NUMBER_OF_SPEED_INFORMATIONS];
    Information damageInformations[NUMBER_OF_DAMAGE_TYPES];
    Information projectileInformations[NUMBER_OF_PROJECTILE_TYPES];
    BindInformation projectileFlagInformations[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS];
    BindInformation effectFlagInformations[NUMBER_OF_EFFECT_FLAG_INFORMATIONS];

    Information weaponClassInformations[NUMBER_OF_WEAPON_CLASS_INFORMATIONS];
    BindInformation weaponFlagInformations[NUMBER_OF_WEAPON_FLAG_INFORMATIONS];
    Information weaponShellCasingInformations[NUMBER_OF_SHELL_CASING_TYPES];

    Information physicsInformations[NUMBER_OF_PHYSICS_MODELS];

    Information errorMessageInformations[NUMBER_OF_ERROR_MESSAGE_INFORMATIONS];
};

extern CPhysicsEditorApp theApp;

void strToChar(CString src, char* dest);
void wcharToChar(WCHAR* src, char* dest);

void charToWChar(char* src, WCHAR* dest);

/**
    コンボボックスつきの数値設定
    -1==NONEの場合なし状態をセレクト

*/
void setComboNum(int sel, int none,
                        CEdit* edit, CComboBox* cmb);
/**
    エディットボックスに整数を代入します
*/
void setIntegerNum(int num, CEdit* edit);
int getIntegerNum(CEdit* edit);

//割り当て番号つきコンボとエディットボックスを設定
void setComboNumBinded(int bindId, int max,
                       BindInformation* bindInformations,
                       CEdit* edit, CComboBox* cmb);


