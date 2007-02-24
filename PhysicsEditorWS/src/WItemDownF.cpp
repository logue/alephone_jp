#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WItemDownF(WSCbase* object){
	int type = selectedWeaponType;
	bool isMax = false;
	int index = weapon_definitions[type].item_type;
	long ret = selectFromDialog(&index, object, stockCollections, isMax);
	if(ret == WS_DIALOG_OK){
		weapon_definitions[type].item_type = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("WItemDownF",(void*)WItemDownF);
