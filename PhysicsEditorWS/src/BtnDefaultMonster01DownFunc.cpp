#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnDefaultMonster01DownFunc(WSCbase* object){
  //do something...
	//TODO
	messageBox("Cannot use this function, yet");
}
static WSCfunctionRegister  op("BtnDefaultMonster01DownFunc",(void*)BtnDefaultMonster01DownFunc);
