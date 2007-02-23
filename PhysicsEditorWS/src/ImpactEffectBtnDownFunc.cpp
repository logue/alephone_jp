#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ImpactEffectBtnDownFunc(WSCbase* object){
	//ëIëÇµÇƒílê›íË
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*óLÇË
	selectFromDialog(&monster_definitions[type].impact_effect,
		object, stockEffects, isMaxNONE);
}
static WSCfunctionRegister  op("ImpactEffectBtnDownFunc",(void*)ImpactEffectBtnDownFunc);
