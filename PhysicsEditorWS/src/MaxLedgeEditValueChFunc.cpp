#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MaxLedgeEditValueChFunc(WSCbase* object){
	int type = selectedMonsterType;
	monster_definitions[type].maximum_ledge_delta = getInteger(object);
}
static WSCfunctionRegister  op("MaxLedgeEditValueChFunc",(void*)MaxLedgeEditValueChFunc);
