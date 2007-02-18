#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListWeaponsDownFunc(WSCbase* object){
  //do something...
	selectedWeaponType = ((WSClist*)object)->getSelectedPos();
	setupDialog();
}
static WSCfunctionRegister  op("ListWeaponsDownFunc",(void*)ListWeaponsDownFunc);
