#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WIdleWidthVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("WIdleWidthVChF",(void*)WIdleWidthVChF);
