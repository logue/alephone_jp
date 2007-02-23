#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnMeleeTypeDownFunc(WSCbase* object){
	//select projectile
	int type = selectedMonsterType;
	int index = monster_definitions[type].melee_attack.type;
	bool isMax = true;
	selectFromDialog(&index, object, stockProjectiles, isMax);
	monster_definitions[type].melee_attack.type = index;
	setupDialog();
}
static WSCfunctionRegister  op("BtnMeleeTypeDownFunc",(void*)BtnMeleeTypeDownFunc);
