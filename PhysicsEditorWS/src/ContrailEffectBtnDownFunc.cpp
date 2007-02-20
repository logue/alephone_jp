#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ContrailEffectBtnDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("ContrailEffectBtnDownFunc",(void*)ContrailEffectBtnDownFunc);
