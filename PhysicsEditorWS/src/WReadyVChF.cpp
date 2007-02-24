#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WReadyVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WReadyVChF",(void*)WReadyVChF);
