#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WShellCasingVChF(WSCbase* object){
	int index = ((WSCoption*)object)->getValue()-1;
	int type = selectedWeaponType;
	weapon_definitions[type].weapons_by_trigger[0].shell_casing_type = index;
}
static WSCfunctionRegister  op("WShellCasingVChF",(void*)WShellCasingVChF);
