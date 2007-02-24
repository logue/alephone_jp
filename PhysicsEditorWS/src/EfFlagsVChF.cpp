#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void EfFlagsVChF(WSCbase* object){
	int type = selectedEffectType;
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
		WSCvradio* item = (WSCvradio*)((WSCcheckGroup*)object)->getItem(i);
		if(item == NULL){
			messageBox("NULL id[%d], effect flags[%x]", i, item);
			exit(1);
		}
		WSCbool status = item->getStatus();
		if(status == True){
			flags |= valueEffectFlags[i];
		}else{
		}
	}
	effect_definitions[type].flags = flags;
}
static WSCfunctionRegister  op("EfFlagsVChF",(void*)EfFlagsVChF);
