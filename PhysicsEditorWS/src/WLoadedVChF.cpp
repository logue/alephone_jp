#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WLoadedVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WLoadedVChF",(void*)WLoadedVChF);
