#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MeleeEffectBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	int index = monster_definitions[type].melee_impact_effect;
	selectFromDialog((int*)&index,
		object, stockEffects, isMaxNONE);
	monster_definitions[type].melee_impact_effect = index;
	setupDialog();
}
static WSCfunctionRegister  op("MeleeEffectBtnDownFunc",(void*)MeleeEffectBtnDownFunc);
