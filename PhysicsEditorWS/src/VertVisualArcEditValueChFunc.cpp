#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void VertVisualArcEditValueChFunc(WSCbase* object){
	int type = selectedMonsterType;
	monster_definitions[type].half_vertical_visual_arc = getInteger(object);
}
static WSCfunctionRegister  op("VertVisualArcEditValueChFunc",(void*)VertVisualArcEditValueChFunc);
