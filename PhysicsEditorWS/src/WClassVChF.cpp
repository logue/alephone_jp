#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WClassVChF(WSCbase* object){
	int index = ((WSCoption*)object)->getValue() - 1;
	int type = selectedWeaponType;
	weapon_definitions[type].weapon_class = index;
	setupDialog();
}
static WSCfunctionRegister  op("WClassVChF",(void*)WClassVChF);
