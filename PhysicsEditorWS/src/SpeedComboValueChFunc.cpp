#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void SpeedComboValueChFunc(WSCbase* object){
	int val = ((WSCoption*)object)->getValue()-1;
	int type = selectedMonsterType;
	monster_definitions[type].speed = valueSpeed[val];
	setupDialog();
}
static WSCfunctionRegister  op("SpeedComboValueChFunc",(void*)SpeedComboValueChFunc);
