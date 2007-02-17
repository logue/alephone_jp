#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListProjectileDownFunc(WSCbase* object){
  //do something...
	//get selected index
	selectedProjectileType = ((WSClist*)object)->getSelectedPos();
	setupDialog();
}
static WSCfunctionRegister  op("ListProjectileDownFunc",(void*)ListProjectileDownFunc);
