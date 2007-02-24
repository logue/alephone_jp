#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WFlagsVChF(WSCbase* object){
	int type = selectedWeaponType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d], weapon flags[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= valueWeaponFlags[i];
		}else{
		}
	}
	weapon_definitions[type].flags = flags;
}
static WSCfunctionRegister  op("WFlagsVChF",(void*)WFlagsVChF);
