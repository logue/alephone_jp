#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnRangedPresetDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("BtnRangedPresetDownFunc",(void*)BtnRangedPresetDownFunc);
