#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WSShellCasingVChF(WSCbase* object){
	int index = ((WSCoption*)object)->getValue()-1;
	weapon_definitions[selectedWeaponType].weapons_by_trigger[1].shell_casing_type = index;
}
static WSCfunctionRegister  op("WSShellCasingVChF",(void*)WSShellCasingVChF);
