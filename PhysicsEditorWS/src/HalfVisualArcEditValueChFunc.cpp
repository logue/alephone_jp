#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void HalfVisualArcEditValueChFunc(WSCbase* object){
	int type = selectedMonsterType;
	monster_definitions[type].half_visual_arc = getInteger(object);
}
static WSCfunctionRegister  op("HalfVisualArcEditValueChFunc",(void*)HalfVisualArcEditValueChFunc);
