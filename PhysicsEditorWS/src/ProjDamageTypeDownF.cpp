#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjDamageTypeDownF(WSCbase* object){
	int type = selectedProjectileType;
	bool isMax = true;
	int index = projectile_definitions[type].damage.type;
	long ret = selectFromDialog(&index, object, stockDamages, isMax);
	if(ret == WS_DIALOG_OK){
		projectile_definitions[type].damage.type = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ProjDamageTypeDownF",(void*)ProjDamageTypeDownF);
