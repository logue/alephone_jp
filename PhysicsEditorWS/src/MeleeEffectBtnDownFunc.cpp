#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MeleeEffectBtnDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("MeleeEffectBtnDownFunc",(void*)MeleeEffectBtnDownFunc);
