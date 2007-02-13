#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainWindowExitFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("MainWindowExitFunc",(void*)MainWindowExitFunc);
