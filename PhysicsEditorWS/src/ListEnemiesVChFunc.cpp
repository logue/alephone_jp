#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListEnemiesVChFunc(WSCbase* object){
	int type = selectedMonsterType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d],enemies[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= FLAG(i);
		}else{
		}
	}
	monster_definitions[type].enemies = flags;
}
static WSCfunctionRegister  op("ListEnemiesVChFunc",(void*)ListEnemiesVChFunc);
