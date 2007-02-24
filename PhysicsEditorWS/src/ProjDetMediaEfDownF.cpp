#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjDetMediaEfDownF(WSCbase* object){
	int type = selectedProjectileType;
	bool isMax = true;
	int index = projectile_definitions[type].media_detonation_effect;
	long ret = selectFromDialog(&index, object, stockEffects, isMax);
	if(ret == WS_DIALOG_OK){
		projectile_definitions[type].media_detonation_effect = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ProjDetMediaEfDownF",(void*)ProjDetMediaEfDownF);
