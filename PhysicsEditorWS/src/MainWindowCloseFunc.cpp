#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainWindowCloseFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("MainWindowCloseFunc",(void*)MainWindowCloseFunc);
