#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjFlyBySndDownF(WSCbase* object){
	int type = selectedProjectileType;
	bool isMax = true;
	int index = projectile_definitions[type].flyby_sound;
	long ret = selectFromDialog(&index, object, stockSounds, isMax);
	if(ret == WS_DIALOG_OK){
		projectile_definitions[type].flyby_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ProjFlyBySndDownF",(void*)ProjFlyBySndDownF);
