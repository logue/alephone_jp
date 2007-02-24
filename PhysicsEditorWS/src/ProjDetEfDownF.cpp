#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjDetEfDownF(WSCbase* object){
	int type = selectedProjectileType;
	bool isMax = true;
	int index = projectile_definitions[type].detonation_effect;
	long ret = selectFromDialog(&index, object, stockEffects, isMax);
	if(ret == WS_DIALOG_OK){
		projectile_definitions[type].detonation_effect = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ProjDetEfDownF",(void*)ProjDetEfDownF);
