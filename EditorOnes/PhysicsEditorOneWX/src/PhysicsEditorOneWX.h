#ifndef _PHYSICS_EDITOR_ONE_WX_
#define _PHYSICS_EDITOR_ONE_WX_

#include "Common.h"
#include "PhysicsDefaultValues.h"
#include "PhysicsEditorCommonSrc/PhysicsEditorCommon.h"

static char* TITLE = "Physics Editor One wxWidgets version";

class MainFrame;

class PhysicsEditorOneWX: public wxApp{
public:
	//フレーム
	MainFrame* frame;

	//デフォルト設定
	PhysicsDefaultValues defaultValues;

	//一般 general
	//	Collections <jp>コレクション
	hpl::aleph::Information collectionInfo[NUMBER_OF_COLLECTIONS];
	//	Sounds <jp>音
	hpl::aleph::Information soundInfo[NUMBER_OF_SOUND_DEFINITIONS];
	//	damage
	hpl::aleph::Information damageInfo[NUMBER_OF_DAMAGE_TYPES];
    //	Items <jp>アイテム
    hpl::aleph::Information itemInfo[NUMBER_OF_DEFINED_ITEMS];
	//	speed (preset)
	hpl::aleph::InformationBinded speedBind[NUMBER_OF_SPEED_INFORMATIONS];

    //モンスター
	//	種類 <en> types
    hpl::aleph::Information monsterInfo[NUMBER_OF_MONSTER_TYPES];
	//	アクティブ要素
    hpl::aleph::Information monsterActivateInfo[NUMBER_OF_MONSTER_ACTIVATE_INFORMATIONS];
	//	classes
	hpl::aleph::InformationBinded monsterClassBind[NUMBER_OF_CLASS_INFORMATIONS];
	//	intelligence
	hpl::aleph::InformationBinded monsterIntelligenceBind[NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS];
	//	door retry mask
	hpl::aleph::InformationBinded monsterDoorRetryMaskBind[NUMBER_OF_MONSTER_DOOR_RETRY_MASK_INFORMATIONS];
	//	flags
	hpl::aleph::InformationBinded monsterFlagsBind[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];

	//projectiles
	//	types
	hpl::aleph::Information projectileInfo[NUMBER_OF_PROJECTILE_TYPES];
	//	flags
	hpl::aleph::InformationBinded projectileFlagsBind[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS];

	//effect
	//	types
	hpl::aleph::Information effectInfo[NUMBER_OF_EFFECT_TYPES];
	//	flags
	hpl::aleph::InformationBinded effectFlagsBind[NUMBER_OF_EFFECT_FLAG_INFORMATIONS];

	//physics
	hpl::aleph::Information physicsInfo[NUMBER_OF_PHYSICS_MODELS];

	//weapon
	//	types
	hpl::aleph::Information weaponInfo[MAXIMUM_NUMBER_OF_WEAPONS];
	//	classs
	hpl::aleph::Information weaponClassInfo[NUMBER_OF_WEAPON_CLASS_INFORMATIONS];
	//	flags
	hpl::aleph::InformationBinded weaponFlagsBind[NUMBER_OF_WEAPON_FLAG_INFORMATIONS];
	//	shell casing
	hpl::aleph::Information weaponShellCasingInfo[NUMBER_OF_SHELL_CASING_TYPES];
private:
	/**このPhysicsデータは編集されているか？*/
	bool isChanged_;

	/**このPhysicsデータはファイルから読み込まれたものではないのか？*/
	bool isNew_;

	/**読み込んだ場合保存先のパス*/
	std::string saveFilePath;
public:
private:
	bool OnInit();

	/**
		wxWidgetsに依存しない初期設定
	*/
	void init();
public:
	/**
		更新があったかどうか
	*/
	void setNewAndChanged(bool new_, bool changed);
	bool isChanged();
	/**
		新規データか
	*/
	bool isNew();

	/**
		読み込んだあるいは保存先のファイルパスを設定
		存在しない場合にこれを呼ぶというのは処理がおかしいことになる。
		それのチェックも兼ねる
	*/
	void setSaveFilePath(const char* filePath);
	std::string getSaveFilePath();

	/**
		デフォルト設定の取り出し
	*/
	PhysicsDefaultValues* getDefaultValues();

	/**
		PhysicsFileを読み込みます
	*/
	void loadPhysicsFile(const char* filePath);
	void loadDefaultPhysicsFile();

	/**
		Save and/or create PhysicsFile
	*/
	void savePhysicsFile(const char* filePath);
};

DECLARE_APP(PhysicsEditorOneWX)

#endif
