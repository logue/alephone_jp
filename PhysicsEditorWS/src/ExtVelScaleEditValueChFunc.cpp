#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ExtVelScaleEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	monster_definitions[type].external_velocity_scale = getInteger(object);
}
static WSCfunctionRegister  op("ExtVelScaleEditValueChFunc",(void*)ExtVelScaleEditValueChFunc);
