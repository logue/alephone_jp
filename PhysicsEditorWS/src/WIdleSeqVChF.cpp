#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WIdleSeqVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WIdleSeqVChF",(void*)WIdleSeqVChF);
