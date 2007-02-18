#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void HoverEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	monster_definitions[type].preferred_hover_height = getInteger(object);
}
static WSCfunctionRegister  op("HoverEditValueChFunc",(void*)HoverEditValueChFunc);
