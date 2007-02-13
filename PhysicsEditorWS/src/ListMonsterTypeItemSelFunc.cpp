#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

#include <WSClist.h>
#include <WSCwindow.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListMonsterTypeItemSelFunc(WSCbase* object){
  //do something...
	//get selected pos
	long index = ((WSClist*)object)->getSelectedPos();
	
	//set type
	selectedMonsterType = index;
	//update monster window
	WSCbase* wndMonster = getObject("WSCwindow", "WndMonster");
	setupDialog(wndMonster);

}
static WSCfunctionRegister  op("ListMonsterTypeItemSelFunc",(void*)ListMonsterTypeItemSelFunc);
