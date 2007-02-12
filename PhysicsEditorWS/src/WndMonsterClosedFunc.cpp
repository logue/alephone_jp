#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WndMonsterClosedFunc(WSCbase* object){
  //do something...
	
}
static WSCfunctionRegister  op("WndMonsterClosedFunc",(void*)WndMonsterClosedFunc);
