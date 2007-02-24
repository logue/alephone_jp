#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjPresetHandGrenadeDownF(WSCbase* object){
	int type = selectedProjectileType;
	//TODO
	messageBox("Cannot use this function");
}
static WSCfunctionRegister  op("ProjPresetHandGrenadeDownF",(void*)ProjPresetHandGrenadeDownF);
