#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ImpactEffectBtnDownFunc(WSCbase* object){
	//選択して値設定
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*有り
	selectFromDialog(&monster_definitions[type].impact_effect,
		object, stockEffects, isMaxNONE);
}
static WSCfunctionRegister  op("ImpactEffectBtnDownFunc",(void*)ImpactEffectBtnDownFunc);
