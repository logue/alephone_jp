#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"
#include <WSCwindow.h>
#include <WSClist.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnMonsterPressFunc(WSCbase* object){
  //do something...
	changeForm(Windows::Monster);
}
static WSCfunctionRegister  op("BtnMonsterPressFunc",(void*)BtnMonsterPressFunc);