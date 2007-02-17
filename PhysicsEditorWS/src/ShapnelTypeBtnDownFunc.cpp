#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ShapnelTypeBtnDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("ShapnelTypeBtnDownFunc",(void*)ShapnelTypeBtnDownFunc);
