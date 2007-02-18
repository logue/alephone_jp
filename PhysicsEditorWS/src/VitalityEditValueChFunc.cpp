#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void VitalityEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	if(type >= 0 && type < NUMBER_OF_MONSTER_TYPES){
		long val = getInteger(object);
		monster_definitions[type].vitality = val;
	}
}
static WSCfunctionRegister  op("VitalityEditValueChFunc",(void*)VitalityEditValueChFunc);
