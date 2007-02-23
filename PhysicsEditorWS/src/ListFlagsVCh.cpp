#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListFlagsVCh(WSCbase* object){
	int type = selectedMonsterType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d],flags[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= FLAG(i);
		}else{
		}
	}
	monster_definitions[type].flags = flags;
	//setupDialog();
}
static WSCfunctionRegister  op("ListFlagsVCh",(void*)ListFlagsVCh);
