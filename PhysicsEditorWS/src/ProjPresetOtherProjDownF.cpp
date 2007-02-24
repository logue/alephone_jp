#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjPresetOtherProjDownF(WSCbase* object){
	int type = selectedProjectileType;
	int index = 1;
	bool isMax = false;
	long ret = selectFromDialog(&index, object, stockProjectiles, isMax);
	if(ret == WS_DIALOG_OK && 
		index >= 0 && index < NUMBER_OF_PROJECTILE_TYPES){
		//copy
		memcpy(&projectile_definitions[type],
			&projectile_definitions[index], sizeof(struct projectile_definition));
		setupDialog();
	}
}
static WSCfunctionRegister  op("ProjPresetOtherProjDownF",(void*)ProjPresetOtherProjDownF);
