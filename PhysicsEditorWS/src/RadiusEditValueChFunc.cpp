#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void RadiusEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	monster_definitions[type].radius = getInteger(object);
}
static WSCfunctionRegister  op("RadiusEditValueChFunc",(void*)RadiusEditValueChFunc);
