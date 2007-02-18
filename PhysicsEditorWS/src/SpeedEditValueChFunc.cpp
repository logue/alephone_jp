#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void SpeedEditValueChFunc(WSCbase* object){
	int type = selectedMonsterType;
	monster_definitions[type].speed = getInteger(object);
	setupDialog();
}
static WSCfunctionRegister  op("SpeedEditValueChFunc",(void*)SpeedEditValueChFunc);
