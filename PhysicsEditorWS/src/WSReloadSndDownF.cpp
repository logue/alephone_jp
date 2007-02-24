#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WSReloadSndDownF(WSCbase* object){
	int type = selectedWeaponType;
	bool isMax = true;
	int index = weapon_definitions[type].weapons_by_trigger[1].reloading_sound;
	long ret = selectFromDialog(&index, object, stockSounds, isMax);
	if(ret == WS_DIALOG_OK){
		weapon_definitions[type].weapons_by_trigger[1].reloading_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("WSReloadSndDownF",(void*)WSReloadSndDownF);
