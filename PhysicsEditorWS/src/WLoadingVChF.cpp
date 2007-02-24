#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WLoadingVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WLoadingVChF",(void*)WLoadingVChF);
