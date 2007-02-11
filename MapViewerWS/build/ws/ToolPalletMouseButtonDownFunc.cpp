#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ToolPalletMouseButtonDownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("ToolPalletMouseButtonDownFunc",(void*)ToolPalletMouseButtonDownFunc);
