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
	int index = monster_definitions[type].contrail_effect;
	long ret = selectFromDialog((int*)&index,
		object, stockEffects, isMaxNONE);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].contrail_effect = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ContrailEffectBtnDownFunc",(void*)ContrailEffectBtnDownFunc);
