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
	selectFromDialog(&monster_definitions[type].melee_effect,
		object, stockEffects, isMaxNONE);
}
static WSCfunctionRegister  op("MeleeEffectBtnDownFunc",(void*)MeleeEffectBtnDownFunc);
