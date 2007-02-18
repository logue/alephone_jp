#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ClassComboValueChFunc(WSCbase* object){
  //do something...
	int val = ((WSCoption*)object)->getValue() - 1;
	int type = selectedMonsterType;
	int _class = valueMonsterClasses[val];
	monster_definitions[type]._class = _class;
}
static WSCfunctionRegister  op("ClassComboValueChFunc",(void*)ClassComboValueChFunc);
