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

void setupDialog(WSCbase* object)
{
	if(windowType == Windows::Monster){
		//window
		WSCwindow* wnd = (WSCwindow*)getObject("WSCwindow", "WndMonster");
		int type = selectedMonsterType;
		
		//設定
		int16 collection = monster_definitions[type].collection;
		int16 col = GET_COLLECTION(collection);
		int16 clut = GET_COLLECTION_CLUT(collection);
		
		//index
		WSCindexForm* indextab = (WSCindexForm*)wnd->getChildInstance("Maiinde_012");
		//clut
		WSCvifield* clutField = (WSCvifield*)indextab->getChildInstance("PalletEdit");
		clutField->setProperty(WSNlabelString, (long)clut);
		//clutField->update();
		
		//vitality
		setInteger(indextab->getChildInstance("VitalityEdit"), monster_definitions[type].vitality);
		//class
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
		//carryitem
		//halfvisualarc
		setInteger(indextab->getChildInstance("HalfVisualArc"), monster_definitions[type].half_visual_arc);
		//vertvisualarc
		setInteger(indextab->getChildInstance("VertVisualArc"), monster_definitions[type].half_vertical_visual_arc);
		//interlligence
		//speed
		//gravity
		setInteger(indextab->getChildInstance("Gravity"), monster_definitions[type].gravity);
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
