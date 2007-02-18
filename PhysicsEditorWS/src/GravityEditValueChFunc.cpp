#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void GravityEditValueChFunc(WSCbase* object){
	int type = selectedMonsterType;
	monster_definitions[type].gravity = getInteger(object);
}
static WSCfunctionRegister  op("GravityEditValueChFunc",(void*)GravityEditValueChFunc);
