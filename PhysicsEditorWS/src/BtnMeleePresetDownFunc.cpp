#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnMeleePresetDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("BtnMeleePresetDownFunc",(void*)BtnMeleePresetDownFunc);
