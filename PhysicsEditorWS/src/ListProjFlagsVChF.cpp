#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListProjFlagsVChF(WSCbase* object){
	int type = selectedProjectileType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d], proj flags[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= valueProjectileFlags[i];
		}else{
		}
	}
	projectile_definitions[type].flags = flags;
}
static WSCfunctionRegister  op("ListProjFlagsVChF",(void*)ListProjFlagsVChF);
