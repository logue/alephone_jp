#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void HeightEditValueChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	monster_definitions[type].height = getInteger(object);
}
static WSCfunctionRegister  op("HeightEditValueChFunc",(void*)HeightEditValueChFunc);
