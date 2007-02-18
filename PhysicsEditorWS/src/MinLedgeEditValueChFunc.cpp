#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MinLedgeEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	monster_definitions[type].minimum_ledge_delta = getInteger(object);
}
static WSCfunctionRegister  op("MinLedgeEditValueChFunc",(void*)MinLedgeEditValueChFunc);
