#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WSAmmoItemDownF(WSCbase* object){
	int type = selectedWeaponType;
	bool isMax = true;
	int index = weapon_definitions[type].weapons_by_trigger[1].ammunition_type;
	long ret = selectFromDialog(&index, object, stockItemTypes, isMax);
	if(ret == WS_DIALOG_OK){
		weapon_definitions[type].weapons_by_trigger[1].ammunition_type = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("WSAmmoItemDownF",(void*)WSAmmoItemDownF);
