#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WChargingSeqVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WChargingSeqVChF",(void*)WChargingSeqVChF);
