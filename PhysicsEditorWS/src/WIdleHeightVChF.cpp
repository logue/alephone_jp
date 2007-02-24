#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WIdleHeightVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WIdleHeightVChF",(void*)WIdleHeightVChF);
