#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ContrailEffectBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].contrail_effect,
		object, stockEffects, isMaxNONE);
}
static WSCfunctionRegister  op("ContrailEffectBtnDownFunc",(void*)ContrailEffectBtnDownFunc);
