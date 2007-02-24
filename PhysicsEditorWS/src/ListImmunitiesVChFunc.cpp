#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListImmunitiesVChFunc(WSCbase* object){
	int type = selectedMonsterType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d], immunity[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= valueEffectFlags[i];
		}else{
		}
	}
	monster_definitions[type].immunities = flags;
}
static WSCfunctionRegister  op("ListImmunitiesVChFunc",(void*)ListImmunitiesVChFunc);
