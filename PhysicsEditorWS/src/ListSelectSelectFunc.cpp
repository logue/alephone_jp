#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSClist.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListSelectSelectFunc(WSCbase* object){
  //do something...
	selectIndex = ((WSClist*)object)->getSelectedPos();
}
static WSCfunctionRegister  op("ListSelectSelectFunc",(void*)ListSelectSelectFunc);
